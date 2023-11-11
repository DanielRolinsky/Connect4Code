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
void dropToken();
void sortToken();

void humanMove();
void robotMove();

void moveSelect();
bool legalCheck();
void moveCalc();

void reset();
int gameState(); //gameState() should return 0 if not won, 1 if red won, 2 if yellow won, 3 = draw
//gameState() must check if game is won or board is full

const int DEFAULT_DISPLAY_LINE = 3;
const int DISTANCE_BETWEEN_TWO_COL = 3.5;
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

	dropToken();
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

bool legalCheck()
{

}

void robotMove(){
	void moveCalc();
	void dropToken();
}

void sortTokens(){
	spinnter(true);
	while(tokensLeft && finishSignal){
	if(SensorValue[S1] = ){}
	}
}

void spinnerMotor(bool state = false){
	if(state) motor[motorC1] = 25;
	else motor[motorC1] = 0;
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


}

void dropToken(int currentCol, int colWant, int )
{
	float colDx= 0;
	float colHyp = 0;
	colDx = colWant-currentCol;
	colDx *= DISTANCE_BETWEEN_TWO_COL;
	colHyp = colDx / cos(0.08726646) // which is 5 deg angle is rad
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
	while (nMotorEncoder[motorA] < countsConversion)
	{} 
	motor[motorA]=motor[motorD] = 0; 
	// Theorectically we have the hole in the track lined up to  the specified col

}
