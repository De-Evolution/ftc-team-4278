////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                    HiTechnic Servo/Motor Controller Device Driver  - UPDATED 1/08/2009//
//
// With the TETRIX system, the PC Controller Station sends messages over Bluetooth to the NXT containing
// current settings of a PC joystick. The joystick settings arrive using the standard NXT BLuetooth
// "message mailbox" facility.
//
// This is a short ROBOTC program to extract the joystick data from a mailbox message and format it
// into data structure that can be easily acccessed by end user programs.
//
// The driver resides in a separate file that can be simply added to any user program with a
// "#include" preprocessor directive. End users should not have to modify this program and can use
// it as is.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __JOSTICKDRIVERC4278__
#define __JOSTICKDRIVERC4278__

#pragma autoStartTasks        // Automatically start this task when the main user program starts.
#pragma systemFile

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Joystick Information Structure
//
//
// Structure containing info from Joystick.
//
// "short" variables are used to prevent conversion errors. For example, negating a byte variable with
// value -128 results in -128 because -128 does not fit in a byte!
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  bool    UserMode;          // Autonomous or Telep-Operated mode
  bool    StopPgm;           // Stop program

  short   joy1_x1;           // -128 to +127
  short   joy1_y1;           // -128 to +127
  short   joy1_x2;           // -128 to +127
  short   joy1_y2;           // -128 to +127
  short   joy1_Buttons;      // Bit map for 12-buttons
  short   joy1_TopHat;       // value -1 = not pressed, otherwise 0 to 7 for selected "octant".
/*
  short   joy2_x1;           // -128 to +127
  short   joy2_y1;           // -128 to +127
  short   joy2_x2;           // -128 to +127
  short   joy2_y2;           // -128 to +127
  short   joy2_Buttons;      // Bit map for 12-buttons
  short   joy2_TopHat;       // value -1 = not pressed, otherwise 0 to 7 for selected "octant".
  */
} TJoystick;
TJoystick joystick;      // User defined variable access

#if defined(hasJoystickMessageOpcodes)
intrinsic void getJoystickSettings(TJoystick &joystick)
asm(opcdSystemFunctions, byte(sysFuncGetJoysticks),
variableRefRAM(joystick));
#endif

#define getJoystickSettings(joystick) 	memcpy(joystick, joystickCopy, sizeof(joystick))

bool joy1Btn(int btn) {return ((joystick.joy1_Buttons & (1 << btn)) != 0);}
//bool joy2Btn(int btn) {return ((joystick.joy2_Buttons & (1 << btn)) != 0);}

const TMailboxIDs kJoystickQueueID = mailbox1;
TJoystick joystickCopy;  // Internal buffer to hold the last received message from the PC. Do not use

long ntotalMessageCount = 0;

bool bDisconnected = false;
bool bOverrideJoystickDisabling = false;
long nNoMessageCounterLimit = 500;
long nNoMessageCounter = 0;
task readMsgFromPC() {
  bool bMsgFound;

  TFileIOResult nBTCmdRdErrorStatus;
  const int kMaxSizeOfMessage = 18;
  sbyte tempBuffer[kMaxSizeOfMessage];

  joystickCopy.UserMode  = false;
  joystickCopy.StopPgm   = true;

  joystickCopy.joy1_x1 = 0;
  joystickCopy.joy1_y1 = 0;
  joystickCopy.joy1_x2 = 0;
  joystickCopy.joy1_y2 = 0;
  joystickCopy.joy1_Buttons = 0;
  joystickCopy.joy1_TopHat = -1;
/*
  joystickCopy.joy2_x1 = 0;
  joystickCopy.joy2_y1 = 0;
  joystickCopy.joy2_x2 = 0;
  joystickCopy.joy2_y2 = 0;
  joystickCopy.joy2_Buttons = 0;
  joystickCopy.joy2_TopHat = -1;
*/
  bool bTempUserMode, bTempStopPgm;

  while(true) {
    bMsgFound = false;
    bDisconnected = false;
    while(true) {
      // There may be more than one message in the queue. We want to get to the last received
      // message and discard the earlier "stale" messages. This loop simply discards all but
      // the last message.
      int nSizeOfMessage;
      nSizeOfMessage = cCmdMessageGetSize(kJoystickQueueID);

      if (nSizeOfMessage <= 0) {
        if (!bMsgFound) {
          if (nNoMessageCounter > nNoMessageCounterLimit) {
            hogCPU();
            if (!bOverrideJoystickDisabling) {
              bTempUserMode = joystickCopy.UserMode;
              bTempStopPgm = joystickCopy.StopPgm;

              memset(joystickCopy, 0, sizeof(joystickCopy));

              joystickCopy.UserMode = bTempUserMode;
              joystickCopy.StopPgm = bTempStopPgm;
              joystickCopy.joy1_TopHat = -1;
              //joystickCopy.joy2_TopHat = -1;
            }
            bDisconnected = true;
            releaseCPU();
          }
          wait1Msec(4);    // Give other tasks a chance to run
          nNoMessageCounter++;
          continue;        // No message this time. Loop again
        } else {
          bDisconnected = false;
          nNoMessageCounter = 0;
          break;
        }
        // No more messages available and at least one message found. This is not essential but
        // useful to ensure that we're working with the latest message. We simply discard earlier
        // messages. This is useful because there could be many messages queued and we don't
        // want to work with stale data.
      }

      if(nSizeOfMessage > sizeof(tempBuffer)) {nSizeOfMessage = sizeof(tempBuffer);}
      nBTCmdRdErrorStatus = cCmdMessageRead(&tempBuffer[0], nSizeOfMessage, kJoystickQueueID);
      nBTCmdRdErrorStatus = nBTCmdRdErrorStatus; //Get rid of info message

      // Repeat loop until there are no more messages in the queue. We only want to process the
      // last message in the queue.
      bMsgFound = true;
    }

    hogCPU();   // grab CPU for duration of critical section

    ++ntotalMessageCount;

    joystickCopy.UserMode           = (bool)tempBuffer[1];
    joystickCopy.StopPgm            = (bool)tempBuffer[2];

    joystickCopy.joy1_x1            = tempBuffer[3];
    joystickCopy.joy1_y1            = -tempBuffer[4];// Negate to "natural" position
    joystickCopy.joy1_x2            = tempBuffer[5];
    joystickCopy.joy1_y2            = -tempBuffer[6];// Negate to "natural" position
    joystickCopy.joy1_Buttons       = (tempBuffer[7] & 0x00FF) | (tempBuffer[8] << 8);
    joystickCopy.joy1_TopHat        = tempBuffer[9];

    releaseCPU(); // end of critical section
  }
}

#endif
