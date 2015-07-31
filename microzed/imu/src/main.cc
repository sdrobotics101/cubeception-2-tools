#include <iostream>
#include "IMU/mpu9250.h"

#define MPU0ADDR 0x00040000
#define MPU1ADDR 0x00050000

int16_t ax0, ay0, az0;
int16_t gx0, gy0, gz0;
int16_t mx0, my0, mz0;

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t mx1, my1, mz1;

int main()
{
	MPU9250 *mpu0 = new MPU9250(MPU0ADDR,0);
	MPU9250 *mpu1 = new MPU9250(MPU1ADDR,0);
	mpu0->reset();
	mpu1->reset();
	mpu0->init(0,0);
	mpu1->init(0,0);
	mpu0->read_robot_raw(&ax0, &ay0, &az0,
			 	   	     &gx0, &gy0, &gz0,
			 	   	     &mx0, &my0, &mz0);
	mpu1->read_robot_raw(&ax1, &ay1, &az1,
				   	     &gx1, &gy1, &gz1,
				   	     &mx1, &my1, &mz1);

	std::cout << "A0:  " << ax0 << " " << ay0 << " " << az0 << std::endl;
	std::cout << "G0:  " << gx0 << " " << gy0 << " " << gz0 << std::endl;
	std::cout << "M0:  " << mx0 << " " << my0 << " " << mz0 << std::endl;

	std::cout << "A1:  " << ax1 << " " << ay1 << " " << az1 << std::endl;
	std::cout << "G1:  " << gx1 << " " << gy1 << " " << gz1 << std::endl;
	std::cout << "M1:  " << mx1 << " " << my1 << " " << mz1 << std::endl;

	delete mpu0;
	delete mpu1;
}
