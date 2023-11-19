void sortTokens(){
	motor[motorA] = -10;
	wait1Msec(100);
	bool tokens = true;
	time1[T1] = 0;
	time1[T2] = 0;
	int previousMotor = 100;
	int nextEncoder = 0;

	while(tokens && SensorValue[S1] == false){
  		if(SensorValue[S2] == 4) {
  			motor[motorB] = -20;
  			while(nMotorEncoder[motorB] > -65){}
  			motor[motorB] = 0;
		}

		else if(SensorValue[S2] == 5) {
	 		wait1Msec(500);
	    	motor[motorB] = 20;
  			while(nMotorEncoder[motorB] < 0){}
  			motor[motorB] = 0;
		}

		int timeSample = time1[T1];

		if(time1[T1] >= 1000){

				if(previousMotor == nMotorEncoder[motorA]){
				  	displayString(4, "yes");
						motor[motorA] = 10;
						wait1Msec(1000);
						motor[motorA] = -10;
						}
						previousMotor = nMotorEncoder[motorA];
						displayString(5, "%f", previousMotor);
						time1[T1] =0;
					}
    }


		/*if(nMotorEncoder[motorA] == nextEncoder){
			time1[T2] = 0;
			while(time1[T2] <= 1000){
				motor[motorA] = 10;
			}
			motor[motorA] = -10;
		}

		nextEncoder = nMotorEncoder[motorA] + 2;


		if(nMotorEncoder[motorA] == previousMotor){
			time1[T2] = 0;
			while(time1[T2] <= 1000){
				motor[motorA] = 10;
			}
			motor[motorA] = -10;
		}

		if(time1[T1] == 250){
			previousMotor = nMotorEncoder[motorA];
			time1[T1] = 0;
		}*/
	motor[motorB] = 20;
  	while(nMotorEncoder[motorB] < 0)
  		{}
  	motor[motorB] = 0;
}

task main(){
	SensorType[S1] = sensorEV3_Touch;
wait1Msec(50);
SensorType[S2] = sensorEV3_Color;
wait1Msec(50);
SensorMode[S2] = modeEV3Color_Color;
wait1Msec(50);

nMotorEncoder[motorA] = 0;
nMotorEncoder[motorB] = 0;


	sortTokens();
}
