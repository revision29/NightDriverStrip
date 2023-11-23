//+--------------------------------------------------------------------------
//
// File:        remotecontrol.cpp
//
// NightDriverStrip - (c) 2018 Plummer's Software LLC.  All Rights Reserved.
//
// This file is part of the NightDriver software project.
//
//    NightDriver is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    NightDriver is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Nightdriver.  It is normally found in copying.txt
//    If not, see <https://www.gnu.org/licenses/>.
//
//
// Description:
//
//    Handles a simple IR remote for changing effects, brightness, etc.
//
// History:     Jun-14-2023     Rbergen        Extracted handle() from header
//---------------------------------------------------------------------------

#include "globals.h"

#if ENABLE_REMOTE


#include "systemcontainer.h"

// Include any effects you will directly trigger with the remote.
#include "effects/strip/misceffects.h"
#include "effects/strip/paletteeffect.h"

#define BRIGHTNESS_STEP     20
/*
We will need to define the user remote control
*/

UserRemoteControl myRemoteController = UserRemoteControl();//Loads remote and user defined buttons

//Repeat codes
//Press and hold brightness up or down to wuickly adjust up. 
//Otherwise acknolwedge the keypress only every 200ms or.
//First check for a match. If no metch we just return.
//If a match then we check against repeating then we trigger the button action


