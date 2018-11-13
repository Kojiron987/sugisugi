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
	void isComment(char c);					// コメントかどうかの判定

	std::string inputFile;					// 読み込むファイルの名前
	std::string magic;					// P(123456)
	int width;						// 画像の幅
	int height;						// 画像の縦の大きさ
	int colorSize;						// 輝度を格納
	int *colorArray;					// width * height の画素を格納する
	bool fileOpenFlag;					// false..ファイルを読む込みが失敗した
								// true.. ファイルを正しく読み込めた

};
