#include "Pgm.h"

/* implements Pgm class */


Pgm::Pgm(const char* inputFile)
{
	this->inputFile = std::string(inputFile);
	this->isSuccessedOpen = false;
	this->setPgm(void);
}



Pgm::~Pgm()
{
	delete this->colorArray;
}



Pgm::setPgm()
{
	std::ifstream inFile(this->inputFile, 
}