/*
!!! See ~/Development/Remote Code/Changes to effect manager.md for task list
*/
void RemoteControl::handle()
{
    decode_results results;
    auto& deviceConfig = g_ptrSystem->DeviceConfig();

    static uint lastResult = 0;
    static uint lastProcessTime = millis();
    //static int currentBrightness = deviceConfig.GetBrightness() == 0 ? 255 : deviceConfig.GetBrightness();
    static int currentBrightness = deviceConfig.GetBrightness();

    static boolean remotePower = true;
    
    if (!_IR_Receive.decode(&results))
        return;

    uint result = results.value;
    //debugI("Remote code %08x", result);
    _IR_Receive.resume();
    //debugI("Now %i, lastProcessTime %i\n", millis(), lastProcessTime);
    uint timeDiff = millis() - lastProcessTime;
    //debugI("Process time diff %i\n", timeDiff);
    /*
    if (result == 0xFFFFFFFF)
    {
        debugI("We have a repeat code\n");
    }
    */

    if (result == 0xFFFFFFFF && timeDiff < 100) 
        return;
    if (result == 0xFFFFFFFF  && lastResult != 0xFFFFFFFF && lastResult != 0) // Repeat code sent by remote. Treat like it was the previous button code processed.
        result = lastResult;

    auto searchResult = myRemoteController.buttons.find(result);
    if (searchResult != myRemoteController.buttons.end()) 
    {
        RemoteButton thisButton = searchResult->second;
        if (result == lastResult) 
        {
            static uint lastRepeatTime = millis();
            auto kMinRepeatms = (thisButton.buttonAction == BRIGHTNESS_DOWN || thisButton.buttonAction == BRIGHTNESS_UP) ? 150 : 300;

            //We do not want to set the kMinRepeatms to 0 because some remotes send a code more than once and also there might be refelctive surfaces that will cause the signal to be recieved more than once in rapid succession.
            // Brightness adjustments will be allowed to repeat more often. 
            if (millis() - lastRepeatTime > kMinRepeatms)
            {
                //debugI("Remote Repeat; lastResult == %08x, elapsed = %lu, repeate time = %i \n", lastResult, millis()-lastRepeatTime, kMinRepeatms);
                lastRepeatTime = millis();
            }
            else
            {
                //debugI("Remote Repeat, not repeating; lastResult == %08x, elapsed = %lu, repeate time = %i \n", lastResult, millis()-lastRepeatTime, kMinRepeatms);
                //processingRemoteButtonPress = false;
                //debugI("The code was sent too soon. Exiting.\n");
                return;
            }   
        }

        //Process the code
        auto &effectManager = g_ptrSystem->EffectManager();
        
        switch (thisButton.buttonAction)
        {
            case BRIGHTNESS_UP:
               deviceConfig.SetBrightness((int)deviceConfig.GetBrightness() + BRIGHTNESS_STEP);
               currentBrightness = deviceConfig.GetBrightness();

            break;
            case BRIGHTNESS_DOWN:
                deviceConfig.SetBrightness((int)deviceConfig.GetBrightness() - BRIGHTNESS_STEP);
                if (deviceConfig.GetBrightness() != 0)
                    currentBrightness = deviceConfig.GetBrightness();
                //debugI("After brightness down global brightness is  %i\n",deviceConfig.GetBrightness());

            break;
            case POWER_TOGGLE:
            {
                if (deviceConfig.GetBrightness() == 0)
                {
                    if (currentBrightness == 0)
                        currentBrightness = 20;
                    deviceConfig.SetBrightness(currentBrightness);
                } else
                {
                    currentBrightness = deviceConfig.GetBrightness();
                    deviceConfig.SetBrightness(0);
                }
/*
                if (remotePower == true)
                {
                    debugI("Power is on, so w turn it off.\n");
                    remotePower = false;
                    if (deviceConfig.GetBrightness() != 0) 
                        currentBrightness = deviceConfig.GetBrightness();
                    else
                        currentBrightness = 255;
                    deviceConfig.SetBrightness(0);
                    //deviceConfig.ClearGlobalColor();
                    
                } else 
                {
                    debugI("Power is off, so we turn it on\n");
                    remotePower = false;
                    if (currentBrightness == 0)
                        currentBrightness = 255;
                    deviceConfig.SetBrightness(currentBrightness);
                }
                */
            }
            case ButtonActions::POWER_ON:
                //effectManager.SetInterval(0);
                //effectManager.SetTemporaryStripEffect(make_shared_psram<ColorFillEffect>(lastManualColor, 1));
                //effectManager.StartEffect();
                {
                    
                }
            break;
            case POWER_OFF:
                effectManager.ClearTemporaryStripEffect();
                effectManager.ClearGlobalColor();
            break;
            case NEXT_EFFECT: 
                effectManager.NextEffect();
            break;
            case FILL_COLOR:
            {
                CRGB fillColor = hexToCRGB(thisButton.actionArgs);
                effectManager.SetGlobalColor(fillColor);
                /*
                if (deviceConfig.GetGlobalColor() == fillColor)
                    effectManager.ClearGlobalColor();
                else
                    effectManager.SetGlobalColor(fillColor);
                */
            }
            break;
            
            case TRIGGER_EFFECT:
                {
                    auto effect = make_shared_psram<ColorFillEffect>(CRGB::White, 1);
                }
                
            break;
            case CHANGER: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GetGlobalColor();
                    tempColor.red += thisButton.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor);
                }
            break;
            case CHANGEG: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GetGlobalColor();
                    tempColor.green += thisButton.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor);
                }
                    
            break;
            case CHANGEB: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GetGlobalColor();
                    tempColor.blue += thisButton.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor); 
                }
            break;
            case DIY1:
                effectManager.SetCurrentEffectIndex(0);
            break;
            case DIY2: 
                effectManager.SetCurrentEffectIndex(1);
                
            break;
            case DIY3: 
                effectManager.SetCurrentEffectIndex(2);
            break;
            case DIY4: 
                effectManager.SetCurrentEffectIndex(3);
            break;
            case DIY5: 
                effectManager.SetCurrentEffectIndex(4);
            break;
            case DIY6: 
                effectManager.SetCurrentEffectIndex(5);
            break;
            
            // There are effects defined that will scroll throw different effects.
            case JUMP3:
            {
            // Fade speed is 0
            // 3 colors

                //ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB::Blue, CRGB::MediumPurple, CRGB::Azure), 256 / 32, .3, 0,4,0);
                auto effect = make_shared_psram<PaletteEffect>(CRGBPalette16(CRGB::Blue, CRGB::MediumPurple, CRGB::Azure), 256 / 32, .3, 0,4,0);
            }
            break;
            //case JUMP7:
            //Fade speed is 0
            //Colors are 7
            //break;
            //case FADE3:
            //break;
            //case FADE7:
            //break;
            //case STROBE:
            //break;
            case AUTO:
            {
                if (effectManager.GetInterval() != 30000) 
                {
                    //debugI("Setting interval to 30 seconds\n");
                    effectManager.SetInterval(30000, true);
                   // debugI("Triggering Next Effect\n");
                    effectManager.NextEffect();
                } else
                {
                    //debugI("Setting interval to 0 seconds\n");
                    effectManager.SetInterval(0);
                }
            }
            break;
            case FLASH:
                effectManager.ClearGlobalColor();
            break;
            //case QUICK:
            //break;
            //case SLOW:
            //break;
        } // End of Switch
        lastProcessTime = millis();
    } else
    {
        // This block is only needed to help debug issues.
        // debugI("We do not have a remote code result 0X%08X", result);
    }
    if (result != 0xFFFFFFFF )
        lastResult = result;
    //processingRemoteButtonPress = false;
    //debugI("end of IR handle time: %i", millis());
}

