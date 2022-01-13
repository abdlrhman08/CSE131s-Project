#pragma once

#include "CarsData.h"
#include "FileManager.h"

#include <vector>

namespace ProgramLoop {
	
	void run();
	void rent(std::string plate, std::string name, std::vector<CarsData>& cars, FileManager &fs);
}
