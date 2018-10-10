#ifndef HTTP_SERVER_FILE_H
#define HTTP_SERVER_FILE_H

#include <string>
#include <fstream>
#include "../defines.h"

#define FILE "file.cpp : "

using namespace std;

/**
 * @class file
 *
 * This class takes care of reading from and writing to files.
 */
class file {
public:
    string open_file(string filename);
    string get_filename(string request);
    string get_file_ending(string filename);

private:
    bool file_exists(string filename);
};


#endif //HTTP_SERVER_FILE_H
