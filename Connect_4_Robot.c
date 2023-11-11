// Configure Sensors
void sensorConfig() {
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
}

//Function Prototypes
void playGame();

void humanMove();
void moveSelect();
void legalCheck();

void robotMove();
void moveCalc();


void dropTocken();

//Main function
task main()
{
	while(SensorValue[S1] = false){}


}

//Playing Function

	//HumanMove Function
		//moveSelect
		//Legal Move check function
		//Drop Token Function

	//RobotMove Function
		//MiniMax Function
		//Drop Token Function

//Sorting Function
	//

// WHATS UPP FUCKERSSS!!!!

// helooo!!!



// this is a test