
#include "mindsensors-motormux.h"
void sortTokens(){
	MSMMotor(mmotor_S4_1, -1);
	wait1Msec(100);
	bool tokens = true;
	time1[T1] = 0;
	time1[T3] = 0;
	int previousMotor = 100;
	int nextEncoder = 0;

	while(time1[T3] < 7000){
  		if(SensorValue[S2] == 4) {
  			motor[motorB] = -35;
  			while(nMotorEncoder[motorB] > -55){}
  			motor[motorB] = 0;
  			time1[T3] = 0;
		}

		else if(SensorValue[S2] == 5) {
	 		wait1Msec(500);
	    	motor[motorB] = 35;
  			while(nMotorEncoder[motorB] < 0){}
  			motor[motorB] = 0;
  			time1[T3] = 0;
		}

		if(time1[T1] >= 1000){

				if(previousMotor == MSMMotorEncoder(mmotor_S4_1)){
						MSMMotor(mmotor_S4_1, 1);
						wait1Msec(1000);
						MSMMotor(mmotor_S4_1, -1);
						}

						previousMotor = MSMMotorEncoder(mmotor_S4_1);
						time1[T1] = 0;

					}


}
	motor[motorB] = 50;
  	while(nMotorEncoder[motorB] < -10)
  		{}
  	MSMotorStop(mmotor_S4_1);
  	motor[motorB] = 0;
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

MSMMotorEncoderReset(mmotor_S4_1);
nMotorEncoder[motorB] = 0;


	sortTokens();
}
