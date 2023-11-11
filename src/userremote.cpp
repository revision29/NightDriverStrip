#include "globals.h"

#if ENABLE_REMOTE

void UserRemoteControl::getRemoteButtons() {
    
    //This populates the remote control buttons
    
    /*
    The ButtonActions ENUM in userremote.h defines what actions are available.

    Here, buttons are being added to the "buttons" std::map using the emplace method. This allows the button to be added to the map with a single line.
    The first argument is the key which. The value for key is the hex code for the IR button.
    The second argument is the value. In this case the value is a RemoteButton object that we are creating in line.
    
    The remote button object takes three arguments. A label, button action (as defined in the ButtonActions enum), and action arguments (optional).
    Some of the actions require an argument (FILL_COLOR or example), while others do not (such as BRIGHTNESS_UP).
    If an action requires miltuple arguments, those will be formatted in a single string where each argument value is seperated by a comma. Example: "1,String Phrase,25". 
    Your code for the action in remotecontrol.cpp will need to be able to parse the action arguments string and pass the arguments along as you desire. It's up to you to make that happen.
    */

    // This is for a 44 key remote. There is a set of definitions below for a 24 key remote.
    // To disable the 44 button definitions use a block comment (slash-star) or comment out each line.
    // To enable the 24 button definitions, uncomment the 23 key definition block.
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

}



/*
int hexStringToInt (String hexString)
    {
        //This function is used to a convert hex code stored into a string to an integer reprsenting the value of the hex code if it were a true hex code.

        //string hexString = "7FF";
        int hexNumber = 0;
        sscanf(hexString.c_str(), "%x", &hexNumber);
        return hexNumber;
    }
*/

