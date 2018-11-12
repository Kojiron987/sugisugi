#include "Pgm.h"

/* implements Pgm class */


Pgm::Pgm(const char* inputFile)
{
	this->colorArray = nullptr;
	this->inputFile = std::string(inputFile);
	this->isSuccessedOpen = false;
	this->setPgm(void);
}



Pgm::~Pgm()
{
	if(this->colorArray != nullptr) { // new していれば消す
		delete this->colorArray;
	}
}



void Pgm::setPgm()
{
	std::ifstream inFile(this->inputFile, ios::in | ios::binary);

	if(!inFile.is_open())
		return;
	else
		this->fileOpenFlag = true;


	char cData;	// charでファイルを読む
	int iData;	// intでファイルを読む

	while(!inFile.get(cData)) {
		if(this->isComment(cData)) {
			this->skipComment(inFile);
		}

	}



	for(int i = 0; i < this->width; i++)
		for(int j = 0; j < this->height; j++) {
			if(inFile.eof()) {  // 途中でファイルの終端までいった場合
				this->fileOpenFlag = false;  // 読み込みを失敗にしてコンストラクタを抜ける
				return;
			}

		}
}


int Pgm::getWidth()
{
	return this->width;
}


int Pgm::getHeight()
{
	return this->height;
}

int Pgm::getColorSize()
{
	return this->colorSize;
}
