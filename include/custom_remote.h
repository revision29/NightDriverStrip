#include "globals.h"

#if ENABLE_REMOTE

#include "systemcontainer.h"
#include "custom_remote_helpers.h"
//#include "userremote.h"

// Include any effects you will directly trigger with the remote.
#include "effects/strip/misceffects.h"
#include "effects/strip/paletteeffect.h"


#define BRIGHTNESS_STEP     20

void RemoteControl::handle()
{
    decode_results results;
    auto &deviceConfig = g_ptrSystem->DeviceConfig();
    
    //static std::map<uint, RemoteButton> buttons = GetRemoteButtons(); // Defined in remotecontrolhelpers.h.
    //static UserRemoteControl myRemoteController = UserRemoteControl();//Loads remote and user defined buttons
    static uint lastResult = 0;
    static uint lastProcessTime = millis();
    static int currentBrightness = deviceConfig.GetBrightness();
    
    static boolean remotePower = true;
    
    if (!_IR_Receive.decode(&results))
        return;

    uint result = results.value;
    debugI("start of IR handle time: %i", millis());
    debugI("received Remote Code");
    debugI("Remote code %08x", result);
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
    debugI("about to search buttons");
    auto searchResult = remoteButtons.find(result);
    if (searchResult != remoteButtons.end()) 
    {

        debugI("we have a button match");
        RemoteButton button = searchResult->second;
        if (result == lastResult) 
        {
            static uint lastRepeatTime = millis();
            auto kMinRepeatms = (button.buttonAction == BRIGHTNESS_DOWN || button.buttonAction == BRIGHTNESS_UP) ? 150 : 300;

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
        
        switch (button.buttonAction)
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
            }
            case ButtonActions::POWER_ON:
                //effectManager.SetInterval(0);
                //effectManager.SetTemporaryStripEffect(make_shared_psram<ColorFillEffect>(lastManualColor, 1));
                //effectManager.StartEffect();
                {
                    
                }
            break;
            case POWER_OFF:
                //effectManager.ClearTemporaryStripEffect();
                //effectManager.ClearGlobalColor();
                {
                    currentBrightness = deviceConfig.GetBrightness() == 0 ? 127 :  deviceConfig.GetBrightness();
                    deviceConfig.SetBrightness(0);
                    effectManager.ClearTemporaryEffect();
                }
            break;
            case NEXT_EFFECT: 
                effectManager.NextEffect();
                // Soon to be implemented with fresh codebase
                /*
                if (deviceConfig.ApplyGlobalColors())
                    effectManager.ClearRemoteColor();
                else
                    effectManager.NextEffect();
                return;
                */
            break;
            case FILL_COLOR:
            {
                if (button.color)
                {
                    effectManager.SetGlobalColor(button.color); 
                }
                else
                {
                    CRGB fillColor = hexToCRGB(button.actionArgs);
                    effectManager.SetGlobalColor(fillColor);
                }
                //to be repalced by: 
                /*
                effectManager.ApplyGlobalColor(fillColor);
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
                    tempColor.red += button.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor);
                }
            break;
            case CHANGEG: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GetGlobalColor();
                    tempColor.green += button.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor);
                }
                    
            break;
            case CHANGEB: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GetGlobalColor();
                    tempColor.blue += button.actionArgs.toInt();
                    effectManager.SetGlobalColor(tempColor); 
                }
            break;
            case DIY1:
                debugI("DIY 1 pressed. Effect count is %i\n", effectManager.EffectCount());
                effectManager.SetCurrentEffectIndex(0);
                
                
            break;
            case DIY2: 
            {
                debugI("DIY 2 pressed. Effect count is %i\n", effectManager.EffectCount());
                //if (effectManager.EffectCount() > 1)
                //    effectManager.SetCurrentEffectIndex(1);
            }
                
            break;
            case DIY3: 
            {
                debugI("DIY 3 pressed. Effect count is %i\n", effectManager.EffectCount());
                //if (effectManager.EffectCount() > 2)
                //    effectManager.SetCurrentEffectIndex(2);
            }
            break;
            case DIY4: 
            {
                debugI("DIY 4 pressed. Effect count is %i\n", effectManager.EffectCount());
                //if (effectManager.EffectCount() > 3)
                //    effectManager.SetCurrentEffectIndex(3);
            }

            break;
            case DIY5: 
            {
                debugI("DIY 5 pressed. Effect count is %i\n", effectManager.EffectCount());
                //if (effectManager.EffectCount() > 4)
                 //   effectManager.SetCurrentEffectIndex(4);
            }
            
            break;
            case DIY6: 
            {
                debugI("DIY 6 pressed. Effect count is %i\n", effectManager.EffectCount());
                //if (effectManager.EffectCount() > 5)
                    //effectManager.SetCurrentEffectIndex(5);
            }
            break;
            
            // There are effects defined that will scroll throw different effects.
            case JUMP3:
            {
            // Fade speed is 0
            // 3 colors

                //ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB::Blue, CRGB::MediumPurple, CRGB::Azure), 256 / 32, .3, 0,4,0);
                //auto effect = make_shared_psram<PaletteEffect>(CRGBPalette16(CRGB::Blue, CRGB::MediumPurple, CRGB::Azure), 256 / 32, .3, 0,4,0);
                //effectManager.SetTemporaryEffect(effect); //This method (and ) needs to be added to the upstream codebase
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
            case AUTO_SCROLL:
            {
                if (effectManager.GetInterval() != (DEFAULT_EFFECT_INTERVAL != 0 ? DEFAULT_EFFECT_INTERVAL : 3000)) 
                {
                    //debugI("Setting interval to 30 seconds\n");
                    // effectManager.ClearRemoteColor(); // To be uncommented when on current codebase
                    effectManager.SetInterval(DEFAULT_EFFECT_INTERVAL != 0 ? DEFAULT_EFFECT_INTERVAL : 3000, true);
                    effectManager.NextEffect();
                } 
                else
                {
                    //debugI("Setting interval to 0 seconds\n");
                    effectManager.SetInterval(0);
                    int tempBrightness = deviceConfig.GetBrightness();
                    deviceConfig.SetBrightness(tempBrightness/2);
                    sleep(200);
                    deviceConfig.SetBrightness(tempBrightness);

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
        debugI("We do not have a remote code result 0X%08X", result);
    }
    if (result != 0xFFFFFFFF )
        lastResult = result;
    //processingRemoteButtonPress = false;
    debugI("end of IR handle time: %i", millis());
}

#endif