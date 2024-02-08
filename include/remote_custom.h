#include "globals.h"

#if ENABLE_REMOTE

#include "systemcontainer.h"
#include "remote_custom_helpers.h"
//#include "userremote.h"

/*
To get this to work, wrap the existing remote code in the followig code

#if __has_include ("custom_remote.h")
      #include "custom_remote.h"
#else
//Existing code
#endif
*/

// Include any effects you will directly trigger with the remote.
#include "effects/strip/misceffects.h"
#include "effects/strip/paletteeffect.h"

void RemoteControl::handle()
{
    decode_results results;
    auto &deviceConfig = g_ptrSystem->DeviceConfig();
    
    //static std::map<uint, RemoteButton> buttons = GetRemoteButtons(); // Defined in remotecontrolhelpers.h.
    //static UserRemoteControl myRemoteController = UserRemoteControl();//Loads remote and user defined buttons
    static uint lastResult = 0;
    static uint lastProcessTime = millis();
    static int currentBrightness = deviceConfig.GetBrightness();
    static uint currentEffectInterval = g_ptrSystem->EffectManager().GetInterval();
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
                    effectManager.ClearTempEffect();
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
                    effectManager.ClearTempEffect();
                }
            break;
            case NEXT_EFFECT: 
            {
                if(effectManager.HasTempEffect())
                    effectManager.ClearTempEffect();
                else
                    effectManager.NextEffect();
            }
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
                    debugI("we have a button color with r value of %i\n", button.color.r);
                    effectManager.ApplyGlobalColor(button.color); 
                    
                }
                else
                {
                    debugI("we have a button arg");
                    CRGB fillColor = hexToCRGB(button.actionArgs);
                    effectManager.ApplyGlobalColor(fillColor);
                    
                }
                //auto effect = make_shared_psram<ColorFillEffect>(deviceConfig.GlobalColor());
                //effectManager.SetTempEffect(effect);

                //to be repalced by: 
                /*
                effectManager.ApplyGlobalColor(fillColor);
                */
            }
            break;
            
            case TRIGGER_EFFECT:
                {
                    auto effect = make_shared_psram<ColorFillEffect>(CRGB::Yellow, 1, true);
                    effectManager.SetTempEffect(effect);
                }
                
            break;
            case CHANGER: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GlobalColor();
                    tempColor.red += button.actionArgs.toInt();
                    effectManager.ApplyGlobalColor(tempColor);
                }
            break;
            case CHANGEG: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GlobalColor();
                    tempColor.green += button.actionArgs.toInt();
                    effectManager.ApplyGlobalColor(tempColor);
                }
                    
            break;
            case CHANGEB: // The button can send a positive or negative value to adjust the color.
                {
                    CRGB tempColor = g_ptrSystem->DeviceConfig().GlobalColor();
                    tempColor.blue += button.actionArgs.toInt();
                    effectManager.ApplyGlobalColor(tempColor); 
                }
            break;
            case DIY1:
                debugI("DIY 1 pressed. Effect count is %i\n", effectManager.EffectCount());
                effectManager.SetCurrentEffectIndex(0);
                
                
            break;
            case DIY2: 
            {
                debugI("DIY 2 pressed. Effect count is %i\n", effectManager.EffectCount());
                if (effectManager.EffectCount() > 1)
                    effectManager.SetCurrentEffectIndex(1);
            }
                
            break;
            case DIY3: 
            {
                debugI("DIY 3 pressed. Effect count is %i\n", effectManager.EffectCount());
                if (effectManager.EffectCount() > 2)
                    effectManager.SetCurrentEffectIndex(2);
            }
            break;
            case DIY4: 
            {
                debugI("DIY 4 pressed. Effect count is %i\n", effectManager.EffectCount());
                if (effectManager.EffectCount() > 3)
                    effectManager.SetCurrentEffectIndex(3);
            }

            break;
            case DIY5: 
            {
                debugI("DIY 5 pressed. Effect count is %i\n", effectManager.EffectCount());
                if (effectManager.EffectCount() > 4)
                    effectManager.SetCurrentEffectIndex(4);
            }
            
            break;
            case DIY6: 
            {
                debugI("DIY 6 pressed. Effect count is %i\n", effectManager.EffectCount());
                if (effectManager.EffectCount() > 5)
                    effectManager.SetCurrentEffectIndex(5);
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
            case FADE3:
            {
                auto tempEffect = make_shared_psram<PaletteEffect>(CRGBPalette16(CRGB::Blue, CRGB::Red, CRGB::Blue), 32, .1, 0, NUM_LEDS, 0, NOBLEND, false); // Someone called the cops.
                effectManager.SetTempEffect(tempEffect);
            }
            break;
            //case FADE7:
            //break;
            //case STROBE:
            //break;
            case AUTO_SCROLL:
            {
                debugI("we have the auto scroll button");
                
                if (effectManager.GetInterval() == 0)
                {
                    debugI("effect interval is 0");
                    effectManager.SetInterval(currentEffectInterval != 0 ? currentEffectInterval : (DEFAULT_EFFECT_INTERVAL != 0 ? DEFAULT_EFFECT_INTERVAL : 30000));
                    debugI("we set interval to %i", effectManager.GetInterval());
                    effectManager.NextEffect();
                } 
                else 
                {
                    currentEffectInterval = effectManager.GetInterval();
                    effectManager.SetInterval(0);
                    uint8_t tempBrightness = deviceConfig.GetBrightness();
                    deviceConfig.SetBrightness(tempBrightness/5);
                    //sleep(200);
                    usleep(250000);
    
                    deviceConfig.SetBrightness(tempBrightness);
                    
                    //deviceConfig.SetBrightness(deviceConfig.GetBrightness()/2);
                    //sleep(200);
                    //deviceConfig.SetBrightness(deviceConfig.GetBrightness() + deviceConfig.GetBrightness());
                    debugI("effect interval is not 0");
                    debugI("we set interval to 0");
                }

/*
                if (currentEffectInterval != (DEFAULT_EFFECT_INTERVAL != 0 ? DEFAULT_EFFECT_INTERVAL : currentEffectInterval)) 
                {
                    //debugI("Setting interval to 30 seconds\n");
                    // effectManager.ClearRemoteColor(); // To be uncommented when on current codebase
                    effectManager.SetInterval(DEFAULT_EFFECT_INTERVAL != 0 ? DEFAULT_EFFECT_INTERVAL : 15000, true);
                    effectManager.NextEffect();
                } 
                else
                {
                    currentEffectInterval = effectManager.GetInterval();
                    //debugI("Setting interval to 0 seconds\n");
                    effectManager.SetInterval(0);
                    int tempBrightness = deviceConfig.GetBrightness();
                    deviceConfig.SetBrightness(tempBrightness/2);
                    sleep(200);
                    deviceConfig.SetBrightness(tempBrightness);
                }
                */
            }
            break;
            case FLASH:
            {
                if (deviceConfig.ApplyGlobalColors())
                    deviceConfig.ClearApplyGlobalColors();
                else
                    deviceConfig.SetApplyGlobalColors();
            }
            break;
            case QUICK:
                effectManager.SetInterval(15000);
                deviceConfig.SetBrightness(deviceConfig.GetBrightness()/5);
                usleep(250000);
                deviceConfig.SetBrightness(deviceConfig.GetBrightness()*5);
            break;
            case SLOW:
                effectManager.SetInterval(30000);
                deviceConfig.SetBrightness(deviceConfig.GetBrightness()/5);
                usleep(250000);
                deviceConfig.SetBrightness(deviceConfig.GetBrightness()*5);
            break;
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