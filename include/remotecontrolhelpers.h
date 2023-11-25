#pragma once
//#include "userremote.h"
#if ENABLE_REMOTE
CRGB hexToCRGB (String hexString) 
{
    //This function converts a hex code stored as a tring to a CRGB color object.
    //It should no longer require the helper function: hexStringToInt. I rewrot that function and then incorporated the logic into this function because it was so simple.
    CRGB myColor = CRGB(5,5,5);//The variable that we will return, with an arbitrary initial value.
    int rHexInt = 0;
    int bHexInt = 0;
    int gHexInt = 0;

    //We need to prpare the hex string for processing by removing any pound signs, spaces, and adding 0s if the string is less than 6 charactrs long.
    hexString.replace("#","");
    hexString.replace(" ","");
    if (hexString.length() < 6 && hexString.length() != 3)
    {
        while (hexString.length() < 6 ) {
            hexString += "0";
        }
    } 
    else if (hexString.length() == 3)
    {
        //Sometimes an RGB hex can be 3 charactrs. That is when each of the three colors consist of two values that are the same. EX: 00FFAA ir rendered 0FA.

        String r1 = hexString.substring(0,1);
        String g1 = hexString.substring(1,2);
        String b1 = hexString.substring(2,3);
        hexString = r1 + r1 + g1 + g1 + b1 + b1;//Ugly yet effective

    }

    String rHexString = hexString.substring(0,2);
    String gHexString = hexString.substring(2,4);
    String bHexString = hexString.substring(4,6);
    //debugI("Color we are sending to draw %s \n",hexString);
    
    if (rHexString.length() == 2 && gHexString.length() == 2 && bHexString.length() == 2 )
    {
        sscanf(rHexString.c_str(), "%x", &rHexInt);
        sscanf(gHexString.c_str(), "%x", &gHexInt); 
        sscanf(bHexString.c_str(), "%x", &bHexInt);
        //debugI("r is %i, g is %i, b is %i", rHexInt, gHexInt,bHexInt);
        myColor = CRGB (rHexInt,gHexInt,bHexInt);
    }
    return myColor;
}

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
        SMOOTH,
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

