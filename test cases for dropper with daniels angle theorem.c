void dropToken( int choiceCol, bool isHumanPlaying);
const int CONVEYOR_ANGLE = 5 / (180/PI);
const int  DISTANCE_BETWEEN_TWO_COL = 3.5;
void spinnerMotor(bool isHumanPlaying);

const int col1 = 0;
const int col2 = -73;
const int col3 = -155;
const int col4 = -210;
const int col5 = -303;
const int col6 = -460;
const int col7 = -530;


task main()
{
dropToken(1,true);
}

void dropToken(int choiceCol, bool isHumanPlaying)
{
	nMotorEncoder[motorA] = 0;
	int colAngle[7]=
	{0, -73, -155, -225, -320, -400, -528};

	for(int col =0; col < 7; col++)
	{
		if(choiceCol == col + 1)
		{
			motor[motorA] = -5;
			motor[motorD] = 5;
			while(nMotorEncoder[motorA] > colAngle[col])
			{}
			motor[motorA] = motor[motorD] = 2;
			while(!getButtonPress(buttonEnter))
		{

			}

			motor[motorA] = motor[motorD] = 0;

		}
	}
}

/*

*/
