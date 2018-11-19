#pragma once

		/*
		Pgmファイルの読み取りを行う
 		P5にしか対応していない
		エラーチェックも未対応
		*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctype.h>

class Pgm
{

	public:
		Pgm(const char *inputFile);
		virtual ~Pgm();
		void init(void);  // 初期化

		int getWidth(void);		// Pgmファイルの幅を返す
		int getHeight(void);	// Pgmファイルの縦の大きさを返す
		int getColorSize(void);		// Pgmファイルの輝度の数を返す
		bool is_openSucceed(void);	// ファイルを正しく読めたかどうかを呼び出し側からこれで判定する
		void printPgmToken(void);		// magic, width, height, colorSizeの順でPgmファイルの要素を返す
		bool setImageMatrix(std::vector<int>& vec);
		bool writePgm(const std::string& outFile, const std::vector<int> vec);
		bool setImageMatrix(int *arr);
		bool writePgm(const std::string& outFile, const int *arr);
		friend std::ostream &operator<<(std::ostream &os, const Pgm &pgm);     	// overload << operator
																																						// this behavor is same as printPgmToken function.
private:

	int setPgmToken(std::ifstream& fin, int state);  // magic, width, height, colorSizeに値を格納する

	static const int COMMENT;
	static const int NEWLINE;
	static const int MAX_IGNORE;
	static const int MAGIC;
	static const int WIDTH;
	static const int HEIGHT;
	static const int COLOR;
	static const int READEND;
	bool readSucceedFlag;     // Pgmファイルの要素と画像データが始まる位置を特定できたらtrue

protected:
	std::string inputFile;					// 読み込むファイルの名前
	std::string magic;					// P(123456)
	int width;						// 画像の幅
	int height;						// 画像の縦の大きさ
	int colorSize;						// 輝度を格納
	int colorStartSeeker;     // 画像データがどこから始まるかを格納




};
