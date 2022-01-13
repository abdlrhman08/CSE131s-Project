#include "ProgramLoop.h"

#include "Renter.h"
#include "FileManager.h"

#include <string>
#include <iostream>
#include <vector>

void ProgramLoop::rent(std::string plate, std::string name, std::vector<CarsData>& cars, FileManager& fs) {
	for (int i = 0; i < cars.size(); i++) {
		if (cars[i].get_license_plates_number() == plate && cars[i].get_renter() == "not rented") {
			cars[i].set_Renter(name);
			fs.write(name, fs.getIndex(plate), 3);
		}
	}
}

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


		if (command == "rent") {
			std::cout << "Please select on of the following cars by plate number: " << std::endl;
			int index = 1;
			for (int i = 0; i < carsData.getObjectNumber(); i++) {
				if (cars[i].get_renter() == "not rented") {
					std::cout << index << ". model: " << cars[i].get_car_model() << ", plate number: " << cars[i].get_license_plates_number() << std::endl;
					index++;
				}
			}

			std::string plate;
			std::cin >> plate;
			std::cout << "Please enter your name" << std::endl;
			std::string name;
			std::getline(std::cin, name);
				rent(plate, name, cars ,carsData);
			std::cout << carsData.read(3, 3) << std::endl;
		}
		else if (command == "exit")
			running = false;
	}

}
