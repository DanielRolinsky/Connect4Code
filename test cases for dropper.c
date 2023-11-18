void dropToken(int currentCol, int choiceCol, bool isHumanPlaying);
const int CONVEYOR_ANGLE = 5 / (180/PI);
const int  DISTANCE_BETWEEN_TWO_COL = 3.5;
void spinnerMotor(bool isHumanPlaying);
task main()
{
motor[motorA] = 1;
motor[motorD] = 1;
while(1)
{}
// dropToken(1, 5, true)
}
void dropToken(int currentCol, int choiceCol, bool isHumanPlaying)
{
	float colDx= 0;
	float colHyp = 0;
	int coldifference  = 0;
	coldifference = choiceCol-currentCol;
	colDx = coldifference;
	colDx *= DISTANCE_BETWEEN_TWO_COL;
	//colHyp = colDx / cos(CONVEYOR_ANGLE) // which is 5 deg angle is rad
	float countsConversion = (colDx * 360.0) / (1.7*PI*2);

	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorD] = 0;

	if (countsConversion > 0)
	{
		if (coldifference == 1)
		{
		motor[motorA] = -5;
		motor[motorD] = 5;
		while (nMotorEncoder[motorD] <  countsConversion)
		{}
		motor[motorA]=motor[motorD] = 0;
		}
		else if(coldifference == 2)
			{
				countsConversion = (colDx * 360.0) / (2*PI*2)
				motor[motorA] = -5;
				motor[motorD] = 5;
				while (nMotorEncoder[motorD] <  countsConversion)
				{}
				motor[motorA]=motor[motorD] = 0;
			}
			else
			{
				countsConversion = (colDx * 360.0) / (2*PI*2)
				motor[motorA] = -5;
				motor[motorD] = 5;
				while (nMotorEncoder[motorD] <  countsConversion)
				{}
				motor[motorA]=motor[motorD] = 0;
			}
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
}
