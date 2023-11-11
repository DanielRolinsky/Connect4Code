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
void legalCheck();
void moveCalc();

void reset();
bool gameState(); //gameState() should be used to assess if game is won or not & return a bool value

const int DEFAULT_DISPLAY_LINE = 3;

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

void playGame(){
	
	while(!gameState())
	{
		humanMove();
		robotMove();
	}

}

void humanMove(){
	void moveSelect();
	void legalCheck();
	void dropToken();
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
	nMotorEncoder[motorA]= nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

void reset()
{
	nMotorEncoder[motorA]= nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
}

void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}

bool gameState()
{


}

void dropToken(int currentCol, int colWant)
{
	float colDx= 0;
	float colHyp = 0;
	colDx = colWant-currentCol;
	colDx *= DISTANCE_BETWEEN_TWO_COL;
	colHyp = colDx / cos(0.08726646) // which is 5 deg angle is rad
	float countsConversion = colHyp * 180 / (2.75*PI);
	nMotorEncoder[motorA] = 0;
	motor[MotorA] = motor[MotorD] = 20;
	while (nMotorEncoder[motorA] < countsConversion)
	{} 
	motor[motorA]=motor[motorD] = 0; 
}
