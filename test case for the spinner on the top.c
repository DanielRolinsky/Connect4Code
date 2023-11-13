void spinnerMotor(bool isHumanPlaying);

task main()
{
spinnerMotor(true);
}

void spinnerMotor(bool isHumanPlaying) // at the top!!!!!!
{
	while(!getButtonPress(buttonEnter))
	{

		if(getButtonPress(buttonRight))
		{
				motor[motorC] = 25;
				while (nMotorEncoder[motorC] < 45)
				{}
				motor[motorC] = 0;
		}
		else if(getButtonPress(buttonLeft))
		{
			motor[motorC] = -25;
			while (nMotorEncoder[motorC] < 45)
			{}
			motor[motorC] = 0;
		}
	}
	while(getButtonPress(buttonEnter))
	{}

}
