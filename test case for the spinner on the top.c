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

if(isHumanPlaying)
	{

		motor[motorC] = 25;
		while (nMotorEncoder[motorC] < 45)
		{}
		motor[motorC] = 0;
	}
	else
	{

		motor[motorC] = -25;
		while (nMotorEncoder[motorC1] > -45)
		{}
		motor[motorC] = 0;
	}

	void configureMotors()
{
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	wait1Msec(500);
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD]= 0 ;
}
