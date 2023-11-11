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
int gameState(); //gameState() should return 0 if not won, 1 if red won, 2 if yellow won, 3 = draw
//gameState() must check if game is won or board is full

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

int playGame(){
	
	while(gameState() == 0)
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
	MotorEncoder[motorA]= nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}

void reset()
{
	MotorEncoder[motorA]= nMotorEncoder[motorB]= nMotorEncoder[motorC]= nMotorEncoder[motorD] = 0;
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
	int col_x_axis_Displacement= 0;
	col_x_axis_Displacement = colWant-currentCol;
	col_x_axis_Displacement*= DISTANCE_BETWEEN_TWO_COL;
	col_hypotnuse_Displacement = col_x_axis_Displacement / cos(0.08726646) // which is angle is rad
	m
}