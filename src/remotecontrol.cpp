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

#define BRIGHTNESS_STEP     20

UserRemoteControl myRemoteController (44);

//Repeat codes
//Press and hold brightness up or down to wuickly adjust up. 
//Otherwise acknolwedge the keypress only every 200ms or.
//First check for a match. If no metch we just return.
//If a match then we check against repeating then we trigger the button action

void RemoteControl::handle()
{
    decode_results results;
    static int lastResult = 0;

    static CRGB lastManualColor = CRGB(0,0,0);

    auto& deviceConfig = g_ptrSystem->DeviceConfig();

    if (!_IR_Receive.decode(&results))
        return;

    int result = results.value;
    _IR_Receive.resume();

auto searchResult = myRemoteController.buttons.find(result);
    if (searchResult != myRemoteController.buttons.end()) 
    {
        debugI("We have a remote code result %08x", result);
        uint buttonCount = myRemoteController.buttons.size();
        debugI("There are %i buttons in the remote", buttonCount);
        RemoteButton thisButton =  searchResult->second;
        //Check for repeat
        //myRemoteController.buttons[result]
        /*
        if (result == lastResult) 
        {
            static uint lastRepeatTime = millis();
            const auto kMinRepeatms = (myRemoteController.buttons[result].buttonAction == BRIGHTNESS_DOWN || myRemoteController.buttons[result].buttonAction == BRIGHTNESS_UP) ? 150 : 250;
            //We do not want to set the kMinRepeatms to 0 because some remotes send a code more than once and also there might be refelctive surfaces that will cause the signal to be recieved more than once in rapid succession.
            //250 will allow 4 units brightness changes over one second. That will be about 3 seconds to fully ramp the brightnss up or down
            if (millis() - lastRepeatTime > kMinRepeatms)
            {
                debugV("Remote Repeat; lastResult == %08x, elapsed = %lu\n", lastResult, millis()-lastRepeatTime);
                lastRepeatTime = millis();
            }
            else
            {
                return;
            }   

        }
        lastResult = result;

        //Process the code
        auto &effectManager = g_ptrSystem->EffectManager();
        
        auto &myEffect = effectManager.GetCurrentEffect();
        

        //As we create the switch, if we need to use variables inside the case, we enclose the case code in curley brackets
        //    case TRIGGER_EFFECT:
        //    {
        //        //We can initialize variables here, including an array of the arguments passed to the effect
        //    }
        
       switch (thisButton.buttonAction)
       {
            case BRIGHTNESS_UP:
               deviceConfig.SetBrightness((int)deviceConfig.GetBrightness() + BRIGHTNESS_STEP);

            break;
            case BRIGHTNESS_DOWN:
                deviceConfig.SetBrightness((int)deviceConfig.GetBrightness() - BRIGHTNESS_STEP);
                debugI("After brightness down global brightness is  %i\n",deviceConfig.GetBrightness());

            break;
            case POWER_ON:
                effectManager.ClearRemoteColor();
                effectManager.SetInterval(0);
                effectManager.SetGlobalColor(lastManualColor);
                effectManager.StartEffect();
            break;
            case POWER_OFF:
                //effectManager.SetGlobalColor(CRGB(0,0,0));
                //g_Values.Brightness = std::max(0, (int) g_Values.Brightness - BRIGHTNESS_STEP);
                effectManager.ClearRemoteColor();
            break;
            case NEXT_EFFECT: 
                effectManager.NextEffect();
            break;
            case FILL_COLOR:
                lastManualColor = hexToCrgb(thisButton.actionArgs);
                lastManualColor.maximizeBrightness(myRemoteController.currentBrightness);
                effectManager.SetGlobalColor(lastManualColor); 
                //debugI("Current FastLED brightness %i\n",FastLED.getBrightness());
                effectManager.SetInterval(0);
            break;
            
            case TRIGGER_EFFECT:
            
            break;
            case CHANGER:
                if (lastManualColor.red + thisButton.actionArgs.toInt() > 255 ) {
                    lastManualColor.red = 255;
                } else if (lastManualColor.red + thisButton.actionArgs.toInt() < 0) {
                    lastManualColor.red = 0;
                } else {
                    lastManualColor.red += thisButton.actionArgs.toInt();
                }
                effectManager.SetGlobalColor(lastManualColor); 
                effectManager.SetInterval(0);

            break;
            case CHANGEG:
                if (lastManualColor.green + thisButton.actionArgs.toInt() > 255 ) {
                    lastManualColor.green = 255;
                } else if (lastManualColor.green + thisButton.actionArgs.toInt() < 0) {
                    lastManualColor.green = 0;
                } else {
                    lastManualColor.green += thisButton.actionArgs.toInt();
                }
                effectManager.SetGlobalColor(lastManualColor);
                effectManager.SetInterval(0);
            break;
            case CHANGEB:
                if (lastManualColor.blue + thisButton.actionArgs.toInt() > 255 ) {
                    lastManualColor.blue = 255;
                } else if (lastManualColor.blue + thisButton.actionArgs.toInt() < 0) {
                    lastManualColor.blue = 0;
                } else {
                    lastManualColor.blue += thisButton.actionArgs.toInt();
                }
                effectManager.SetGlobalColor(lastManualColor); 
                effectManager.SetInterval(0);
            break;
            case DIY1:
               effectManager.NextEffect();
            break;
            case DIY2: 
                effectManager.PreviousEffect();
                
                
            break;
            case DIY3: 
                
            break;
            case DIY4: 
                
            break;

            //case JUMP3:
            //break;
            //case JUMP7:
            //break;
            //case FADE3:
            //break;
            //case FADE7:
            //break;
            //case STROBE:
            //break;
            //case AUTO:
            //break;
            //case FLASH:
            //break;
            //case QUICK:
            //break;
            //case SLOW:
            //break;
       }
  */

    }
    else
    {
        //There was no result, so just return.
        debugI("We do not have a remote code result %08x", result);
        return;
    }
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
        effectManager.ClearRemoteColor();
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
        effectManager.ClearRemoteColor();
        effectManager.NextEffect();
        return;
    }
    else if (IR_BMINUS == result)
    {
        effectManager.ClearRemoteColor();
        effectManager.PreviousEffect();
        return;
    }
    else if (IR_SMOOTH == result)
    {
        effectManager.ClearRemoteColor();
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
}
*/

#endif