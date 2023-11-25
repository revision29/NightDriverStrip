//+--------------------------------------------------------------------------
//
// File:        RemoteControl.h
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
// History:     Jul-17-2021     Davepl      Documented
//---------------------------------------------------------------------------

#pragma once
#if ENABLE_REMOTE
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <limits>

void IRAM_ATTR RemoteLoopEntry(void *);


class RemoteControl
{
  private:
    IRrecv _IR_Receive;
    

  public:

    RemoteControl() : _IR_Receive(IR_REMOTE_PIN)
    {
    }

    bool begin()
    {
        debugW("Remote Control Decoding Started");
        _IR_Receive.enableIRIn();
        return true;
    }

    void end()
    {
        debugW("Remote Control Decoding Stopped");
        _IR_Receive.disableIRIn();
    }

    void handle();
};

#endif