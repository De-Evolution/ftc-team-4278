#ifndef __SHAREDUTILS__
#include "JoystickDriver4278.c"
#include "hitechnic-irseeker-v2.h"
#include "wiringnxt.h"

#define __SHAREDUTILS__

#define setLeftMotors(x)  {motor[mLeft1]  = x; motor[mLeft2]  = x;}
#define setRightMotors(x) {motor[mRight1] = x; motor[mRight2] = x;}
#define setArmMotors(x)   {motor[mArm1] = x; motor[mArm2] = -x;}
#define setSpinMotor(x)   {motor[mSpin] = x;}
#define lockArmMotors()   {servo[servoL1] = 155; servo[servoL2] = 20;}
#define unlockArmMotors() {servo[servoL1] = 120; servo[servoL2] = 70;}

#define leftEncoder     abs(nMotorEncoder[mArm2])
#define rightEncoder    abs(nMotorEncoder[mArm1])
#define clearEncoders() {nMotorEncoder[mArm1] = 0; nMotorEncoder[mArm2] = 0;}

//Distance Macros
#define INCH   1.0
#define CM     0.3937
#define MM    39.370
#define YARD  36.0
#define FOOT  12.0
#define METER 39.370

#define WHEELCIRC 12.566
#define WHEELBASE 15.309
#define FLOORMAT  24.0

#define BTN_CENTER 3
#define BTN_LEFT   2
#define BTN_RIGHT  1
#define BTN_BACK   0

float linearScale(float x, float in_min, float in_max, float out_min, float out_max) {return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

void displayDiagnostics() {
	if(externalBatteryAvg < 0) nxtDisplayTextLine(3, "Ext Batt: OFF");
 		else nxtDisplayTextLine(3, "Ext Batt:%4.1f V", externalBatteryAvg/1000.0);
  nxtDisplayTextLine(4, "NXT Batt:%4.1f V", nAvgBatteryLevel/1000.0);
}

string sTextLines[8];
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC) {
	string sTemp;

	StringFormat(sTemp, "%4d  %4d", nValueDC, nValueAC);
	// Check if the new line is the same as the previous one
	// Only update screen if it's different.
	if (sTemp != sTextLines[nLineNumber])	{
		string sTemp2;

		sTextLines[nLineNumber] = sTemp;
		StringFormat(sTemp2, "%s:  %s", cChar, sTemp);
		nxtDisplayTextLine(nLineNumber, sTemp2);
	}
}

#endif //__SHAREDUTILS__