/*
//The old remote handling code
void RemoteControl::handle()
{
    decode_results results;
    static uint lastResult = 0;

    if (!_IR_Receive.decode(&results))
        return;

    uint result = results.value;
    _IR_Receive.resume();

    debugV("Received IR Remote Code: 0x%08X, Decode: %08X\n", result, results.decode_type);

    if (0xFFFFFFFF == result || result == lastResult)
    {
        static uint lastRepeatTime = millis();

        // Only the OFF key runs at the full unbounded speed, so you can rapidly dim.  But everything
        // else has its repeat rate clamped here.

        const auto kMinRepeatms = (lastResult == IR_OFF) ? 0 : 200;

        if (millis() - lastRepeatTime > kMinRepeatms)
        {
        debugV("Remote Repeat; lastResult == %08x, elapsed = %lu\n", lastResult, millis()-lastRepeatTime);
            result = lastResult;
            lastRepeatTime = millis();
        }
        else
        {
            return;
        }
    }
    lastResult = result;

    auto &effectManager = g_ptrSystem->EffectManager();

    if (IR_ON == result)
    {
        debugV("Turning ON via remote");
        effectManager.ClearGlobalColor();
        effectManager.SetInterval(0);
        effectManager.StartEffect();
        g_ptrSystem->DeviceConfig().SetBrightness(BRIGHTNESS_MAX);
        return;
    }
    else if (IR_OFF == result)
    {
        auto& deviceConfig = g_ptrSystem->DeviceConfig();
        deviceConfig.SetBrightness((int)deviceConfig.GetBrightness() - BRIGHTNESS_STEP);
        return;
    }
    else if (IR_BPLUS == result)
    {
        effectManager.ClearGlobalColor();
        effectManager.NextEffect();
        return;
    }
    else if (IR_BMINUS == result)
    {
        effectManager.ClearGlobalColor();
        effectManager.PreviousEffect();
        return;
    }
    else if (IR_SMOOTH == result)
    {
        effectManager.ClearGlobalColor();
        effectManager.SetInterval(EffectManager::csSmoothButtonSpeed);
    }
    else if (IR_STROBE == result)
    {
        effectManager.NextPalette();
    }
    else if (IR_FLASH == result)
    {
        effectManager.PreviousPalette();
    }
    else if (IR_FADE == result)
    {
        effectManager.ShowVU( !effectManager.IsVUVisible() );
    } else if (IR_BPLUS == result) {
        

    }

    
    for (int i = 0; i < ARRAYSIZE(RemoteColorCodes); i++) 
    {
        if (RemoteColorCodes[i].code == result)
        {
            debugV("Changing Color via remote: %08X\n", (uint) RemoteColorCodes[i].color);
                        effectManager.SetGlobalColor(RemoteColorCodes[i].color);
            return;
        }
    }
    */

#endif