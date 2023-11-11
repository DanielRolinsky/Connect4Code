// Configure Sensors
void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}

/*

motor descriptions:

motor A = left pulley
Motor B = flipper
Motor C1 = spinner at the top 
Motor C2 = spinner at the bottom (with sorter)
Motor D = Right pulley

*/
//Function Prototypes
void playGame();
void configureMotors();
void humanMove();
void moveSelect();
void legalCheck();
void robotMove();
void moveCalc();
void dropTocken();
void sortToken();
void reset();
void 
//Main function
task main()
{
	configureMotors();
	while(SensorValue[S1] = false){}
	

}

void playGame(){
	void humanMove();
	void moveSelect();
	void robotMove();
}

void sortToken()
{

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

void humanMove()
{
	legalCheck();
	
}

void robotMove()
{
	legalCheck();
}