std::map<uint, RemoteButton> GetRemoteButtons()
{
     std::map<uint, RemoteButton> buttons
    {
        //Row 1
        {0xFF3AC5, {"Brightness Up",BRIGHTNESS_UP}},
        {0xFFBA45, {"Brightness Down",BRIGHTNESS_DOWN}},
        {0xFF827D, {"Next Effect",NEXT_EFFECT}},
        {0xFF02FD, {"Power Off",POWER_TOGGLE}},

        //Row 2
        {0xFF1AE5, {"Full Red",FILL_COLOR, "FF0000"}},
        {0xFF9A65, {"Full Green",FILL_COLOR, "00FF00"}},
        {0xFFA25D, {"Full Blue",FILL_COLOR, "0000FF"}},
        {0xFF22DD, {"Full White",FILL_COLOR, "FFFFFF"}},
        
        //Row 3
        {0xFF2AD5, {"Color 1",FILL_COLOR, "E18E28"}},
        {0xFFAA55, {"Color 2",FILL_COLOR, "1B9205"}},
        {0xFF926D, {"Color 3",FILL_COLOR, "170C96"}},
        {0xFF12ED, {"Color 4",FILL_COLOR, "F1BFDC"}},

        //Row 4
        {0xFF0AF5, {"Color 5",FILL_COLOR, "FBBE56"}},
        {0xFF8A75, {"Color 6",FILL_COLOR, "229248"}},
        {0xFFB24D, {"Color 7",FILL_COLOR, "200991"}},
        {0xFF32CD, {"Color 8",FILL_COLOR, "D72FB9"}},

        //Row 5
        {0xFF38C7, {"Color 9",FILL_COLOR, "EDD917"}},
        {0xFFB847, {"Color 10",FILL_COLOR, "2A92A1"}},
        {0xFF7887, {"Color 11",FILL_COLOR, "7415B4"}},
        {0xFFF807, {"Color 12",FILL_COLOR, "39AAC3"}},

        //Row 6
        {0xFF18E7, {"Color 13",FILL_COLOR, "D0E30F"}},
        {0xFF9867, {"Color 14",FILL_COLOR, "2E7CC7"}},
        {0xFF58A7, {"Color 15",FILL_COLOR, "C121B1"}},
        {0xFFD827, {"Color 16",FILL_COLOR, "2D87D7"}},

        // Remote with 7th row as JUMP3, JUMP7...

        //Row 7
        {0xFF28D7, {"Jump 3",JUMP3}},
        {0xFFA857, {"Jump 7",JUMP7}},
        {0xFF6897, {"Fade 3",FADE3}},
        {0xFFE817, {"Fade 7",FADE7}},

        //Row 8
        {0xFF08F7, {"Increase Red",CHANGER, "10"}},
        {0xFF8877, {"Increase Green",CHANGEG, "10"}},
        {0xFF48B7, {"Increase Blue",CHANGEB, "10"}},
        {0xFFC837, {"Quick",QUICK}},//fade speed is fast

        //Row 9
        {0xFF30CF, {"Descrease Red",CHANGER, "-10"}},
        {0xFFB04F, {"Descrease Green",CHANGEG, "-10"}},
        {0xFF708F, {"Decrease Blue",CHANGEB, "-10"}},
        {0xFFF00F, {"Slow",SLOW}},//fade speed is slow

        //Row 10
        {0xFF10EF, {"DIY 1",DIY1}},
        {0xFF906F, {"DIY 2",DIY2}},
        {0xFF50AF, {"DIY 3",DIY3}},
        {0xFFD02F, {"Auto",AUTO}},

        //Row 11
        {0xFF20DF, {"DIY 4",DIY4}},
        {0xFFA05F, {"DIY 5",DIY5}},
        {0xFF609F, {"DIY 6",DIY6}},
        {0xFFE01F, {"Flash",FLASH}}


        /*
        // Remote with 7th row as REDUP, GREENUP, ...
        //Row 7
        {0xFF28D7, {"Increase Red", CHANGER, "10"}},
        {0xFFA857, {"Increase Green", CHANGEG, "10"}},
        {0xFF6897, {"Increase Blue", CHANGEB, "10"}},
        {0xFFE817, {"Quick", QUICK}},

        //Row 8
        {0xFF08F7, {"Decrease Red",CHANGER, "-10"}},
        {0xFF8877, {"Decrease Green",CHANGEG, "-10"}},
        {0xFF48B7, {"Decrease Blue",CHANGEB, "-10"}},
        {0xFFC837, {"Slow", SLOW}},//fade speed is Slow

        //Row 9
        {0xFF30CF, {"DIY 1", DIY1}},
        {0xFFB04F, {"DIY 2", DIY2}},
        {0xFF708F, {"DIY 3", DIY3}},
        {0xFFF00F, {"Auto", AUTO}},

        //Row 10
        {0xFF10EF, {"DIY 4", DIY4}},
        {0xFF906F, {"DIY 5", DIY5}},
        {0xFF50AF, {"DIY 6", DIY6}},
        {0xFFD02F, {"Flash", FLASH}},

        //Row 11
        {0xFF20DF, {"Jump 3", JUMP3}},
        {0xFFA05F, {"Jump 7", JUMP7}},
        {0xFF609F, {"Fade 3", FADE3}},
        {0xFFE01F, {"Fade 7", FADE7}},
        */

        /*
        // 24 Key Remote Buttons
        //Row 1
        {0xF700FF, {"Brightness Up",BRIGHTNESS_UP}},
        {0xF7807F, {"Brightness Down",BRIGHTNESS_DOWN}},
        {0xF740BF, {"Off", POWER_OFF}},
        {0xF7C03F, {"Power On", NEXT_EFFECT}},

        //Row 2
        {0xF720DF, {"Full Red",FILL_COLOR, "FF0000"}},
        {0xF7A05F, {"Full Green",FILL_COLOR, "00FF00"}},
        {0xF7609F, {"Full Blue",FILL_COLOR, "0000FF"}},
        {0xF7E01F, {"Full White",FILL_COLOR, "AAAAAA"}}, //because we don't want FULL white

        //Row 3
        {0xF710EF, {"Color 1",FILL_COLOR, "E18E28"}},
        {0xF7906F, {"Color 2",FILL_COLOR, "1B9205"}},
        {0xF750AF, {"Color 3",FILL_COLOR, "170C96"}},
        {0xF7D02F, {"Auto", AUTO}},

        //Row 4
        {0xF730CF, {"Color 4",FILL_COLOR, "FBBE56"}},
        {0xF7B04F, {"Color 5",FILL_COLOR, "229248"}},
        {0xF7708F, {"Color 6",FILL_COLOR, "200991"}},
        {0xF7F00F, {"Strobe", STROBE}},

        //Row 5
        {0xF708F7, {"Color 7",FILL_COLOR, "EDD917"}},
        {0xF78877, {"Color 8",FILL_COLOR, "2A92A1"}},
        {0xF748B7, {"Color 9",FILL_COLOR, "7415B4"}},
        {0xF7C837, {"Fade", FADE}},

        //Row 6
        {0xFF18E7, {"Color 10",FILL_COLOR, "D0E30F"}},
        {0xFF9867, {"Color 11",FILL_COLOR, "2E7CC7"}},
        {0xFF58A7, {"Color 12",FILL_COLOR, "C121B1"}},
        {0xFFD827, {"Smooth", SMOOTH, "2D87D7"}}
        */
    };
    return buttons;
}
#endif