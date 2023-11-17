/*
motor descriptions:

motor A = left pulley
Motor B = flipper
Motor C1 = spinner at the top 
Motor C2 = spinner at the bottom (with sorter)
Motor D = Right pulley
*/
//Function Prototypes

const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;
const int CONVEYOR_ANGLE = 5 / (180/PI); // currently angle of slope of CONVEYOR
const int DEFAULT_DISPLAY_LINE = 3;
const int DISTANCE_BETWEEN_TWO_COL = 3.5;

void sensorConfig();
void configureMotors();
void waitButton(TEV3Buttons buttonName);

void playGame();
void dropToken(int currentCol, int choiceCol, bool isHumanPlaying); // done
void sortToken();

void humanMove(int currentCol);
void robotMove();

void moveSelect(int currentCol);
void spinnerMotor(bool isHumanPlaying); // done
bool legalCheck(int choiceCol);
void moveCalc();

void gameReset(int currentConverPos);
int gameState(int boardArray[][BOARD_COLUMNS]); //gameState() should return 0 if not won, 1 if red won, 2 if yellow won, 3 = draw
//gameState() must check if game is won or board is full

int boardArray[BOARD_ROWS][BOARD_COLUMNS] = 
    {
	{0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
    }; 

//Main function
task main()
{
	bool stillPlaying
	while(stillPlaying){
		sensorConfig();
		configureMotors();
		
		displayString(DEFAULT_DISPLAY_LINE, "First place cartridges on top");
		displayString(DEFAULT_DISPLAY_LINE + 1, "Then press Enter to play!");
		waitButton(buttonEnter);
		eraseDisplay();

		playGame();
		sortToken();
		displayString(DEFAULT_DISPLAY_LINE, "Please replace cartidges");
		displayString(DEFAULT_DISPLAY_LINE + 1, "press enter once you're done");
		waitButton(buttonEnter);
		eraseDisplay();


		displayString(DEFAULT_DISPLAY_LINE, "Press the enter button to play again");
		displayString(DEFAULT_DISPLAY_LINE + 1, "Enter any other button to exit");
	}
	
	time1[T2] = 0;
	displayString(DEFAULT_DISPLAY_LINE, "Thank you for playing!")
	displayString(DEFAULT_DISPLAY_LINE, "Please leave a rating")
	displayString(DEFAULT_DISPLAY_LINE, "by pressing the enter button 1-5 times")
	displayString(DEFAULT_DISPLAY_LINE, "jk thats not a thing XD")
	while(time1[T2] < 7000){}
	eraseDisplay();
}

int playGame(){
	
	int currentCol = 1;

	while(gameState() == 0)
	{
		humanMove(currentCol);
		robotMove();
	}

}

void humanMove(int currentCol){
	int choiceCol = 1;
	do {
		choiceCol = moveSelect(currentCol);
	} while(!legalCheck(choiceCol));
	
	dropToken(currentCol, choiceCol, true); // means human is playing

	return;
}

int moveSelect(int currentCol);
{
	int selectCol = currentCol;
	eraseDisplay();
	displayString(DEFAULT_DISPLAY_LINE, "Current Column: %d", selectCol);

	while(!getButtonPressed(buttonEnter))
	{
		if(getButtonPressed(buttonRight))
		{
			while(getButtonPressed(buttonRight))
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
		}
		else if(getButtonPressed(buttonLeft))
		{
			while(getButtonPressed(buttonLeft))
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
		}
	}
	while(getButtonPressed(buttonEnter))
	{}

	return selectCol;
}

bool legalCheck(int choiceCol)
{
	if(boardArray[0][choiceCol - 1] != 0)
	{
		return false
	}
	
	return true
}

void robotMove(){
	void moveCalc();
	void dropToken (int currentCol, int colWant, false ); // means robot is playing dummy
}

void sortTokens(){
	motor[motorC2] = -10;
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
		if(nMotorEncoder[motorC2] == perviousMotor){
			time1[T2] = 0;
			while(time1[T2] <= 500){
				motor[motorC2] = 10;
			}
			motor[motorC2] = -10;
		}

		if(time1[T1] == 250){
			previousMotor = nMotorEncoder[motorC2];
			time1[T1] = 0;
		}
	}
	motor[motorB] = 20;
  	while(nMotorEncoder[motorB] < 0){}
  	motor[motorB] = 0;
}

void spinnerMotor(bool isHumanPlaying) // at the top!!!!!!
{ 
/*
assumption: the red = 1 = human, yellow = 2 = robot, also that the at the top view of the spinner,
 the cartriage at 180 deg will be the red token and the cartirage at 270 deg will be the yellow cartirage
 FRAME OF REFERENCE: counter clock with is -ve while clockwise is +ve
*/ 

void spinnerMotor(bool isHumanPlaying);
void configureMotors();


task main()
{
	configureMotors();
	for(int i = 0; i <= 21; i ++){
		spinnerMotor(true);
		wait1Msec(1000);
		spinnerMotor(false);
		wait1Msec(1000);
	}
}

void spinnerMotor(bool isHumanPlaying){

	if(isHumanPlaying)
	{
		motor[motorC1] = 10;
		while (nMotorEncoder[motorC1] < 95)
		{}
		motor[motorC1] = 0;
	}
	
	else
	{
		motor[motorC1] = -10;
		while (nMotorEncoder[motorC1] > -5)
		{}
		motor[motorC1] = 0;
	}
	return;
}

void configureMotors()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;

	wait1Msec(500);
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

}

