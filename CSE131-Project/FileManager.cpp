#include "FileManager.h"

FileManager::FileManager(std::string filename) {
	fs.open(filename.c_str());

	if (!fs) {
		std::cout << "[ERROR]: file nout found" << std::endl;
		return;
	}

	fs.seekg(0, std::ios::end);
	filesize = fs.tellg();
	std::cout << "File has " << filesize << " bytes" << std::endl;

}

std::string FileManager::read(int patch, int place) {
	std::string buffer;

	fs.seekg((patch * PATCHSIZE), std::ios::beg);
	std::getline(fs, buffer);

	return buffer.substr(place * PARTSIZE, PARTSIZE);
}

void FileManager::write(std::string data, int patch, int place) {
	std::string bufferdata( PARTSIZE, ' ');

	for (int i = 0; i < data.length(); i++)
		bufferdata[i] = data[i];

	fs.seekp((patch * PATCHSIZE) + (place * PARTSIZE));
	fs << bufferdata;
}

FileManager::~FileManager() { fs.close(); }
