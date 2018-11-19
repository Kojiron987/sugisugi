#include "Pgm.h"

/* implements Pgm class */
const int Pgm::COMMENT = '#';
const int Pgm::NEWLINE = '\n';
const int Pgm::MAX_IGNORE = 1024; // 1024byteまでのコメントを許す
const int Pgm::MAGIC = 0;
const int Pgm::WIDTH = 1;
const int Pgm::HEIGHT = 2;
const int Pgm::COLOR = 3;
const int Pgm::READEND = 4;


Pgm::Pgm()
{
	this->readSucceedFlag = false;
	this->inputFile = "";
	this->magic = "";
	this->width = 0;						// 画像の幅
	this->height = 0;						// 画像の縦の大きさ
	this->colorSize = 0;						// 輝度を格納

}



Pgm::~Pgm()
{

}

void Pgm::init(const char* inputFile)
{
	this->readSucceedFlag = false;
	this->inputFile = std::string(inputFile);

	int data; 					// ファイルから一文字ずつ読み取るときに代入する
	int pgmFlag = Pgm::MAGIC;

	std::ifstream fin(this->inputFile, std::ios::in | std::ios::binary);
	if(!fin.is_open()) {
		std::cerr << "Failed to open" << this->inputFile <<  "." << std::endl;
		return;
	}

	/* Pgmファイルの要素を読み込む */

	while (!fin.eof()) {
		data = fin.get();

		if(data == Pgm::COMMENT) {		// コメントは改行まで飛ばす
				fin.ignore(Pgm::MAX_IGNORE, Pgm::NEWLINE);
		}
		else if(isspace(data)) {
			continue;
		}
		else {
			fin.putback((char)data);						//  一文字戻す
			pgmFlag = this->setPgmToken(fin, pgmFlag);
		}

		if(pgmFlag == Pgm::READEND) {				// finished reading pgm token
			this->readSucceedFlag = true;
			this->colorStartSeeker = fin.tellg();   // どこから画像データが始まるかを記録する
			fin.close();
			return;																	// 最後まで読めたらFlagをtrueにして終了
		}
	}
	return;
}



int Pgm::setPgmToken(std::ifstream& fin, int state)
{
	std::string token;
	int c;
	while(!isspace(c = fin.get()) && !fin.eof())        //　区切り文字が現れるまで読み取る
	{
		token.push_back((char)c);
	}

	switch (state) {
		case Pgm::MAGIC:
			this->magic = token;
			return Pgm::WIDTH;
		case Pgm::WIDTH:
			this->width = std::stoi(token, nullptr, 10);    // 10進数でstringからintへ変換
			return Pgm::HEIGHT;
		case Pgm::HEIGHT:
			this->height = std::stoi(token, nullptr, 10);
			return Pgm::COLOR;
		case Pgm::COLOR:
			this->colorSize = std::stoi(token, nullptr, 10);    // 10進数でstringからintへ変換
			return Pgm::READEND;
		default:
			break;
		}
		return -1;
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

bool Pgm::is_openSucceed()
{
	return this->readSucceedFlag;
}

void Pgm::printPgmToken()
{
	std::cout << "magic number: " << this->magic
						<< " width: " << this->width
						<< " height: " << this->height
						<< " colorSize: " << this->colorSize << std::endl;
	return;
}

bool Pgm::setImageMatrix(std::vector<int>& vec)
{
	std::ifstream fin(this->inputFile, std::ios::in | std::ios::binary);
	if(!fin.is_open()) {
		std::cerr << "Failed to open" << this->inputFile <<  "." << std::endl;
		return false;
	}

	fin.seekg(this->colorStartSeeker, fin.beg);

	for(int i = 0; i < this->height; i++)
		for(int j = 0; j < this->width; j++)
			vec[i * this->width + j] = fin.get();
	fin.close();
	return true;
}

bool Pgm::setImageMatrix(int *arr)
{
	std::ifstream fin(this->inputFile, std::ios::in | std::ios::binary);
	if(!fin.is_open()) {
		std::cerr << "Failed to open" << this->inputFile <<  "." << std::endl;
		return false;
	}

	fin.seekg(this->colorStartSeeker, fin.beg);

	for(int i = 0; i < this->height; i++)
		for(int j = 0; j < this->width; j++)
			arr[i * this->width + j] = fin.get();
	fin.close();
	return true;
}

bool Pgm::writePgm(const std::string& outFile, const std::vector<int> vec)
{
	std::ofstream fout(outFile, std::ios::out | std::ios::binary);
	if(fout.is_open()) {
		fout << this->magic << std::endl;
		fout << this->width<< std::endl;
		fout << this->height << std::endl;
		fout << this->colorSize << std::endl;

		for(int i = 0; i < this->height; i++)
			for(int j = 0; j < this->width; j++)
				fout.put((char)vec[i * this->width + j]);

		fout.close();
		return true;
	}
	else {
		std::cerr << "Failed to open " << outFile << std::endl;
		return false;
	}
}




bool Pgm::writePgm(const std::string& outFile, const int *arr)
{
	std::ofstream fout(outFile, std::ios::out | std::ios::binary);
	if(fout.is_open()) {
		fout << this->magic << std::endl;
		fout << this->width<< std::endl;
		fout << this->height << std::endl;
		fout << this->colorSize << std::endl;

		for(int i = 0; i < this->height; i++)
			for(int j = 0; j < this->width; j++)
				fout.put((char)arr[i * this->width + j]);

		fout.close();
		return true;
	}
	else {
		std::cerr << "Failed to open " << outFile << std::endl;
		return false;
	}
}

std::ostream &operator<<(std::ostream &os, const Pgm &pgm)
{
	os << "magic number: " << pgm.magic
		 << " width: " << pgm.width
		 << " height: " << pgm.height
		 << " colorSize: " << pgm.colorSize;

	return os;
}