void UserRemoteControl::getRemoteButtonMap() {

        
    //This populates the remote control buttons
    
    /*
    The ButtonActions ENUM in userremote.h defines what actions are available.

    Here, buttons are being added to the "buttons" std::map using the emplace method. This allows the button to be added to the map with a single line.
    The first argument is the key which. The value for key is the hex code for the IR button.
    The second argument is the value. In this case the value is a UserRemoteButton object that we are creating in line.
    
    The remote button object takes three arguments. A label, button action (as defined in the ButtonActions enum), and action arguments (optional).
    Some of the actions require an argument (FILL_COLOR or example), while others do not (such as BRIGHTNESS_UP).
    If an action requires miltuple arguments, those will be formatted in a single string where each argument value is seperated by a comma. Example: "1,String Phrase,25". 
    Your code for the action in remotecontrol.cpp will need to be able to parse the action arguments string and pass the arguments along as you desire. It's up to you to make that happen.
    */

    // This is for a 44 key remote. There is a set of definitions below for a 24 key remote.
    // To disable the 44 button definitions use a block comment (slash-star) or comment out each line.
    // To enable the 24 button definitions, uncomment the 23 key definition block.
    /*
    //Row 1
    buttonMap.emplace(0xFF3AC5, {"Brightness Up",BRIGHTNESS_UP, ""});
    buttonMap.emplace(0xFFBA45, {"Brightness Down",BRIGHTNESS_DOWN, ""});
    buttonMap.emplace(0xFF827D, {"Next Effect",NEXT_EFFECT, ""});
    buttonMap.emplace(0xFF02FD, {"Power Off",POWER_OFF, ""});

    //Row 2
    buttonMap.emplace(0xFF1AE5, {"Full Red",FILL_COLOR, "FF0000"});
    buttonMap.emplace(0xFF9A65, {"Full Green",FILL_COLOR, "00FF00"});
    buttonMap.emplace(0xFFA25D, {"Full Blue",FILL_COLOR, "0000FF"});
    buttonMap.emplace(0xFF22DD, {"Full White",FILL_COLOR, "AAAAAA"}); //because we don't want FULL white
    //Row 3
    buttonMap.emplace(0xFF2AD5, {"Color 1",FILL_COLOR, "E18E28"});
    buttonMap.emplace(0xFFAA55, {"Color 2",FILL_COLOR, "1B9205"});
    buttonMap.emplace(0xFF926D, {"Color 3",FILL_COLOR, "170C96"});
    buttonMap.emplace(0xFF12ED, {"Color 4",FILL_COLOR, "F1BFDC"});

    //Row 4
    buttonMap.emplace(0xFF0AF5, {"Color 5",FILL_COLOR, "FBBE56"});
    buttonMap.emplace(0xFF8A75, {"Color 6",FILL_COLOR, "229248"});
    buttonMap.emplace(0xFFB24D, {"Color 7",FILL_COLOR, "200991"});
    buttonMap.emplace(0xFF32CD, {"Color 8",FILL_COLOR, "D72FB9"});

    //Row 5
    buttonMap.emplace(0xFF38C7, {"Color 9",FILL_COLOR, "EDD917"});
    buttonMap.emplace(0xFFB847, {"Color 10",FILL_COLOR, "2A92A1"});
    buttonMap.emplace(0xFF7887, {"Color 11",FILL_COLOR, "7415B4"});
    buttonMap.emplace(0xFFF807, {"Color 12",FILL_COLOR, "39AAC3"});

    //Row 6
    buttonMap.emplace(0xFF18E7, {"Color 13",FILL_COLOR, "D0E30F"});
    buttonMap.emplace(0xFF9867, {"Color 14",FILL_COLOR, "2E7CC7"});
    buttonMap.emplace(0xFF58A7, {"Color 15",FILL_COLOR, "C121B1"});
    buttonMap.emplace(0xFFD827, {"Color 16",FILL_COLOR, "2D87D7"});

    // Remote with 7th row as JUMP3, JUMP7...
    
    //Row 7
    buttonMap.emplace(0xFF28D7, {"Jump 3",JUMP3, ""});
    buttonMap.emplace(0xFFA857, {"Jump 7",JUMP7, ""});
    buttonMap.emplace(0xFF6897, {"Fade 3",FADE3, ""});
    buttonMap.emplace(0xFFE817, {"Fade 7",FADE7, ""});

    //Row 8
    buttonMap.emplace(0xFF08F7, {"Increase Red",CHANGER, "10"});
    buttonMap.emplace(0xFF8877, {"Increase Green",CHANGEG, "10"});
    buttonMap.emplace(0xFF48B7, {"Increase Blue",CHANGEB, "10"});
    buttonMap.emplace(0xFFC837, {"Quick",QUICK, ""});//fade speed is fast

    //Row 9
    buttonMap.emplace(0xFF30CF, {"Descrease Red",CHANGER, "-10"});
    buttonMap.emplace(0xFFB04F, {"Descrease Green",CHANGEG, "-10"});
    buttonMap.emplace(0xFF708F, {"Decrease Blue",CHANGEB, "-10"});
    buttonMap.emplace(0xFFF00F, {"Slow",SLOW});//fade speed is slow

    //Row 10
    buttonMap.emplace(0xFF10EF, {"DIY 1",DIY1, ""});
    buttonMap.emplace(0xFF906F, {"DIY 2",DIY2, ""});
    buttonMap.emplace(0xFF50AF, {"DIY 3",DIY3, ""});
    buttonMap.emplace(0xFFD02F, {"Auto",AUTO, ""});

    //Row 11
    buttonMap.emplace(0xFF20DF, {"DIY 4",DIY4, ""});
    buttonMap.emplace(0xFFA05F, {"DIY 5",DIY5, ""});
    buttonMap.emplace(0xFF609F, {"DIY 6",DIY6, ""});
    buttonMap.emplace(0xFFE01F, {"Flash",FLASH, ""});
    */

/*
    // Remote with 7th row as REDUP, GREENUP, ...
    //Row 7
    buttonMap.emplace(0xFF28D7, {"Increase Red", CHANGER, "10"});
    buttonMap.emplace(0xFFA857, {"Increase Green", CHANGEG, "10"});
    buttonMap.emplace(0xFF6897, {"Increase Blue", CHANGEB, "10"});
    buttonMap.emplace(0xFFE817, {"Quick", QUICK});

    //Row 8
    buttonMap.emplace(0xFF08F7, {"Decrease Red",CHANGER, "-10"});
    buttonMap.emplace(0xFF8877, {"Decrease Green",CHANGEG, "-10"});
    buttonMap.emplace(0xFF48B7, {"Decrease Blue",CHANGEB, "-10"});
    buttonMap.emplace(0xFFC837, {"Slow", SLOW});//fade speed is Slow

    //Row 9
    buttonMap.emplace(0xFF30CF, {"DIY 1", DIY1});
    buttonMap.emplace(0xFFB04F, {"DIY 2", DIY2});
    buttonMap.emplace(0xFF708F, {"DIY 3", DIY3});
    buttonMap.emplace(0xFFF00F, {"Auto", AUTO});

    //Row 10
    buttonMap.emplace(0xFF10EF, {"DIY 4", DIY4});
    buttonMap.emplace(0xFF906F, {"DIY 5", DIY5});
    buttonMap.emplace(0xFF50AF, {"DIY 6", DIY6});
    buttonMap.emplace(0xFFD02F, {"Flash", FLASH});

    //Row 11
    buttonMap.emplace(0xFF20DF, {"Jump 3", JUMP3});
    buttonMap.emplace(0xFFA05F, {"Jump 7", JUMP7});
    buttonMap.emplace(0xFF609F, {"Fade 3", FADE3});
    buttonMap.emplace(0xFFE01F, {"Fade 7", FADE7});
*/

/*
    // 24 Key Remote Buttons
    //Row 1
    buttonMap.emplace(0xF700FF, {"Brightness Up",BRIGHTNESS_UP, ""});
    buttonMap.emplace(0xF7807F, {"Brightness Down",BRIGHTNESS_DOWN, ""});
    buttonMap.emplace(0xF740BF, {"Off", POWER_OFF, ""});
    buttonMap.emplace(0xF7C03F, {"Power On", NEXT_EFFECT, ""});

    //Row 2
    buttonMap.emplace(0xF720DF, {"Full Red",FILL_COLOR, "FF0000"});
    buttonMap.emplace(0xF7A05F, {"Full Green",FILL_COLOR, "00FF00"});
    buttonMap.emplace(0xF7609F, {"Full Blue",FILL_COLOR, "0000FF"});
    buttonMap.emplace(0xF7E01F, {"Full White",FILL_COLOR, "AAAAAA"}); //because we don't want FULL white
    
    //Row 3
    buttonMap.emplace(0xF710EF, {"Color 1",FILL_COLOR, "E18E28"});
    buttonMap.emplace(0xF7906F, {"Color 2",FILL_COLOR, "1B9205"});
    buttonMap.emplace(0xF750AF, {"Color 3",FILL_COLOR, "170C96"});
    buttonMap.emplace(0xF7D02F, {"Auto", AUTO, ""});

    //Row 4
    buttonMap.emplace(0xF730CF, {"Color 4",FILL_COLOR, "FBBE56"});
    buttonMap.emplace(0xF7B04F, {"Color 5",FILL_COLOR, "229248"});
    buttonMap.emplace(0xF7708F, {"Color 6",FILL_COLOR, "200991"});
    buttonMap.emplace(0xF7F00F, {"Strobe", STROBE, ""});

    //Row 5
    buttonMap.emplace(0xF708F7, {"Color 7",FILL_COLOR, "EDD917"});
    buttonMap.emplace(0xF78877, {"Color 8",FILL_COLOR, "2A92A1"});
    buttonMap.emplace(0xF748B7, {"Color 9",FILL_COLOR, "7415B4"});
    buttonMap.emplace(0xF7C837, {"Fade", FADE, ""});
    
    //Row 6
    buttonMap.emplace(0xFF18E7, {"Color 10",FILL_COLOR, "D0E30F"});
    buttonMap.emplace(0xFF9867, {"Color 11",FILL_COLOR, "2E7CC7"});
    buttonMap.emplace(0xFF58A7, {"Color 12",FILL_COLOR, "C121B1"});
    buttonMap.emplace(0xFFD827, {"Smooth", SMOOTH, "2D87D7"});
    }
    */

}

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

#endif