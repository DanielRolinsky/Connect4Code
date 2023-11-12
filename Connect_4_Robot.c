/*
motor descriptions:

motor A = left pulley
Motor B = flipper
Motor C1 = spinner at the top 
Motor C2 = spinner at the bottom (with sorter)
Motor D = Right pulley
*/
//Function Prototypes


void sensorConfig();
void configureMotors();
void displayAndWait();

void playGame();
void dropToken(); // done
void sortToken();

void humanMove();
void robotMove();

void moveSelect();
void spinnerMotor(); // done
bool legalCheck();
void moveCalc();

void reset();
int gameState(); //gameState() should return 0 if not won, 1 if red won, 2 if yellow won, 3 = draw
//gameState() must check if game is won or board is full

const int CONVEYOR_ANGLE = 5 / (180/PI); // currently angle of slope of CONVEYOR
const int DEFAULT_DISPLAY_LINE = 3;
const int DISTANCE_BETWEEN_TWO_COL = 3.5;

int boardArray[6][7] = 
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
	int currentCol = 0;
	sensorConfig();
	configureMotors();
	
	displayString(DEFAULT_DISPLAY_LINE - 1, "First, place cartridges.");
	displayAndWait("Then, press Enter to play!");

	playGame();

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
	} while(!legalCheck(choiceCol))
	
	dropToken(currentCol, choiceCol, true);

	return;
}

void moveSelect(int currentCol);
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
				selectCol++;
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
	spinnter(true);
	while(tokensLeft && finishSignal){
	if(SensorValue[S1] = ){}
	}
}

void spinnerMotor(bool isHumanPlaying) // at the top!!!!!!
{ 
/*
assumption: the red = 1 = human, yellow = 2 = robot, also that the at the top view of the spinner,
 the cartriage at 180 deg will be the red token and the cartirage at 270 deg will be the yellow cartirage
 FRAME OF REFERENCE: counter clock with is -ve while clockwise is +ve
*/ 

	if(isHumanPlaying) 
	{
	
		motor[motorC1] = 25;
		while (nMotorEncoder[motorC1] < 45)
		{} 
		motor[motorC1] = 0; 
	}
	else 
	{
	
		motor[motorC1] = -25;
		while (nMotorEncoder[motorC1] < -45)
		{} 
		motor[motorC1] = 0; 
	}

	

void displayAndWait(string message, int firstLine = DEFAULT_DISPLAY_LINE, TEV3Buttons buttonName = buttonEnter)
{
	displayString(firstLine, message);

	while(!getButtonPressed(buttonName))
	{}
	while(getButtonPressed(buttonName))
	{}

	eraseDisplay();
}

void configureMotors()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

void reset()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
}

void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}

bool gameState()
{
//stuff that goes inside

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
	}
	else
	{
		motor[MotorA] = motor[MotorD] = 20;
	}
	while (nMotorEncoder[motorA] < countsConversion) // never leaves loop
	{} 
	motor[motorA]=motor[motorD] = 0; 
	// Theorectically we have the hole in the track lined up to  the specified col
	spinnerMotor(isHumanPlaying);
}
