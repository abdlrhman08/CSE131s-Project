#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class FileManager
{
private:
	std::fstream fs;

	int filesize, patchnum;
	const int PATCHSIZE = 31, PARTSIZE = 15;

public:

	std::string read(int patch, int patchPart = 0);
	void write(std::string data, int patch, int patchPart);

	FileManager(std::string filename);
	~FileManager();

};

