#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker1200)
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
//*!!Code automagically venerated by 'ROBOTC' configuration lizard               !!*//

#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"

#define IR 0

void rbtMoveFd(float inches) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);

	while(leftEncoder < enc || rightEncoder < enc) {
		//nxtDisplayTextLine(0, "E%i", enc);
		//nxtDisplayTextLine(1, "L%i", leftEncoder);
		//nxtDisplayTextLine(2, "R%i", rightEncoder);

		setLeftMotors (50*norm);
		setRightMotors(50*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtMoveFdTime(float inches, int msec) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);
	ClearTimer(T3);
	while(leftEncoder < enc || rightEncoder < enc || time1[T3] < msec) {
		//nxtDisplayTextLine(0, "E%i", enc);
		//nxtDisplayTextLine(1, "L%i", leftEncoder);
		//nxtDisplayTextLine(2, "R%i", rightEncoder);

		setLeftMotors (100*norm);
		setRightMotors(100*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*45);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*45);
	while(rightEncoder < enc) wait1Msec(10);
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*35);
	setRightMotors(sgn(degs)*35);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*35);
	setRightMotors(-1*sgn(degs)*35);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void dumpArm() {
	setArmMotors(60);
	wait1Msec(1600);
	setArmMotors(0);
	wait1Msec(500);
	setArmMotors(-50);
	wait1Msec(1100);
	setArmMotors(0);
}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Start Autonomous Fucntions
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void normstop(){
	while(true) wait1Msec(100);
}

void estop(){
	StopAllTasks();
}
void leftBridge(float bridgeDist){
	rbtArcRight(90); wait1Msec(150);
	rbtMoveFd(bridgeDist); wait1Msec(150);
	rbtArcRight(-90); wait1Msec(150);
	rbtMoveFd(18); wait1Msec(150);
	rbtArcRight(-94); wait1Msec(150);
	rbtMoveFdTime(32, 5000);
	normstop();
}

void rightBridge(float bridgeDist){
	rbtArcLeft(-90); wait1Msec(150);
	rbtMoveFd(bridgeDist); wait1Msec(150);
	rbtArcLeft(88); wait1Msec(150);
	rbtMoveFd(18); wait1Msec(150);
	rbtArcLeft(94); wait1Msec(150);
	rbtMoveFdTime(32, 5000);
	normstop();
}

void crateOne(){
	rbtArcLeft(23.5); wait1Msec(150);
	rbtMoveFd(35); wait1Msec(150);
	rbtArcRight(-23.5); wait1Msec(150);
	dumpArm();
	leftBridge(10.0);
}

void crateTwo(){
	rbtArcLeft(11); wait1Msec(150);
	rbtMoveFd(32); wait1Msec(150);
	rbtArcRight(-14); wait1Msec(150);
	dumpArm();
	leftBridge(21.5);
}

void crateThree(){
	rbtArcRight(-8.7); wait1Msec(150);
	rbtMoveFd(33); wait1Msec(150);
	rbtArcLeft(11.7); wait1Msec(150);
	dumpArm();
	rightBridge(22.0);
}

void crateFour(){
	rbtArcRight(-24.5); wait1Msec(150);
	rbtMoveFd(35); wait1Msec(150);
	rbtArcLeft(24.5); wait1Msec(150);
	dumpArm();
	rightBridge(11.5);
}

void initialize(){
	unlockArmMotors();
}

void crateSelect(int crate){
	switch(crate){
		case 0:
			break;
		case 1:
			crateOne();
			break;
		case 2:
			crateTwo();
			break;
		case 3:
			crateThree();
			break;
		case 4:
			crateFour();
			break;
	}
}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
End Autonomous Fucntions
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

task main() {
	displayDiagnostics();
	initialize();
	crateSelect(1);
}
