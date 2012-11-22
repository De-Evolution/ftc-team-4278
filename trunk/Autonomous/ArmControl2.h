#define lowEnc 7100.0
#define midEnc 14700.0
#define hiEnc 22750.0

#define armThresh 200.0
#define motArmR motor[motorAmrR]
#define motArmL motor[motorAmrL]

const tMUXSensor colorPort = msensor_S1_4;

task armHi() {
	int _r, _g, _b;
	int l = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1)+(nMotorEncoder[motorAmrR]<lowEnc?-10:10);
	int r = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(true) {
		HTCS2readRGB(colorPort, _r, _g, _b);
		nxtDisplayTextLine(3, "r:%i", _r);
		nxtDisplayTextLine(4, "g:%i", _g);
		nxtDisplayTextLine(5, "b:%i", _b);
		if(_b < 120 && _b > 80 && _g < 80 && _r < 40) break;
		EndTimeSlice();
	}
	motArmL = 0;
	motArmR = 0;
}
task armMid() {
	int _r, _g, _b;
	int l = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1)+(nMotorEncoder[motorAmrR]<lowEnc?-10:10);
	int r = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(true) {
		HTCS2readRGB(colorPort, _r, _g, _b);
		if(_g < 40 && _r < 40 && _b < 40) break;
		EndTimeSlice();
	}
	motArmL = 0;
	motArmR = 0;
}
task armLow() {
	int _r, _g, _b;
	int l = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1)+(nMotorEncoder[motorAmrR]<lowEnc?-10:10);
	int r = 85*(nMotorEncoder[motorAmrR]<lowEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(true) {
		HTCS2readRGB(colorPort, _r, _g, _b);
		if(_r > 100 && _g < 50 && _b < 50) break;
		EndTimeSlice();
	}
	motArmL = 0;
	motArmR = 0;
}
