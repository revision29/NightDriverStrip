/*
This file contains items needed to load user defined remote controls.
Eventually this will include loading the data from preferences.
For now, we will hard code the items and let the user manually change.
*/
#pragma once

class UserRemoteControl 
{
    public:
        //std::map<uint, RemoteButton> buttons;
        
        UserRemoteControl()
        {
            /*
            //Row 1
        buttons.emplace(0xFF3AC5, RemoteButton("Brightness Up",BRIGHTNESS_UP));
        buttons.emplace(0xFFBA45, RemoteButton("Brightness Down",BRIGHTNESS_DOWN));
        buttons.emplace(0xFF827D, RemoteButton("Next Effect",NEXT_EFFECT));
        buttons.emplace(0xFF02FD, RemoteButton("Power Off",POWER_OFF));

        //Row 2
        buttons.emplace(0xFF1AE5, RemoteButton ("Full Red",FILL_COLOR, "FF0000"));
        buttons.emplace(0xFF9A65, RemoteButton ("Full Green",FILL_COLOR, "00FF00"));
        buttons.emplace(0xFFA25D, RemoteButton ("Full Blue",FILL_COLOR, "0000FF"));
        buttons.emplace(0xFF22DD, RemoteButton ("Full White",FILL_COLOR, "AAAAAA")); //because we don't want FULL white
        //Row 3
        buttons.emplace(0xFF2AD5, RemoteButton ("Color 1",FILL_COLOR, "E18E28"));
        buttons.emplace(0xFFAA55, RemoteButton ("Color 2",FILL_COLOR, "1B9205"));
        buttons.emplace(0xFF926D, RemoteButton ("Color 3",FILL_COLOR, "170C96"));
        buttons.emplace(0xFF12ED, RemoteButton ("Color 4",FILL_COLOR, "F1BFDC"));

        //Row 4
        buttons.emplace(0xFF0AF5, RemoteButton ("Color 5",FILL_COLOR, "FBBE56"));
        buttons.emplace(0xFF8A75, RemoteButton ("Color 6",FILL_COLOR, "229248"));
        buttons.emplace(0xFFB24D, RemoteButton ("Color 7",FILL_COLOR, "200991"));
        buttons.emplace(0xFF32CD, RemoteButton ("Color 8",FILL_COLOR, "D72FB9"));

        //Row 5
        buttons.emplace(0xFF38C7, RemoteButton ("Color 9",FILL_COLOR, "EDD917"));
        buttons.emplace(0xFFB847, RemoteButton ("Color 10",FILL_COLOR, "2A92A1"));
        buttons.emplace(0xFF7887, RemoteButton ("Color 11",FILL_COLOR, "7415B4"));
        buttons.emplace(0xFFF807, RemoteButton ("Color 12",FILL_COLOR, "39AAC3"));

        //Row 6
        buttons.emplace(0xFF18E7, RemoteButton ("Color 13",FILL_COLOR, "D0E30F"));
        buttons.emplace(0xFF9867, RemoteButton ("Color 14",FILL_COLOR, "2E7CC7"));
        buttons.emplace(0xFF58A7, RemoteButton ("Color 15",FILL_COLOR, "C121B1"));
        buttons.emplace(0xFFD827, RemoteButton ("Color 16",FILL_COLOR, "2D87D7"));

        // Remote with 7th row as JUMP3, JUMP7...
        
        //Row 7
        buttons.emplace(0xFF28D7, RemoteButton ("Jump 3",JUMP3));
        buttons.emplace(0xFFA857, RemoteButton ("Jump 7",JUMP7));
        buttons.emplace(0xFF6897, RemoteButton ("Fade 3",FADE3));
        buttons.emplace(0xFFE817, RemoteButton ("Fade 7",FADE7));

        //Row 8
        buttons.emplace(0xFF08F7, RemoteButton ("Increase Red",CHANGER, "10"));
        buttons.emplace(0xFF8877, RemoteButton ("Increase Green",CHANGEG, "10"));
        buttons.emplace(0xFF48B7, RemoteButton ("Increase Blue",CHANGEB, "10"));
        buttons.emplace(0xFFC837, RemoteButton ("Quick",QUICK));//fade speed is fast

        //Row 9
        buttons.emplace(0xFF30CF, RemoteButton ("Descrease Red",CHANGER, "-10"));
        buttons.emplace(0xFFB04F, RemoteButton ("Descrease Green",CHANGEG, "-10"));
        buttons.emplace(0xFF708F, RemoteButton ("Decrease Blue",CHANGEB, "-10"));
        buttons.emplace(0xFFF00F, RemoteButton ("Slow",SLOW));//fade speed is slow

        //Row 10
        buttons.emplace(0xFF10EF, RemoteButton ("DIY 1",DIY1));
        buttons.emplace(0xFF906F, RemoteButton ("DIY 2",DIY2));
        buttons.emplace(0xFF50AF, RemoteButton ("DIY 3",DIY3));
        buttons.emplace(0xFFD02F, RemoteButton ("Auto",AUTO));

        //Row 11
        buttons.emplace(0xFF20DF, RemoteButton ("DIY 4",DIY4));
        buttons.emplace(0xFFA05F, RemoteButton ("DIY 5",DIY5));
        buttons.emplace(0xFF609F, RemoteButton ("DIY 6",DIY6));
        buttons.emplace(0xFFE01F, RemoteButton ("Flash",FLASH));
        */
        

    /*
        // Remote with 7th row as REDUP, GREENUP, ...
        //Row 7
        buttons.emplace(0xFF28D7, RemoteButton ("Increase Red", CHANGER, "10"));
        buttons.emplace(0xFFA857, RemoteButton ("Increase Green", CHANGEG, "10"));
        buttons.emplace(0xFF6897, RemoteButton ("Increase Blue", CHANGEB, "10"));
        buttons.emplace(0xFFE817, RemoteButton ("Quick", QUICK));

        //Row 8
        buttons.emplace(0xFF08F7, RemoteButton ("Decrease Red",CHANGER, "-10"));
        buttons.emplace(0xFF8877, RemoteButton ("Decrease Green",CHANGEG, "-10"));
        buttons.emplace(0xFF48B7, RemoteButton ("Decrease Blue",CHANGEB, "-10"));
        buttons.emplace(0xFFC837, RemoteButton ("Slow", SLOW));//fade speed is Slow

        //Row 9
        buttons.emplace(0xFF30CF, RemoteButton ("DIY 1", DIY1));
        buttons.emplace(0xFFB04F, RemoteButton ("DIY 2", DIY2));
        buttons.emplace(0xFF708F, RemoteButton ("DIY 3", DIY3));
        buttons.emplace(0xFFF00F, RemoteButton ("Auto", AUTO));

        //Row 10
        buttons.emplace(0xFF10EF, RemoteButton ("DIY 4", DIY4));
        buttons.emplace(0xFF906F, RemoteButton ("DIY 5", DIY5));
        buttons.emplace(0xFF50AF, RemoteButton ("DIY 6", DIY6));
        buttons.emplace(0xFFD02F, RemoteButton ("Flash", FLASH));

        //Row 11
        buttons.emplace(0xFF20DF, RemoteButton ("Jump 3", JUMP3));
        buttons.emplace(0xFFA05F, RemoteButton ("Jump 7", JUMP7));
        buttons.emplace(0xFF609F, RemoteButton ("Fade 3", FADE3));
        buttons.emplace(0xFFE01F, RemoteButton ("Fade 7", FADE7));
    */

/*
        // 24 Key Remote Buttons
        //Row 1
        buttons.emplace(0xF700FF, RemoteButton("Brightness Up",BRIGHTNESS_UP));
        buttons.emplace(0xF7807F, RemoteButton("Brightness Down",BRIGHTNESS_DOWN));
        buttons.emplace(0xF740BF, RemoteButton("Off", POWER_OFF));
        buttons.emplace(0xF7C03F, RemoteButton("Power On", NEXT_EFFECT));

        //Row 2
        buttons.emplace(0xF720DF, RemoteButton ("Full Red",FILL_COLOR, "FF0000"));
        buttons.emplace(0xF7A05F, RemoteButton ("Full Green",FILL_COLOR, "00FF00"));
        buttons.emplace(0xF7609F, RemoteButton ("Full Blue",FILL_COLOR, "0000FF"));
        buttons.emplace(0xF7E01F, RemoteButton ("Full White",FILL_COLOR, "AAAAAA")); //because we don't want FULL white
        
        //Row 3
        buttons.emplace(0xF710EF, RemoteButton ("Color 1",FILL_COLOR, "E18E28"));
        buttons.emplace(0xF7906F, RemoteButton ("Color 2",FILL_COLOR, "1B9205"));
        buttons.emplace(0xF750AF, RemoteButton ("Color 3",FILL_COLOR, "170C96"));
        buttons.emplace(0xF7D02F, RemoteButton ("Auto", AUTO));

        //Row 4
        buttons.emplace(0xF730CF, RemoteButton ("Color 4",FILL_COLOR, "FBBE56"));
        buttons.emplace(0xF7B04F, RemoteButton ("Color 5",FILL_COLOR, "229248"));
        buttons.emplace(0xF7708F, RemoteButton ("Color 6",FILL_COLOR, "200991"));
        buttons.emplace(0xF7F00F, RemoteButton ("Strobe", STROBE));

        //Row 5
        buttons.emplace(0xF708F7, RemoteButton ("Color 7",FILL_COLOR, "EDD917"));
        buttons.emplace(0xF78877, RemoteButton ("Color 8",FILL_COLOR, "2A92A1"));
        buttons.emplace(0xF748B7, RemoteButton ("Color 9",FILL_COLOR, "7415B4"));
        buttons.emplace(0xF7C837, RemoteButton ("Fade", FADE));
        
        //Row 6
        buttons.emplace(0xFF18E7, RemoteButton ("Color 10",FILL_COLOR, "D0E30F"));
        buttons.emplace(0xFF9867, RemoteButton ("Color 11",FILL_COLOR, "2E7CC7"));
        buttons.emplace(0xFF58A7, RemoteButton ("Color 12",FILL_COLOR, "C121B1"));
        buttons.emplace(0xFFD827, RemoteButton ("Smooth", SMOOTH, "2D87D7"));
        */
        debugI("Creating user remote control.\n");
        }
};
