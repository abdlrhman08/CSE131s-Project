#include "ProgramLoop.h"

#include "Renter.h"
#include "CarsData.h"
#include "FileManager.h"

#include <string>
#include <iostream>
#include <vector>

void ProgramLoop::run() {
	bool running = true;

	std::vector<Renter> renters;
	std::vector<CarsData> cars;
	std::string command;

	FileManager driversData("driversData.csv", 152);
	FileManager carsData("carsData.csv", 122);

	for (int i = 0; i < driversData.getObjectNumber(); i++) {
		Renter newRenter(std::stoll(driversData.read(i, 0)), driversData.read(i, 1), driversData.read(i, 2), std::stoi(driversData.read(i, 3)), std::stoll (driversData.read(i, 4)));
		renters.push_back(newRenter);
	}

	for (int i = 0; i < carsData.getObjectNumber(); i++) {
		CarsData newCar(carsData.read(i, 0), carsData.read(i, 1), carsData.read(i, 2), carsData.read(i, 3));
		cars.push_back(newCar);
	}

	while (running) {
		std::cout << "Please enter your command, for help type '?'" << std::endl;
		std::cin >> command;


		if (command == "show") {
			for (int i = 0; i < renters.size(); i++)
				std::cout << renters[i].get_Name() << std::endl;
		}
		else if (command == "showcars")
		{
			for (int i = 0; i < cars.size(); i++)
				std::cout << cars[i].get_owner() << std::endl;
		}
		else if (command == "rent") {
			long number;
			std::cout << "Please enter your number";
		}
		else if (command == "exit")
			running = false;
	}

}
