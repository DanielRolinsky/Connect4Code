
task main()
{

	motor[motorC] = 20;

	bool exitProgram = false;
	time1[T1] = 0;
	while(exitProgram == false)
	{
		if(SensorValue[S1] == 1 && time1[T1] > 1500)
		{
				 exitProgram = true;
		}
		else if(SensorValue[S1] == 0)
		{
		time1[T1] = 0;
		}

	}
	motor[motorC] = 0;

}
