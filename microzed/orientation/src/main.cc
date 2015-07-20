#include <iostream>

#include "IMU/IMUController.h"
#include "Utilities/INI/INIReader.h"

int main()
{
	INIReader iniReader("/usr/local/etc/cubeception.ini");
	if (iniReader.ParseError() < 0) {
		std::cout << "Could not find config file" << std::endl;
		return -1;
	}

	Eigen::Vector3d mpu0AccBias;
	Eigen::Vector3d mpu1AccBias;
	Eigen::Vector3d mpu0GyroBias;
	Eigen::Vector3d mpu1GyroBias;
	Eigen::Vector3d mpu0MagBias;
	Eigen::Vector3d mpu1MagBias;
	Eigen::Matrix3d mpu0MagTransform;
	Eigen::Matrix3d mpu1MagTransform;

	mpu0AccBias(XAXIS) = iniReader.GetReal("imu", "mpu0accbiasx", 0);
	mpu0AccBias(YAXIS) = iniReader.GetReal("imu", "mpu0accbiasy", 0);
	mpu0AccBias(ZAXIS) = iniReader.GetReal("imu", "mpu0accbiasz", 0);

	mpu1AccBias(XAXIS) = iniReader.GetReal("imu", "mpu1accbiasx", 0);
	mpu1AccBias(YAXIS) = iniReader.GetReal("imu", "mpu1accbiasy", 0);
	mpu1AccBias(ZAXIS) = iniReader.GetReal("imu", "mpu1accbiasz", 0);

	mpu0GyroBias(XAXIS) = iniReader.GetReal("imu", "mpu0gyrobiasx", 0);
	mpu0GyroBias(YAXIS) = iniReader.GetReal("imu", "mpu0gyrobiasy", 0);
	mpu0GyroBias(ZAXIS) = iniReader.GetReal("imu", "mpu0gyrobiasz", 0);

	mpu1GyroBias(XAXIS) = iniReader.GetReal("imu", "mpu1gyrobiasx", 0);
	mpu1GyroBias(YAXIS) = iniReader.GetReal("imu", "mpu1gyrobiasy", 0);
	mpu1GyroBias(ZAXIS) = iniReader.GetReal("imu", "mpu1gyrobiasz", 0);

	mpu0MagBias(XAXIS) = iniReader.GetReal("imu", "mpu0magbiasx", 0);
	mpu0MagBias(YAXIS) = iniReader.GetReal("imu", "mpu0magbiasy", 0);
	mpu0MagBias(ZAXIS) = iniReader.GetReal("imu", "mpu0magbiasz", 0);

	mpu1MagBias(XAXIS) = iniReader.GetReal("imu", "mpu1magbiasx", 0);
	mpu1MagBias(YAXIS) = iniReader.GetReal("imu", "mpu1magbiasy", 0);
	mpu1MagBias(ZAXIS) = iniReader.GetReal("imu", "mpu1magbiasz", 0);

	mpu0MagTransform(0,0) = iniReader.GetReal("imu", "mpu0magtransform00", 0);
	mpu0MagTransform(0,1) = iniReader.GetReal("imu", "mpu0magtransform01", 0);
	mpu0MagTransform(0,2) = iniReader.GetReal("imu", "mpu0magtransform02", 0);
	mpu0MagTransform(1,0) = iniReader.GetReal("imu", "mpu0magtransform10", 0);
	mpu0MagTransform(1,1) = iniReader.GetReal("imu", "mpu0magtransform11", 0);
	mpu0MagTransform(1,2) = iniReader.GetReal("imu", "mpu0magtransform12", 0);
	mpu0MagTransform(2,0) = iniReader.GetReal("imu", "mpu0magtransform20", 0);
	mpu0MagTransform(2,1) = iniReader.GetReal("imu", "mpu0magtransform21", 0);
	mpu0MagTransform(2,2) = iniReader.GetReal("imu", "mpu0magtransform22", 0);

	mpu1MagTransform(0,0) = iniReader.GetReal("imu", "mpu1magtransform00", 0);
	mpu1MagTransform(0,1) = iniReader.GetReal("imu", "mpu1magtransform01", 0);
	mpu1MagTransform(0,2) = iniReader.GetReal("imu", "mpu1magtransform02", 0);
	mpu1MagTransform(1,0) = iniReader.GetReal("imu", "mpu1magtransform10", 0);
	mpu1MagTransform(1,1) = iniReader.GetReal("imu", "mpu1magtransform11", 0);
	mpu1MagTransform(1,2) = iniReader.GetReal("imu", "mpu1magtransform12", 0);
	mpu1MagTransform(2,0) = iniReader.GetReal("imu", "mpu1magtransform20", 0);
	mpu1MagTransform(2,1) = iniReader.GetReal("imu", "mpu1magtransform21", 0);
	mpu1MagTransform(2,2) = iniReader.GetReal("imu", "mpu1magtransform22", 0);

	IMUController imuController(iniReader.GetInteger("imu", "mpu0addr", 0x00040000),
								iniReader.GetInteger("imu", "mpu1addr", 0x00050000),
								iniReader.GetReal("imu", "combine", 0.8),
								mpu0AccBias,
								mpu1AccBias,
								mpu0GyroBias,
								mpu1GyroBias,
								mpu0MagBias,
								mpu1MagBias,
								mpu0MagTransform,
								mpu1MagTransform);

	imuController.start();

	while (1) {
		std::cout << std::endl;
		std::cout << "X: " << imuController.getXRotation() << std::endl;
		std::cout << "Y: " << imuController.getYRotation() << std::endl;
		std::cout << "Z: " << imuController.getZRotation() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
