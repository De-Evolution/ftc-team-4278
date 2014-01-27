#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mArm1,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     mNull1,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case JOY_X:  if(pressed) {setSpinMotor(100);}  else {setSpinMotor(0);} break;
		case JOY_Y:  if(pressed) {setSpinMotor(100);}  else {setSpinMotor(0);} break;
		case JOY_A:  if(pressed) {setSpinMotor(100);}  else {setSpinMotor(0);} break;
		case JOY_B:  if(pressed) {setSpinMotor(100);}  else {setSpinMotor(0);} break;

		case JOY_RB: if(pressed) {setArmMotors(50);}  else {setArmMotors(0);} break;
		case JOY_LB: if(pressed) {setArmMotors(-100);} else {setArmMotors(0);} break;
		case JOY_RT: if(pressed) {unlockArmMotors();} else {} break;
		case JOY_LT: if(pressed) {lockArmMotors();} else {} break;

		case JOY_R3: if(pressed) {} else {} break;
		case JOY_L3: if(pressed) {} else {} break;
		case JOY_ST: if(pressed) {} else {} break;
		case JOY_BA: if(pressed) {} else {} break;
	}
}

short btn = JOY_BTN;
void checkJoystickButtons() {
	if(btn == JOY_BTN) return;
	for(short i = 11; i >= 0; i--) {
		if((btn>>i) ^ (JOY_BTN>>i)) {
			invokeButton(i, ((btn & (1 << i)) == 0));
			btn ^= 1<<i;
		}
	}
}

void debugBlock() {
	nxtDisplayTextLine(0,"%d",rightEncoder);
	nxtDisplayTextLine(4,"%d",joystick.joy1_TopHat);
	int dirIR, strIR;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	nxtDisplayTextLine(1,"IR: %i", dirIR);
	if(dirIR == 5) {
		PlaySound(soundBeepBeep);
		setRightMotors(0); setLeftMotors(0);
		setArmMotors(0);
		while(1 == 1) wait1Msec(5);
	}
}

task main() {
	unlockArmMotors();
	clearEncoders();
 	waitForStart();

 	while(true) {
		getJoystickSettings(joystick);
		checkJoystickButtons();
		//debugBlock();

		if(joystick.joy1_TopHat == -1) {
			setRightMotors(powscl(JOY_Y1)-powscl(JOY_X1)/1.1);
			setLeftMotors(powscl(JOY_Y1)+powscl(JOY_X1)/1.1);
		} else {
			setRightMotors(getRightPowTopHat(joystick.joy1_TopHat));
			setLeftMotors(getLeftPowTopHat(joystick.joy1_TopHat));
		}
	}
}