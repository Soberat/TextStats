#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>


/*
 *	This class contains generic, non-class-specific functions 
 */
class Utils {
	public:
		int openFile(CString, std::ifstream&);
		std::vector<CString> Utils::split(CString, CString);
		CString Utils::trim(CString);
		std::vector<CString> Utils::listFiles(CString);
		bool Utils::endsWith(CString, CString);
		void Utils::filterExtensions(std::vector<CString>&, std::vector<CString>);
};

