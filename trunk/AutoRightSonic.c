#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     sensorIR,         sensorI2CCustom)
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

#include "drivers/wiringnxt.h"
#include "drivers/JoystickDriver4278.c"
#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"

#define DrTimer T3
#define SeTimer T2

void rbtMoveFd(float inches) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);

	while(leftEncoder < enc || rightEncoder < enc) {
		setLeftMotors (40*norm);
		setRightMotors(40*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtMoveFdTime(float inches, int msec) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);
	ClearTimer(DrTimer);
	while(leftEncoder < enc && rightEncoder < enc && time1[DrTimer] < msec) {
		setLeftMotors (100*norm);
		setRightMotors(100*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*35);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*35);
	while(rightEncoder < enc) wait1Msec(10);
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*30);
	setRightMotors(sgn(degs)*30);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*30);
	setRightMotors(-1*sgn(degs)*30);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void dumpArm() {
	setArmMotors(50);
	wait1Msec(1550);
	setArmMotors(0);
	wait1Msec(400);
	setArmMotors(-50);
	wait1Msec(900);
	setArmMotors(0);
}

void pause() {wait1Msec(175);}

bool pathClear(float dist){
	pause();
	float read = 0;
	for(int i=0;i<10;i++){read+=(analogRead(A3)*0.4);wait1Msec(5);}
	return ((read/10)<dist?false:true);
}

void normstop() {while(true) wait1Msec(100);}
void estop() {StopAllTasks();}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Start Autonomous Fucntions
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

void rightBridge(float bridgeDist){
	rbtMoveFd(bridgeDist); pause();
	rbtArcRight(-90); pause();
	rbtMoveFd(18); pause();
	rbtArcRight(-94); pause();
	rbtMoveFdTime(25, 5000);
	normstop();
}

void leftBridge(float bridgeDist){
	rbtMoveFd(bridgeDist); pause();
	rbtArcLeft(88); pause();
	rbtMoveFd(18); pause();
	rbtArcLeft(94); pause();
	rbtMoveFdTime(25, 5000);
	normstop();
}

void farLeftBridge(float bridgeDist){
	rbtMoveFd(-bridgeDist); pause();
	rbtArcRight(90); pause();
	rbtMoveFd(-20); pause();
	rbtArcLeft(-90); pause();
	rbtMoveFdTime(37, 5000);
	normstop();
}

void farRightBridge(float bridgeDist){
	rbtMoveFdTime(-bridgeDist, 3000); pause();
	rbtArcLeft(-89); pause();
	rbtMoveFd(-22); pause();
	rbtArcRight(90); pause();
	rbtMoveFdTime(40, 5000);
	normstop();
}

void crateOne(){
	dumpArm();
	rbtArcRight(88.5); pause();
	if(pathClear(29)) rightBridge(16);
	else farLeftBridge(39.5);
}

void crateTwo(){
	dumpArm();
	rbtArcRight(90); pause();
	if(pathClear(50)) rightBridge(29);
	else farLeftBridge(30);
}

void crateThree(){
	dumpArm();
	rbtMoveFd(-2);
	rbtArcLeft(-87.5); pause();
		if(pathClear(80)) leftBridge(25);
	else farRightBridge(24);
}

void crateFour(){
	dumpArm();
	rbtMoveFd(-0.5); pause();
	rbtArcLeft(-87); pause();
	if(pathClear(50)) leftBridge(14);
	else farRightBridge(33.5);
}

void initializeRobot(){
	unlockArmMotors();
}

int crateButtons() {
	int crate = 0;
	while(!nNxtButtonPressed == BTN_CENTER) {
		if(crate > 0) nxtDisplayTextLine(3, "Crate? %i", crate);
		else nxtDisplayTextLine(3, "Crate? IR");
		if(nNxtButtonPressed == BTN_LEFT)  {crate--; while(nNxtButtonPressed == BTN_LEFT);}
		if(nNxtButtonPressed == BTN_RIGHT) {crate++; while(nNxtButtonPressed == BTN_RIGHT);}
		if(crate < 0) crate = 4; if(crate > 4) crate = 0;
	}
	return crate;
}
long nNumbCyles;
long nInits = 0;
string sTextLines[8];
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC);

