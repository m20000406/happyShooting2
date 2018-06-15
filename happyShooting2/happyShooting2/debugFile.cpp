#include "PCH.h"
#include <fstream>
#include <iostream>
#include <string>

#include "debugFile.h"

debugFile* instance = nullptr;
std::ofstream* ifs = nullptr;

void debugFile::Create(){
	if (instance == nullptr) {
	instance = new debugFile();
		ifs = new std::ofstream("../../debug.txt");
	}
}

void debugFile::Destroy() {
	if (ifs != nullptr) {
		for (int i = 0; i < 4; i++)*ifs << std::endl;
		delete ifs;
		ifs = nullptr;
	}
}

debugFile& debugFile::operator() () {
	return *instance;
}

void debugFile::write(std::string str) {
	*ifs << str << std::endl;
}