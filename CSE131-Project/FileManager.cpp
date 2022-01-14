#include "FileManager.h"

FileManager::FileManager(std::string filename, int patchsize) {
	fs.open(filename.c_str());

	PATCHSIZE = patchsize;

	if (!fs) {
		std::cout << "[ERROR]: file not found" << std::endl;
		return;
	}

	fs.seekg(0, std::ios::end);
	filesize = fs.tellg();
	patchnum = filesize / PATCHSIZE;

	std::cout << "File has " << filesize << " bytes and " << patchnum << " objects" << std::endl;

}

std::string FileManager::read(int patch, int place) {
	std::string buffer;

	fs.seekg((patch * PATCHSIZE), std::ios::beg);
	std::getline(fs, buffer);

	std::string part = buffer.substr(place * PARTSIZE, PARTSIZE);
	for (int i = 0; i < part.length() - 1; i++) {
		if (part.substr(i, 2) == "  ")
			return part.substr(0, i);
	}

	if (part[14] == ' ')
		return part.substr(0, 14);

	return part;
}

int FileManager::getIndex(std::string searchkey) {
	std::string buffer;

	for (int i = 0; i < patchnum; i++) {
		fs.seekg((i * PATCHSIZE), std::ios::beg);
		std::getline(fs, buffer);

		for (int j = 0; j < PATCHSIZE - PARTSIZE; j += PARTSIZE) {
			if (buffer.substr(j, searchkey.length()) == searchkey)
				return i;
		}
	}

	return -1;
}

void FileManager::write(std::string data, int patch, int place) {
	std::string bufferdata(PARTSIZE, ' ');

	for (int i = 0; i < data.length(); i++)
		bufferdata[i] = data[i];
	
	//Can be overwridden on top of deleted part, had to comment to not get lost in this mess
	if (this->getObjectNumber() == patch) {
		int deletedIndex = this->getIndex("DELETED");
		if (deletedIndex != -1) patch = deletedIndex;
	}

	fs.seekp((patch * PATCHSIZE) + (place * PARTSIZE), std::ios::beg);

	if ((PATCHSIZE / PARTSIZE) - 1 == place)
		fs << bufferdata << std::endl;
	else
		fs << bufferdata;
}

void FileManager::deletePatch(int patch) {
	std::string deletestr(PARTSIZE, ' ');
	std::string deletiontext = "DELETED";

	for (int i = 0; i < deletiontext.length(); i++)
		deletestr[i] = deletiontext[i];

	fs.seekp(patch * PATCHSIZE, std::ios::beg);
	
	for (int i = 0; i < (PATCHSIZE / PARTSIZE); i++) {
		if ((PATCHSIZE / PARTSIZE) - 1 == i)
			fs << deletestr << std::endl;
		else
			fs << deletestr;
	}
}

int FileManager::getObjectNumber()  {
	fs.seekg(0, std::ios::end);
	filesize = fs.tellg();
	patchnum = filesize / PATCHSIZE;
	return patchnum;
}

FileManager::~FileManager() { fs.close(); }