int crateIR(tSensors link, bool debug){
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;
	int aSum, dSum;
	//for(;debug;){
if (!HTIRS2readAllDCStrength(sensorIR, dcS1, dcS2, dcS3, dcS4, dcS5)){}
        //break; // I2C read error occurred
      if (!HTIRS2readAllACStrength(sensorIR, acS1, acS2, acS3, acS4, acS5 )){}
       // break; // I2C read error occurred

        aSum = acS1+acS2+acS3+acS4+acS5;
        dSum = dcS1+dcS2+dcS3+dcS4+dcS5;
      displayText(1, "D", dSum, aSum);
      displayText(2, "1", dcS1, acS1);
      displayText(3, "2", dcS2, acS2);
      displayText(4, "3", dcS3, acS3);
      displayText(5, "4", dcS4, acS4);
      displayText(6, "5", dcS5, acS5);
	//}
	if(!debug){
		if(dSum<=2 && (aSum > 25 && aSum < 31)){return 4;}
		else if((dSum==3 || dSum == 4 || dSum == 5) && (aSum > 27 && aSum<45) && acS3 == 0){return 3;}
		else if((dSum==3 || dSum == 4) && (aSum > 27 && aSum<60)){return 2;}
		else return 1;
	}
	return 1;
}

void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC)
{
  string sTemp;

  StringFormat(sTemp, "%4d  %4d", nValueDC, nValueAC);
  // Check if the new line is the same as the previous one
  // Only update screen if it's different.
  if (sTemp != sTextLines[nLineNumber])
  {
    string sTemp2;

    sTextLines[nLineNumber] = sTemp;
    StringFormat(sTemp2, "%s:  %s", cChar, sTemp);
    nxtDisplayTextLine(nLineNumber, sTemp2);
  }
}

void crateSelect(int crate){
	int crt;
	int dirIR, strIR;
	float in;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	clearEncoders();
	if(dirIR == 5 && strIR >= 85){
		rbtMoveFd(4.5);
		pause();
		rbtArcRight(-43);
		pause();
		rbtMoveFdTime(2.4, 1000);
		crateFour();
	}else if(dirIR == 5 && strIR <=84){
		rbtArcLeft(45);
		pause();
		rbtMoveFd(2);
		pause();
		rbtArcRight(-90);
		pause();
		rbtMoveFdTime(2, 750);
		pause();
		crateThree();
	}else{

	}
	//while( + dc2 < 135 && in > 2300) {
	//	nxtDisplayTextLine(3, "Distance: %d", in);
	//	setRightMotors(-25);
	//	setLeftMotors(-25);
	//	in = leftEncoder;
	//	HTIRS2readAllACStrength(sensorIR,ac1,ac2,ac3,ac4,ac5);
	//	HTIRS2readAllDCStrength(sensorIR,dc1,dc2,dc3,dc4,dc5);
	//}
	//setRightMotors(0);
	//setLeftMotors(0);
	//wait1Msec(250);
	//rbtArcRight(-89);
	//crt = floor(in/140)+1;
	//nxtDisplayBigTextLine(5, "%d",crt);
	//rbtMoveFdTime(3.5,1500);
	//wait1Msec(250);
	//switch(crt) {
	//	case 1: crateFour();
	//					break;
	//	case 2: crateThree();
	//					break;
	//	case 3: crateTwo();
	//					break;
	//	default: crateOne();
	//					break;
	//}
	StopAllTasks();
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * End Autonomous Fucntions
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

task main() {
	displayDiagnostics();
	initializeRobot();
	int crate = 0;//crateButtons();
	waitForStart();
	crateSelect(crate);
}
