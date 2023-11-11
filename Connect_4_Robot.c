// Configure Sensors


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
void gameState();

//Main function
task main()
{
	sensorConfig();
	configureMotors();
	while(SensorValue[S1] = false){}
	

}

void playGame(){
	
	void humanMove();
	void robotMove();
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

void displayAndWait(TEV3Buttons buttonName, int firstLine, string message)
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
void gameState()
{


}