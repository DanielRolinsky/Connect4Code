void spinnerMotor(bool isHumanPlaying);
void configureMotors();
#include "mindsensors-motormux.h"
/*
task main(){
	time1[T1] = 0;
		MSMMUXinit();
		MSMMotor(mmotor_S3_2, 2);

		while(time1[T1] < 100000){displayString(4, "%f", MSMMotorEncoder(mmotor_S3_2));}
		MSMotorStop(mmotor_S3_2);

}
*/
task main()
{
	SensorType[S4] = sensorI2CCustom;
	MSMMUXinit();
	MSMMotorEncoderReset(mmotor_S4_2);
	configureMotors();
	for(int i = 0; i <= 10; i ++){
		spinnerMotor(true);
		wait1Msec(1000);
		spinnerMotor(false);
		wait1Msec(1000);
	}
//	spinnerMotor(true);
//	MSMMotor(mmotor_S3_2, 2);
	//while(nMotorEncoder[motorC] < 360)
//{}
	MSMotorStop(mmotor_S4_2);
}

void spinnerMotor(bool isHumanPlaying){

	if(isHumanPlaying)
	{
		MSMMotor(mmotor_S4_2, 2);
		wait1Msec(500);
		/*while (MSMMotorEncoder(mmotor_S3_2) != 95 && MSMMotorEncoder(mmotor_S3_2) != 94 && MSMMotorEncoder(mmotor_S3_2) != 96){
			MSMMotor(mmotor_S3_2, 1);
			while(MSMMotorEncoder(mmotor_S3_2) < 95){}
			wait1Msec(250);
			MSMMotor(mmotor_S3_2, -1);
			while(MSMMotorEncoder(mmotor_S3_2) > 95){}
			wait1Msec(250);
		displayString(4, "%f", MSMMotorEncoder(mmotor_S3_2));
		}*/
		while (MSMMotorEncoder(mmotor_S4_2) < 95){}
		MSMotorStop(mmotor_S4_2);
	}
	else
	{

		MSMMotor(mmotor_S4_2, -2);
		/*while (MSMMotorEncoder(mmotor_S3_2) > -5){
				while(MSMMotorEncoder(mmotor_S3_2) > -5){
				MSMMotor(mmotor_S3_2, -10);
			}
			while(MSMMotorEncoder(mmotor_S3_2) < -5){
			MSMMotor(mmotor_S3_2, 5);
		}
		displayString(4, "%f", MSMMotorEncoder(mmotor_S3_2));
		MSMotorStop(mmotor_S3_2);
		}*/
		while (MSMMotorEncoder(mmotor_S4_2) > -5){}
		MSMotorStop(mmotor_S4_2);
	return;
}
}

void configureMotors()
{
	MSMMotorEncoderReset(mmotor_S4_2);


	wait1Msec(500);
	MSMotorStop(mmotor_S4_2);
}
