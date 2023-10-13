/*
This file contains items needed to load user defined remote controls.
Eventually this will include loading the data from preferences.
For now, we will hard code the items and let the user manually change.
*/

#include "globals.h"
#include "systemcontainer.h"

CRGB hexToCrgb (String hex);
int hexStringToInt (String hexString);

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
        NEXT_EFFECT,
        PREVIOUS_EFFECT,
        ENABLE_MUSIC,
        DISABLE_MUSIC,
        TOGGLE_MUSIC
    };



//We want to convert the remote button from a class to a struct
//https://www.w3schools.com/cpp/cpp_structs.asp
class RemoteButton
{
    //In this case a class is better than a struct. It alows creating the object with attributes defined using a single line of code.
    public:
        String name;
        //uint keyCode;
        ButtonActions buttonAction;
        String actionArgs;
        //RemoteButton (String _name, uint _keyCode, ButtonActions _buttonAction, String _actionArgs) 
        RemoteButton (String _name, ButtonActions _buttonAction, String _actionArgs = "") 
        {
            name = _name;
            buttonAction = _buttonAction;
            actionArgs = _actionArgs;
        };
};


class UserRemoteControl 
    {
        //We want to change the buttons vectory to a map. A map is an associative array type of structure: https://www.geeksforgeeks.org/associative-arrays-in-cpp/
        //The key for the button will be the remote key code

        public:
            //Eventually, the button type and / or button count will depend on a user setting / config file.
            //std::vector<RemoteButton> buttons {}; 
            //RemoteTypes remoteType;
            void getRemoteButtons();
            int buttonCount;
            //int currentBrightness = g_ptrSystem->DeviceConfig().GetBrightness();
            std::map<uint, RemoteButton> buttons;
            //UserRemoteControl (RemoteTypes remoteType, int buttonCount = 0) {
            UserRemoteControl (int buttonCount = 0) 
            {
                buttonCount = buttonCount;
                getRemoteButtons(); //Loads default button configuration
            };
    };
