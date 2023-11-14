void dropToken(int currentCol, int choiceCol, bool isHumanPlaying);
const int CONVEYOR_ANGLE = 5 / (180/PI);
const int  DISTANCE_BETWEEN_TWO_COL = 3.5;
void spinnerMotor(bool isHumanPlaying);
task main()
{

motor[motorD] = 0;
setMotorBrakeMode(motorD, motorCoast);
motor[motorA] = -20
while (true)
{}
 //dropToken(7, 5, true)
// dropToken(3, 5, true);
//	SensorType[S1] = sensorEV3_Touch;
//	wait1Msec(50);
}
void dropToken(int currentCol, int choiceCol, bool isHumanPlaying)
{
	float colDx= 0;
	float colHyp = 0;
	colDx = choiceCol-currentCol;
	colDx *= DISTANCE_BETWEEN_TWO_COL;
	//colHyp = colDx / cos(CONVEYOR_ANGLE) // which is 5 deg angle is rad
	float countsConversion = (colDx * 360) / (4.6*PI);

	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorD] = 0;

	if (countsConversion > 0)
	{
		motor[motorA] = -5;
		motor[motorD] = 5;
		while (nMotorEncoder[motorD] <  countsConversion)
		{}
		motor[motorA]=motor[motorD] = 0;
	}
	else
	{
		motor[motorA] = 5;
	 	motor[motorD] = -5;
		while (nMotorEncoder[motorD] >  countsConversion)
		{}
		motor[motorA]= motor[motorD] = 0;
	}
	// Theorectically we have the hole in the track lined up to  the specified col
	spinnerMotor(isHumanPlaying);
	return;
}

void spinnerMotor(bool isHumanPlaying){

	if(isHumanPlaying)
	{
		motor[motorC] = 10;
		while (nMotorEncoder[motorC] < 95)
		{}
		motor[motorC] = 0;
	}
	else
	{

		motor[motorC] = -10;
		while (nMotorEncoder[motorC] > -5)
		{}
		motor[motorC] = 0;
	}
	return;
}

void configureMotors()
{
	nMotorEncoder[motorC] =  0;


	wait1Msec(500);
	motor[motorC]= 0 ;
}