void waitButton(TEV3Buttons buttonName)
{
	while(!getButtonPressed(buttonName))
	{}
	while(getButtonPressed(buttonName))
	{}

	return;
}

void configureMotors()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

/*
void resegameR()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
}
*/

void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}

int gameState(int boardArray[][BOARD_COLUMNS]) 
// assumption: the red = 1 = human, yellow = 2 = robot
{
	if(boardArray[0][0] != 0 && boardArray[0][1] != 0 && boardArray[0][2] != 0 && boardArray[0][3] != 0
		&& boardArray[0][4] != 0 && boardArray[0][5] != 0 && boardArray[0][6] != 0)
	{
		return draw;
	}

	int redTokenCurrent = 1, yellowTokenCurrent = 2, humanWon = 1, robotWon = 2, draw = 3, notWon = 0;
	
	for(int row = 0; row < 6; row++)
	{
		for(int col = 0; col < 7; col++)
		{
			if(boardArray[row][col] == redTokenCurrent
			&& boardArray[row + 1][col] == redTokenCurrent
			&& boardArray[row + 2 ][col] == redTokenCurrent
			&& boardArray[row + 3][col] == redTokenCurrent)
			{
				return humanWon;
			} // checks vertical
			
			if(boardArray[row][col] == redTokenCurrent
			&& boardArray[row][col + 1] == redTokenCurrent
			&& boardArray[row][col + 2] == redTokenCurrent
			&& boardArray[row][col + 3] == redTokenCurrent)
			{
				return humanWon;
			} // checks horizontal

			if(boardArray[row][col] == redTokenCurrent
			&& boardArray[row + 1][col + 1] == redTokenCurrent
			&& boardArray[row + 2 ][col + 2] == redTokenCurrent
			&& boardArray[row + 3][col + 3] == redTokenCurrent)
			{
				return humanWon;
			} // checks +ve slope

			if(boardArray[row][col] == redTokenCurrent
			&& boardArray[row - 1][col + 1] == redTokenCurrent
			&& boardArray[row - 2 ][col + 2] == redTokenCurrent
			&& boardArray[row - 3][col + 3] == redTokenCurrent)
			{
				return humanWon;
			} //check -ve slope

			// same exact thing but for robot now :)
			if(boardArray[row][col] == yellowTokenCurrent
			&& boardArray[row + 1][col] == yellowTokenCurrent
			&& boardArray[row + 2 ][col] == yellowTokenCurrent
			&& boardArray[row + 3][col] == yellowTokenCurrent)
			{
				return robotWon;
			} // checks vertical
			
			if(boardArray[row][col] == yellowTokenCurrent
			&& boardArray[row][col + 1] == yellowTokenCurrent
			&& boardArray[row][col + 2] == yellowTokenCurrent
			&& boardArray[row][col + 3] == yellowTokenCurrent)
			{
				return robotWon;
			} // checks horizontal

			if(boardArray[row][col] == yellowTokenCurrent
			&& boardArray[row + 1][col + 1] == yellowTokenCurrent
			&& boardArray[row + 2 ][col + 2] == yellowTokenCurrent
			&& boardArray[row + 3][col + 3] == yellowTokenCurrent)
			{
				return robotWon;
			} // checks +ve slope

			if(boardArray[row][col] == yellowTokenCurrent
			&& boardArray[row - 1][col + 1] == yellowTokenCurrent
			&& boardArray[row - 2 ][col + 2] == yellowTokenCurrent
			&& boardArray[row - 3][col + 3] == yellowTokenCurrent)
			{
				return robotWon;
			} //check -ve slope


		}
	}
		
	return notWon; //not won if neither the robot nor human has a connect 4
}
	

void dropToken(int currentCol, int choiceCol, bool isHumanPlaying)
{
	float colDx= 0;
	float colHyp = 0;
	colDx = choiceCol-currentCol;
	colDx *= DISTANCE_BETWEEN_TWO_COL;
	colHyp = colDx / cos(CONVEYOR_ANGLE) // which is 5 deg angle is rad
	float countsConversion = colHyp * 180 / (2.75*PI);
	nMotorEncoder[motorA] = 0;
	if (countsConversion < 0)
	{
		motor[MotorA] = motor[MotorD] = -20;
		while (nMotorEncoder[motorA] > countsConversion) 
		{} 
		motor[motorA]=motor[motorD] = 0;
	}
	else
	{
		motor[MotorA] = motor[MotorD] = 20;
		while (nMotorEncoder[motorA] < countsConversion) // never leaves loop
		{} 
		motor[motorA]=motor[motorD] = 0;
	} 
	// Theorectically we have the hole in the track lined up to  the specified col
	spinnerMotor(isHumanPlaying);
}

void gameReset(int currentConverPos, bool stillPlaying){
	//dropToken(currentConverPos, 1, )
    stringDisplay(DEFAULT_DISPLAY_LINE, "Press enter to continue playing");
	stringDIsplay(DEFUALT_DISPLAY_LINE, "press any other to terminate program");
	while(!getButtonPressed(buttonAny)){}
	eraseDisplay();
	if(getButtonPressed(buttonEnter)){
		stillPlaying = 1;
		return;
	}
		
	else{
		stillPlaying = 0;
		return;
	}
}