#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, PIDControl, reversed, encoder)
#include "mindsensors-motormux.h"
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;
const int DEFAULT_DISPLAY_LINE = 3;

void sensorConfig();
void configureMotors();
void waitButton(TEV3Buttons buttonName);
void motorHold(int choiceCol);
void playGame(int & currentPlayer);
void dropToken(int choiceCol, bool isHumanPlaying); // done
void sortTokens();
int gameState(int & currentPlayer);
void humanMove(int currentCol);
void HumanMove2(int currentCol);

//void gameReset(int currentCol);
int moveSelect(int currentCol);
void spinnerMotor(bool isHumanPlaying); // done
bool legalCheck(int choiceCol);

const int colAngle[7]=
	{0, -70, -145, -215, -300, -400, -528};


int boardArray[BOARD_ROWS][BOARD_COLUMNS] =
    {
		{0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
    };


task main()
{
	bool stillPlaying = false;
	while(stillPlaying)
		{

	MSMMUXinit();
	SensorType[S4] = sensorI2CCustom;
	int	currentPlayer = 0;

		sensorConfig();
		configureMotors();

		displayString(DEFAULT_DISPLAY_LINE, "First place cartridges on top");
		displayString(DEFAULT_DISPLAY_LINE + 1, "Then press Enter to play!");
		waitButton(buttonEnter);
		eraseDisplay();

		playGame(currentPlayer);

		sortTokens();
		MSMMotorEncoderReset(mmotor_S4_1);
		nMotorEncoder[motorB] = 0;
		displayString(DEFAULT_DISPLAY_LINE, "Please replace cartidges");
		displayString(DEFAULT_DISPLAY_LINE + 1, "press enter once you're done");
		waitButton(buttonEnter);
		eraseDisplay();


		displayString(DEFAULT_DISPLAY_LINE, "Press the enter button to play again");
		displayString(DEFAULT_DISPLAY_LINE + 1, "Enter any other button to exit");

	}
	time1[T2] = 0;
	displayString(DEFAULT_DISPLAY_LINE, "Thank you for playing!");
	while(time1[T2] < 7000){}
	eraseDisplay();

}

/*
void gameReset(int currentCol){
	//dropToken(currentConverPos, 1, )
    displayString(DEFAULT_DISPLAY_LINE, "Press enter to continue playing");
	displayString(DEFAULT_DISPLAY_LINE, "press any other to terminate program");
	while(!getButtonPress(buttonAny)){}
	eraseDisplay();
	if(getButtonPress(buttonEnter)){
		//stillPlaying = 1;
		return;
	}

	else{
	//	stillPlaying = 0;
		return;
	}
}
*/

int gameState(int & currentPlayer)
// assumption: the red = 1 = human, yellow = 2 = robot
{
	int draw = 3, notWon = 0, win = 0;
	if(boardArray[0][0] != 0 && boardArray[0][1] != 0 && boardArray[0][2] != 0 && boardArray[0][3] != 0
		&& boardArray[0][4] != 0 && boardArray[0][5] != 0 && boardArray[0][6] != 0)
	{
		return draw;
	}
	if(currentPlayer == 1)
	{
		win = 1; // human won
	}
	else if(currentPlayer == 2)
	{
		win = 2; // robot won
	}


	for(int row = 0; row < 3 ; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col] == currentPlayer
			&& boardArray[row + 2 ][col] == currentPlayer
			&& boardArray[row + 3][col] == currentPlayer)
			{
				return win;
			} // checks vertical

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row][col + 1] == currentPlayer
			&& boardArray[row][col + 2] == currentPlayer
			&& boardArray[row][col + 3] == currentPlayer)
			{
				return win;
			} // checks horizontal

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col + 1] == currentPlayer
			&& boardArray[row + 2 ][col + 2] == currentPlayer
			&& boardArray[row + 3][col + 3] == currentPlayer)
			{
				return win;
			} // checks +ve slope

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col - 1] == currentPlayer
			&& boardArray[row + 2 ][col - 2] == currentPlayer
			&& boardArray[row + 3][col - 3] == currentPlayer)
			{
				return win;
			} //check -ve slope


		}
	}

	return notWon; //not won if neither the robot nor human has a connect 4
}



void playGame(int & currentPlayer){

	int currentCol = 1;

	while(gameState(currentPlayer) == 0)
	{
		humanMove(currentCol);
		HumanMove2(currentCol);
	}
	return;
}

void humanMove(int currentCol){
	int choiceCol = 1;
	do {
		choiceCol = moveSelect(currentCol);
	} while(!legalCheck(choiceCol));

	dropToken(choiceCol -1 , true); // means human is playing
	return;
}

int moveSelect(int currentCol)
{
	int selectCol = currentCol;
	eraseDisplay();
	displayString(DEFAULT_DISPLAY_LINE, "Current Column: %d", selectCol);

	while(!getButtonPress(buttonEnter))
	{
		if(getButtonPress(buttonUp))
		{
			while(getButtonPress(buttonUp))
			{}

			if(selectCol == 7)
			{
				selectCol = 1;
			}
			else
			{
				selectCol++;
			}

			eraseDisplay();
			displayString(DEFAULT_DISPLAY_LINE, "Current Column: %d", selectCol);

			wait1Msec(500);
		}
		else if(getButtonPress(buttonDown))
		{
			while(getButtonPress(buttonDown))
			{}

			if(selectCol == 1)
			{
				selectCol = 7;
			}
			else
			{
				selectCol--;
			}

			eraseDisplay();
			displayString(DEFAULT_DISPLAY_LINE, "Current Column: %d", selectCol);

			wait1Msec(500);
		}
	}
	while(getButtonPress(buttonEnter))
	{}

	return selectCol;
}

