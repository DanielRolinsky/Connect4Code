void spinnerMotor(bool isHumanPlaying);
void configureMotors();


task main()
{
	configureMotors();
	for(int i = 0; i <= 5; i ++){
		spinnerMotor(true);
		wait1Msec(1000);
		spinnerMotor(false);
		wait1Msec(1000);
	}
	spinnerMotor(true);
	motor[motorC] = 10;
	while(nMotorEncoder[motorC] < 360)
{}
	motor[motorC] = 0;
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
	nMotorEncoder[motorC] =  0;


	wait1Msec(500);
	motor[motorC]= 0 ;
}
