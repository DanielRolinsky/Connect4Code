// Configure Sensors
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

void configureMotors();


task main()
{
configureMotors();
}

//Playing Function

	//HumanMove Function
		//Legal Move check function
		//Drop Token Function

	//RobotMove Function`
		//MiniMax Function
		//Drop Token Function

//Sorting Function
	//
void configureMotors()
{
nMotorEncoder[motorA]= nMotorEncoder[motorB]= 0;
motor[motorA] = motor[motorD]= 0 ;
}