#include "pch.h"
#include "TextInfo.h"

TextInfo::TextInfo() {
	lines = 0;
	words = 0;
	chars = 0;
}

int TextInfo::getLines() {
	return this->lines;
}

int TextInfo::getWords() {
	return this->words;
}

int TextInfo::getChars() {
	return this->chars;
}

void TextInfo::analyze(std::ifstream& in) {
	std::string line;
	while (getline(in, line)) {
		this->lines++;
		for (char c : line) {
			chars++;
			if (c == ' ') words++;
		}
	}
}
