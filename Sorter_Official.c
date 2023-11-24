#include "mindsensors-motormux.h"
void sortTokens(){
	motor[motorC] = -10;

	time1[T1] = 0;

	int previousMotor = 100;

	while(SensorValue[T1] == 0){
  		if(SensorValue[S2] == 4) {
  			motor[motorB] = -60;
  			while(nMotorEncoder[motorB] > -60){}
  			motor[motorB] = 0;

		  }

			else if(SensorValue[S2] == 5) {
		 		  wait1Msec(500);
		    	motor[motorB] = 60;
	  			while(nMotorEncoder[motorB] < 0){}
	  			motor[motorB] = 0;
			 }

			if(time1[T1] >= 500){
					if(previousMotor == nMotorEncoder[motorC]){
							motor[motorC] = 10;
							wait1Msec(1000);
							motor[motorC] = -10;
							}
							previousMotor = nMotorEncoder[motorC];
							time1[T1] = 0;
						}
  }

	motor[motorC] = 0;
	motor[motorB] = 30;
  while(nMotorEncoder[motorB] < 0){}
  motor[motorB] = 0;
  wait1Msec(5000);
}



task main(){
	MSMMUXinit();
	SensorType[S4] = sensorI2CCustom;
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);

	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorB] = 0;

	sortTokens();
}
