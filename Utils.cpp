#include "pch.h"
#include "Utils.h"

#define PREVIEW_SIZE 2048

/*
 *  This functions tries to read a file and returns a code based on whether the opening was successful
 *
 *  @params     path - an escaped string containing the path to the file, preferably the absolute path should be passed
 *              file - a reference to which the file will be opened to
 *
 *  @returns    -1 on error
 *              0 on success
 *
 */
int Utils::openFile(CString path, std::ifstream& file) {
    file.open(path);

    if (file.fail()) {
        std::cout << "Failed reading file at " << path << std::endl;
        return -1;
    } else {
        std::cout << "Success reading file at " << path << std::endl;
        return 0;
    }
}


/*
 *  This function splits a given string according to a given delimiter.
 *  @params    str - string to be split
 *             delim - delimiter splitting the string
 * 
 *  @returns   a vector of CStrings, 1-element if @param str was empty  
 */
std::vector<CString> Utils::split(CString str, CString delim) {
    int idx { 0 };
    std::vector<CString> strings {};

    if (str.IsEmpty()) {
        strings.push_back(CString(""));
        return strings;
    }

    CString token = str.Tokenize(delim, idx);

    while (!token.IsEmpty()) {
        token.Trim();
        strings.push_back(token);
        token = str.Tokenize(delim, idx);
    }

    return strings;
}


/*
 *  This function takes advantage of filesystem library available in C++17 to recursively list files in a given directory
 *  @param      dir - CString containing the path to the directory
 * 
 *  @returns    a vector containing all file paths in a given directory EXCLUDING directories themselves
 */
std::vector<CString> Utils::listFiles(CString dir) {
    std::vector<CString> files {};
    std::string path = CT2A(dir.GetString());
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::vector<CString> subdirFiles = listFiles(CString(entry.path().c_str()));
            files.insert(files.begin(), subdirFiles.begin(), subdirFiles.end());
        } else {
            files.push_back(CString(entry.path().c_str()));
        }
    }
        
    return files;
}

//Check whether a given string ends with another string. Used for checking file extensions.
bool Utils::endsWith(CString str, CString end) {
    int endLength = end.GetLength();
    return (str.Mid(str.GetLength() - endLength, endLength) == end);
}

/*
 *  This function filters CStrings in a vector on condition that they don't end in an extension given in @param extensions 
 *  @params     files - reference to a vector containing CStrings to be filtered
 *              extensions - accepted extensions
 *               
 *  @returns    nothing, as the passed reference is modified.
 */
void Utils::filterExtensions(std::vector<CString> &files, std::vector<CString> extensions) {
    auto it = files.begin();
    while (it != files.end()) {
        int hasExtension = 0;
        for (auto ext : extensions) {
            if (Utils().endsWith(*it, ext)) {
                hasExtension = 1;
                break;
            }
        }

        //Since we are removing elements, the size constantly changes. Therefore we use the return value of erase to compensate for that.
        if (!hasExtension) {
            it = files.erase(find(files.begin(), files.end(), *it));
        } else {
            ++it;
        }
    }
}
