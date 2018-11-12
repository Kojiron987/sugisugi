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



void Pgm::setPgm()
{
	std::ifstream inFile(this->inputFile, ios::in | ios::binary);

	if(!inFile.is_open())
		return;
	else
		this->fileOpenFlag = true;

	unsigned char data;
	while(!inFile.get(data)) {
		if(this->isComment(data)) {
			this->skipComment(&inFile);
		}
	}
}
