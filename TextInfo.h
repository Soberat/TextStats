#pragma once
#include <fstream>
#include <string>
#include <iostream>

class TextInfo {
	private:
		int lines;
		int words;
		int chars;

	public:
		int getLines();
		int getWords();
		int getChars();
		void analyze(std::ifstream&);
		TextInfo();
};

