#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

#include "Networking/NetworkServer.hpp"

NetworkServer server;

void processInput(std::string &input);

int main(int argc, char *argv[]) {
	server.open();
	server.start();
	std::string input;
	while (std::getline(std::cin, input)) {
		processInput(input);
	}	
}

void processInput(std::string &input) {
	std::stringstream ss(input);
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(ss, token, ' ')) {
		tokens.push_back(token);
	}

	server.get_n2m_standard_packet()->set_vel_x(std::stod(tokens[0]));
	server.get_n2m_standard_packet()->set_vel_y(std::stod(tokens[1]));
	server.get_n2m_standard_packet()->set_pos_z(std::stod(tokens[2]));
	server.get_n2m_standard_packet()->set_rot_x(std::stod(tokens[3]));
	server.get_n2m_standard_packet()->set_rot_y(std::stod(tokens[4]));
	server.get_n2m_standard_packet()->set_rot_z(std::stod(tokens[5]));

	printf("%8.4f %8.4f %8.4f %8.4f\n", server.get_m2n_standard_packet()->get_orient_x(),
                                      server.get_m2n_standard_packet()->get_orient_y(),
                                      server.get_m2n_standard_packet()->get_orient_z(),
                                      server.get_m2n_standard_packet()->get_pos_z());

	std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(tokens[6])));
}


