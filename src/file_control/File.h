#ifndef HTTP_SERVER_FILE_H
#define HTTP_SERVER_FILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "../defines.h"

#define FILE_CPP "file.cpp : "

using namespace std;

/**
 * @class file
 *
 * This class takes care of reading from and writing to files.
 */
class File {
public:
    File();
    string open_file(string filename);
    string write_file(string filename, string content);
    string get_filename(string request);
    string get_file_ending(string filename);

private:
    string HOME;
    bool is_installed;
    string get_working_path();
    bool file_exists(string filename);
};


#endif //HTTP_SERVER_FILE_H
