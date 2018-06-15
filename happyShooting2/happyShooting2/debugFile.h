#pragma once
#include <string>

class debugFile {
public:
	static void write(std::string);
	static void Create();
	static void Destroy();
	debugFile& operator() ();
};