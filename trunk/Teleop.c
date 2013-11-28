#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     HTSPB,                sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight2,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft1,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     mArm1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/teleoputils.h"
#include "drivers/wiringnxt.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case JOY_X:  if(pressed) {} else {} break;
		case JOY_Y:  if(pressed) {} else {} break;
		case JOY_A:  if(pressed) {} else {} break;
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
			//nxtDisplayTextLine(2, "%i", i);
			btn ^= 1<<i;
		}
	}
}

task main() {
	displayDiagnostics();
	unlockArmMotors();
	//int ac1, ac2, ac3, ac4, ac5;
	while(true) {
		getJoystickSettings(joystick);
		//HTIRS2readAllACStrength(sensorIR, ac1, ac2, ac3, ac4, ac5);
		//nxtDisplayTextLine(0, "AC1: %i", ac1);
		//nxtDisplayTextLine(1, "AC2: %i", ac2);
		//nxtDisplayTextLine(2, "AC3: %i", ac3);
		//nxtDisplayTextLine(3, "AC4: %i", ac4);
		//nxtDisplayTextLine(4, "AC5: %i", ac5);
	  //nxtDisplayTextLine(5, "E1:  %i", rightEncoder);
		//nxtDisplayTextLine(6, "E2:  %i", leftEncoder);
		checkJoystickButtons();
		//nxtDisplayTextLine(3, "Y1: %i X1: %i", JOY_Y1, JOY_X1);
		//nxtDisplayTextLine(4, "PY: %i PX: %i", powscl(JOY_Y1), powscl(JOY_X1);
		setLeftMotors(powscl(JOY_Y1)-powscl(JOY_X1)/1.1);
		setRightMotors(powscl(JOY_Y1)+powscl(JOY_X1)/1.1);
		int t = time1[T1];
		nxtDisplayTextLine(6, "T:%i", t);
		float accum = 0;
		for(short i=0;i<10;i++){accum+=(analogRead(A3)*0.4);}
		nxtDisplayTextLine(3, "A3: %f",accum/10 );
		ClearTimer(T1);
	}
}
