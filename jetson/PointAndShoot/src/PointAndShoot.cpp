#include <iostream>
#include <string>
#include <thread>
#include <math.h>

#include "Networking/NetworkServer.hpp"

NetworkServer server;

int main(int argc, char *argv[]) {
	server.open();
	server.start();
	while(1) {
		std::cout << "WAITING" << std::endl;
		std::cout.flush();
		while (server.get_m2n_standard_packet()->get_health() < 1.0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << "STARTING" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		double heading = server.get_m2n_standard_packet()->get_orient_z();
		server.get_n2m_standard_packet()->set_rot_z(heading);
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		double xComp = cos(heading * (M_PI/180));
		double yComp = sin(heading * (M_PI/180));
		if (std::abs(xComp) > std::abs(yComp)) {
			double scale = (100/std::abs(xComp));
			xComp *= scale;
			yComp *= scale;
		} else {
			double scale = (100/std::abs(yComp));
			xComp *= scale;
			yComp *= scale;
		}
		server.get_n2m_standard_packet()->set_vel_x(xComp);
		server.get_n2m_standard_packet()->set_vel_y(yComp);
		server.get_n2m_standard_packet()->set_pos_z(2);
		printf("H: %f, X: %f, Y: %f\n", heading, xComp, yComp);
		std::cout.flush();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		while (server.get_m2n_standard_packet()->get_health() > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(20));	
		}
		server.get_n2m_standard_packet()->set_vel_x(0);
		server.get_n2m_standard_packet()->set_vel_y(0);
		server.get_n2m_standard_packet()->set_pos_z(0);
		
		std::cout << "FINISHED" << std::endl;
	}
}
