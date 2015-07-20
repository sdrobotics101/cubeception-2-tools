#include <iostream>
#include <unistd.h>

#include "IMU/mpu9250.h"

#define SAMPLE_SIZE 100

int main(int argc, char *argv[])
{
	MPU9250 *mpu0 = new MPU9250(0x00040000, 0);
	MPU9250 *mpu1 = new MPU9250(0x00050000, 0);

	double mpu0Xavg = 0;
	double mpu0Yavg = 0;
	double mpu0Zavg = 0;
	double mpu1Xavg = 0;
	double mpu1Yavg = 0;
	double mpu1Zavg = 0;

	double mpu0Xcurr = 0;
	double mpu0Ycurr = 0;
	double mpu0Zcurr = 0;
	double mpu1Xcurr = 0;
	double mpu1Ycurr = 0;
	double mpu1Zcurr = 0;

	double a;

	for (int i = 0;i < SAMPLE_SIZE;i++) {
		mpu0->read_robot(&mpu0Xcurr, &mpu0Ycurr, &mpu0Zcurr,
				   	   	 &a, &a, &a,
				   	   	 &a, &a, &a);
		mpu1->read_robot(&mpu1Xcurr, &mpu1Ycurr, &mpu1Zcurr,
				   	     &a, &a, &a,
				   	     &a, &a, &a);
		mpu0Xavg += mpu0Xcurr;
		mpu0Yavg += mpu0Ycurr;
		mpu0Zavg += mpu0Zcurr;
		mpu1Xavg += mpu1Xcurr;
		mpu1Yavg += mpu1Ycurr;
		mpu1Zavg += mpu1Zcurr;
		usleep(10000);
	}
	mpu0Xavg /= SAMPLE_SIZE;
	mpu0Yavg /= SAMPLE_SIZE;
	mpu0Zavg /= SAMPLE_SIZE;
	mpu1Xavg /= SAMPLE_SIZE;
	mpu1Yavg /= SAMPLE_SIZE;
	mpu1Zavg /= SAMPLE_SIZE;

	std::cout << "MPU0: " << mpu0Xavg << " " << mpu0Yavg << " " << mpu0Zavg << std::endl;
	std::cout << "MPU1: " << mpu1Xavg << " " << mpu1Yavg << " " << mpu1Zavg << std::endl;
	delete mpu0;
	delete mpu1;
	return 0;
}
