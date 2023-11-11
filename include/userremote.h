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

struct UserRemoteButton 
{
        UserRemoteButton(String buttonName, ButtonActions action, String args) : name(buttonName), buttonAction(action), actionArgs(args) {}
        String name;
        ButtonActions buttonAction;
        String actionArgs;
};

struct category {
        category(int i, const std::string& n): id(i), name(n) {}
        int id;
        std::string name;
};

class UserRemoteControl 
    {
        public:
            void getRemoteButtons();
            void getRemoteButtonMap();
            int buttonCount;
            std::map<uint, RemoteButton> buttons;
            std::map<uint, UserRemoteButton> buttonMap;
            
            UserRemoteControl (int buttonCount = 0) 
            {
                buttonCount = buttonCount;
                getRemoteButtons(); //Loads default button configuration
            };
    };
