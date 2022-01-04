#include <iostream>

#include "FileManager.h"

int main() {
	std::cout << "Hello" << std::endl;

	FileManager fs("data.txt");
	std::cout << fs.read(0, 0) << std::endl;
	fs.write("Ahmed", 1, 1);

	return 0;
}