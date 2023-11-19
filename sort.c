void sortTokens();
task main()
{

sortTokens();

}
w
void sortTokens(){
	motor[motorC] = -10;
	bool tokens = true;
	time1[T1] = 0;
	time1[T2] = 0;
	int previousMotor = 0;

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
		if(nMotorEncoder[motorC] == previousMotor){
			time1[T2] = 0;
			while(time1[T2] <= 500){
				motor[motorC] = 10;
			}
			motor[motorC] = -10;
		}

		if(time1[T1] == 250){
			previousMotor = nMotorEncoder[motorC];
			time1[T1] = 0;
		}
	}
	motor[motorB] = 20;
  	while(nMotorEncoder[motorB] < 0){}
  	motor[motorB] = 0;
}