bool legalCheck(int choiceCol)
{
	if(boardArray[0][choiceCol - 1] != 0)
	{
		return false;
	}

	return true;
}

void HumanMove2(int currentCol){
	int choiceCol = 1;
	do {
		choiceCol = moveSelect(currentCol);
	} while(!legalCheck(choiceCol));

	dropToken(choiceCol -1 , false); // means human is playing

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
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;

	wait1Msec(500);
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}



void dropToken(int choiceCol, bool isHumanPlaying)
{
	//nMotorEncoder[motorA] = 0;

	motor[motorA] = 15;
	motor[motorD] = 15;

	while(nMotorEncoder[motorA] > colAngle[choiceCol])
	{}

	clearTimer(T4);
	bool motorActivated = false;
	while(time1[T4] < 5000)
	{
		motorHold(choiceCol);
		if(time1[T4] > 2000 && !motorActivated)
		{
			spinnerMotor(isHumanPlaying);
			motorActivated = true;
		}
	}

	motor[motorA] = motor[motorD] = 0;
	wait1Msec(2000);

	motor[motorA] = -15;
	motor[motorD] = -15;
	while(nMotorEncoder[motorA] < 0)
	{}
	motor[motorA] = 0;
	motor[motorD] = 0;

	return;

}


void motorHold(int choiceCol)
{
		while(nMotorEncoder[motorA] < colAngle[choiceCol])
		{
			motor[motorD] = -1;
			motor[motorA] = -2;
		}
		while(nMotorEncoder[motorA] > colAngle[choiceCol])
		{
			motor[motorD] = 2;
			motor[motorA] = 1;
		}
		motor[motorD] = 1;
		motor[motorA] = -1;

}

/*
void gameReset(int currentCol){
	//dropToken(currentConverPos, 1, )
    displayString(DEFAULT_DISPLAY_LINE, "Press enter to continue playing");
	displayString(DEFAULT_DISPLAY_LINE, "press any other to terminate program");
	while(!getButtonPress(buttonAny)){}
	eraseDisplay();
	if(getButtonPress(buttonEnter)){
		stillPlaying = 1;
		return;
	}

	else{
		stillPlaying = 0;
		return;
	}
}
*/

/*
int gameState(int boardArray[][BOARD_COLUMNS], int currentPlayer)


// assumption: the red = 1 = human, yellow = 2 = robot
{
	int draw = 3, notWon = 0, win = 0;
	if(boardArray[0][0] != 0 && boardArray[0][1] != 0 && boardArray[0][2] != 0 && boardArray[0][3] != 0
		&& boardArray[0][4] != 0 && boardArray[0][5] != 0 && boardArray[0][6] != 0)
	{
		return draw;
	}
	if(currentPlayer == 1)
	{
		win = 1; // human won
	}
	else if(currentPlayer == 2)
	{
		win = 2; // robot won
	}


	for(int row = 0; row < 3 ; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col] == currentPlayer
			&& boardArray[row + 2 ][col] == currentPlayer
			&& boardArray[row + 3][col] == currentPlayer)
			{
				return win;
			} // checks vertical

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row][col + 1] == currentPlayer
			&& boardArray[row][col + 2] == currentPlayer
			&& boardArray[row][col + 3] == currentPlayer)
			{
				return win;
			} // checks horizontal

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col + 1] == currentPlayer
			&& boardArray[row + 2 ][col + 2] == currentPlayer
			&& boardArray[row + 3][col + 3] == currentPlayer)
			{
				return win;
			} // checks +ve slope

			if(boardArray[row][col] == currentPlayer
			&& boardArray[row + 1][col - 1] == currentPlayer
			&& boardArray[row + 2 ][col - 2] == currentPlayer
			&& boardArray[row + 3][col - 3] == currentPlayer)
			{
				return win;
			} //check -ve slope


		}
	}

	return notWon; //not won if neither the robot nor human has a connect 4
}
*/

void sortTokens(){
	MSMMotor(mmotor_S4_1, -1);
	wait1Msec(100);
	bool tokens = true;
	time1[T1] = 0;
	time1[T2] = 0;
	int previousMotor = 100;
	int nextEncoder = 0;

	while(tokens && SensorValue[S1] == false){
  		if(SensorValue[S2] == 4) {
  			motor[motorB] = -35;
  			while(nMotorEncoder[motorB] > -55){}
  			motor[motorB] = 0;
		}

		else if(SensorValue[S2] == 5) {
	 		wait1Msec(500);
	    	motor[motorB] = 35;
  			while(nMotorEncoder[motorB] < 0){}
  			motor[motorB] = 0;
		}

		int timeSample = time1[T1];

		if(time1[T1] >= 1000){

				if(previousMotor == MSMMotorEncoder(mmotor_S4_1)){
				  	displayString(4, "yes");
						MSMMotor(mmotor_S4_1, 1);
						wait1Msec(1000);
						MSMMotor(mmotor_S4_1, -1);
						}
						previousMotor = MSMMotorEncoder(mmotor_S4_1);
						displayString(5, "%f", previousMotor);
						time1[T1] =0;
					}
    }

	motor[motorB] = 50;
  	while(nMotorEncoder[motorB] < -10)
  		{}
  	MSMotorStop(mmotor_S4_1);
  	motor[motorB] = 0;
}


void waitButton(TEV3Buttons buttonName)
{
	while(!getButtonPress(buttonName))
	{}
	while(getButtonPress(buttonName))
	{}

	return;
}
