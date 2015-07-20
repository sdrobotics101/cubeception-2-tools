#include <iostream>

#include "PS/PSController.h"
#include "Utilities/INI/INIReader.h"

int main()
{
	INIReader iniReader("/usr/local/etc/cubeception.ini");
	if (iniReader.ParseError() < 0) {
		std::cout << "Could not find config file" << std::endl;
		return -1;
	}

	PSController psController(iniReader.GetInteger("ps", "ms0addr", 0x00020000),
							  iniReader.GetInteger("ps", "ms1addr", 0x00030000),
							  iniReader.GetBoolean("ps", "usems0", true),
							  iniReader.GetBoolean("ps", "usems1", true),
							  iniReader.GetReal("ps", "waterdensity", 1000),
						      iniReader.GetReal("ps", "atmosphericpressure", 1000));

	psController.start();

	while (1) {
		std::cout << std::endl;
		std::cout << "D: " << psController.getDepthInMeters() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
