#pragma once

		/*
		Pgmファイルの読み取りを行う
 		P5にしか対応していない
		*/

#include<string>
#include<fstream>
#include<iostream>

class Pgm
{
public:
	Pgm(const char *inputFile);
	~Pgm();

	int getWidth(void);		// Pgmファイルの幅を返す
	int getHeight(void);	// Pgmファイルの縦の大きさを返す
	int getColorSize(void);		// Pgmファイルの輝度の数を返す
	bool isSucceedOpen(void);	// ファイルを正しく読めたかどうかを呼び出し側からこれで判定する
	void printPgmToken(void);		// magic, width, height, colorSizeの順でPgmファイルの要素を返す



private:

	void skipComment(std::ifstream &inFile);  // Pgmファイルのコメントをスキップする
	void setPgm(void);					// width, height, colorSize, colorArrayにPgmファイルの属性を格納
	void isComment(char c);		

	std::string inputFile;
	std::string magic;
	int width;
	int height;
	int colorSize;
	int *colorArray;
	bool fileOpenFlag;

};
