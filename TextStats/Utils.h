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
		static int openFile(CString, std::ifstream&);
		static std::vector<CString> Utils::split(CString, CString);
		static CString Utils::trim(CString);
		static std::vector<CString> Utils::listFiles(CString);
		static bool Utils::endsWith(CString, CString);
		static void Utils::filterExtensions(std::vector<CString>&, std::vector<CString>);
};

