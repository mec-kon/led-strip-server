#ifndef HTTP_SERVER_FILE_H
#define HTTP_SERVER_FILE_H

#include <string>
#include <fstream>
#include "defines.h"

using namespace std;
class file {

public:
    string open_file(string filename);
    string write_file(string filename, string content);
    string get_filename(string request);
    string get_fileending(string filename);

private:
    bool file_exists(string filename);
};


#endif //HTTP_SERVER_FILE_H
