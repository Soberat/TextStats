#pragma once
#include <fstream>
#include <string>
#include <iostream>

/*
 *	This class is a container for information about a single program run, ie. one folder that the user has chosen to be analyzed. 
 */
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

