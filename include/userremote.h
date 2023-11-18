/*
This file contains items needed to load user defined remote controls.
Eventually this will include loading the data from preferences.
For now, we will hard code the items and let the user manually change.
*/

#include "globals.h"
#include "systemcontainer.h"

CRGB hexToCRGB (String hex);
//int hexStringToInt (String hexString);

enum ButtonActions
    {
        BRIGHTNESS_UP,
        BRIGHTNESS_DOWN,
        POWER_ON,
        POWER_OFF,
        POWER_TOGGLE,
        FILL_COLOR,
        TRIGGER_EFFECT,
        CHANGER,
        CHANGEG,
        CHANGEB,
        JUMP3,
        JUMP7,
        FADE, // Toggle between fade 3 and 7
        FADE3,
        FADE7,
        STROBE,
        AUTO,
        FLASH,
        QUICK,
        SLOW,
        DIY1,
        DIY2,
        DIY3,
        DIY4,
        DIY5,
        DIY6,
        SMOOTH, // Toggle between smooth transition or jump : i.e. transition speed
        NEXT_EFFECT,
        PREVIOUS_EFFECT,
        ENABLE_MUSIC,
        DISABLE_MUSIC,
        TOGGLE_MUSIC
    };

class RemoteButton
{
    public:
        String name;
        ButtonActions buttonAction;
        String actionArgs;
        RemoteButton (String _name, ButtonActions _buttonAction, String _actionArgs = "") 
        {
            name = _name;
            buttonAction = _buttonAction;
            actionArgs = _actionArgs;
        };
};

class UserRemoteControl 
    {
        public:
            void getRemoteButtons();
            int buttonCount;
            std::map<uint, RemoteButton> buttons;
            UserRemoteControl (int buttonCount = 0) 
            {
                buttonCount = buttonCount;
                getRemoteButtons(); //Loads default button configuration
            };
    };
