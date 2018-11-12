#pragma once

#include<string>
#include<fstream>
#include<iostream>

class Pgm
{
public:
	Pgm(const char*  inputFile);
	~Pgm();

	int getWidth(void);
	int getHeight(void);
	int getColorSize(void);
	void printPgmToken(void);


private:

	void skipComment(const std::ifstream inFile);
	void setPgm(void);
	
	std::string inputFile;
	std::string magic;
	int width;
	int height;
	int colorSize;
	int *colorArray;

};
