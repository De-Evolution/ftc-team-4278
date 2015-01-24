#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  mtr_S1_C2_1,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_3,    tubeHook1,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    tubeHook2,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "autoconst.h"
#include "drivers/autoutils.h"

int OPT_SIDE = 0; int OPT_DELAY = 0; int OPT_BRIDGE = 0;

void optionScreen() {
	nxtDisplayTextLine(0, "NXT:  %.2f V", ((float)nAvgBatteryLevel)/1000.0);
	if(externalBatteryAvg > 0) nxtDisplayTextLine(1, "EXT: %.2f V", ((float)externalBatteryAvg)/1000.0);
		else nxtDisplayTextLine(1, "EXT: OFF");

	if(nAvgBatteryLevel < NXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT     LOW***");
	if(externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***    EXT LOW***");
	if(nAvgBatteryLevel < NXT_LOW_BAT && externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT EXT LOW***");

	while(nNxtButtonPressed != BTN_CENTER) { // SIDE: Center | Bridge | None
				 if(OPT_SIDE == 0) nxtDisplayTextLine(3, "SIDE: Center");
		else if(OPT_SIDE == 1) nxtDisplayTextLine(3, "SIDE: Bridge");
		else if(OPT_SIDE == 2) nxtDisplayTextLine(3, "SIDE: None");

		if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
			PlaySound(soundShortBlip);
			if(nNxtButtonPressed == BTN_LEFT) OPT_SIDE--;
			if(nNxtButtonPressed == BTN_RIGHT) OPT_SIDE ++;
			if(OPT_SIDE > 2) OPT_SIDE = 0;
			if(OPT_SIDE < 0) OPT_SIDE = 2;

			while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
		}
	} PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(OPT_SIDE != 3) // DELAY: 0 - 25000
		while(nNxtButtonPressed != BTN_CENTER) {
			nxtDisplayTextLine(4, "DELY: %i", OPT_DELAY);
			if(nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {
				PlaySound(soundShortBlip);
				if(nNxtButtonPressed == 2) OPT_DELAY -= (time1[T1] < 200 ? 5000 : 1000);
				if(nNxtButtonPressed == 1) OPT_DELAY += (time1[T1] < 200 ? 5000 : 1000);
				if(OPT_DELAY < 0)     OPT_DELAY = 25000;
				if(OPT_DELAY > 25000) OPT_DELAY = 0;

				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
				ClearTimer(T1);
			}
		} if(OPT_SIDE != 3) PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(OPT_SIDE == 0) // BRIDGE: Closest | Left | Right | Back up | None
		while(nNxtButtonPressed != BTN_CENTER) {
			     if(OPT_BRIDGE == 0) nxtDisplayTextLine(5, "BRDG: Closest");
			else if(OPT_BRIDGE == 1) nxtDisplayTextLine(5, "BRDG: Left");
			else if(OPT_BRIDGE == 2) nxtDisplayTextLine(5, "BRDG: Right");
			else if(OPT_BRIDGE == 3) nxtDisplayTextLine(5, "BRDG: Back up");
			else if(OPT_BRIDGE == 4) nxtDisplayTextLine(5, "BRDG: None");

			if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
				PlaySound(soundShortBlip);
				if(nNxtButtonPressed == BTN_LEFT) OPT_BRIDGE--;
				if(nNxtButtonPressed == BTN_RIGHT) OPT_BRIDGE++;
				if(OPT_BRIDGE > 4) OPT_BRIDGE = 0;
				if(OPT_BRIDGE < 0) OPT_BRIDGE = 4;

				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
			}
		} if(OPT_SIDE < 2) PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);
	nxtDisplayTextLine(7, "*** LOCKED ***");
}

task main() {
	//--------------------------------------------------------
	//Setup stuff goes here
	//--------------------------------------------------------

	StartTask(monitorFeedback);
	retractHooks();

	//--------------------------------------------------------
	//Main sequence goes here
	//--------------------------------------------------------

	//waitForStart();
  //extendArm();
	rbtMoveFdDist(-48, 13000);

	int centerpiecePosition = getCenterpiecePosition();

	if(centerpiecePosition == 1)
	{
		rbtTurnRight(-80);
		rbtMoveFdDist(30, 27, 5000);
		rbtTurnLeft(35);
		rbtMoveFdDist(100, 20, 4000);
	}
	else if(centerpiecePosition == 2)
	{
		rbtMoveFdDist(-8, 2000);
		rbtTurnRight(-92);
		rbtMoveFdDist(100, 45, 5000);
	}
	else
	{
		rbtArcRight(-45);
		rbtMoveFdDist(-30, 9000);

		rbtArcLeft(-53);
		rbtMoveFdDist(100, 55, 5000);
	}

	//rbtTurnRight(90);
	//rbtTurnLeft(90);


	//rbtMoveFdDist(35, 6000);
	//rbtTurnRight(90);
	//rbtTurnLeft(180);


}
