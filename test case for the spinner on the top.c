void spinnerMotor(bool isHumanPlaying);
void configureMotors();


task main()
{
	configureMotors();
	for(int i = 0; i <= 10; i ++){
	spinnerMotor(true);
	wait1Msec(1000);
	spinnerMotor(false);
}
}

void spinnerMotor(bool isHumanPlaying){

if(isHumanPlaying)
	{

		motor[motorC] = 25;
		while (nMotorEncoder[motorC] < 90)
		{}
		motor[motorC] = 0;
	}
	else
	{

		motor[motorC] = -25;
		while (nMotorEncoder[motorC] > -90)
		{}
		motor[motorC] = 0;
	}
}
void configureMotors()
{
 nMotorEncoder[motorC] =  0;


	wait1Msec(500);
	 motor[motorC]= 0 ;
}
