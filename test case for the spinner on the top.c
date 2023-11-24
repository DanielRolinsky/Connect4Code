void spinnerMotor(bool isHumanPlaying);
void configureMotors();
#include "mindsensors-motormux.h"

task main()
{
	MSMMUXinit();
	configureMotors();
	for(int i = 0; i <= 5; i ++){
		spinnerMotor(true);
		wait1Msec(1000);
		spinnerMotor(false);
		wait1Msec(1000);
	}
	spinnerMotor(true);
	MSMMotor(mmotor_S4_1, 1);
	while(nMotorEncoder[motorC] < 360)
{}
	MSMotorStop(mmotor_S4_1);
}

void spinnerMotor(bool isHumanPlaying){

	if(isHumanPlaying)
	{
		MSMMotor(mmotor_S4_1, 1);
		while (MSMMotorEncoder(mmotor_S4_1) < 95)
		{}
		MSMotorStop(mmotor_S4_1);
	}
	else
	{

		MSMMotor(mmotor_S4_1, -1);
		while (MSMMotorEncoder(mmotor_S4_1) > -5)
		{}
		MSMotorStop(mmotor_S4_1);
	}
	return;
}

void configureMotors()
{
	MSMMotorEncoderReset(mmotor_S4_1);


	wait1Msec(500);
	MSMotorStop(mmotor_S4_1);
}
