#include <iostream>
#include "File.h"

File::File() {
    HOME = getenv("HOME");
    string working_directory = get_working_path();
    string base_name = working_directory.substr(working_directory.find_last_of('/'), working_directory.size());

#ifdef DEBUG_MODE
    cout << FILE_CPP << "working directory: " << working_directory << endl;
    cout << FILE_CPP << "base name: " << base_name << endl;
#endif

    is_installed = base_name != "/cmake-build-debug" && base_name != "/build";
}

string File::get_working_path() {
    char *temp = getcwd(nullptr, 0);

    if (temp != nullptr)
        return temp;

    int error = errno;

    switch (error) {
        // EINVAL can't happen - size argument > 0

        // PATH_MAX includes the terminating nul,
        // so ERANGE should not be returned

        case EACCES:
            throw std::runtime_error("Access denied");

        case ENOMEM:
            // I'm not sure whether this can happen or not
            throw std::runtime_error("Insufficient storage");

        default: {
            std::ostringstream str;
            str << "Unrecognised error " << error;
            throw std::runtime_error(str.str());
        }
    }
}

/**
 * @brief method to get the file name with file extension
 *
 * This method returns the file name with an extension for a
 * string,in which an HTTP request is stored.
 *
 * @param request (The HTTP request.)
 * @return filename (The filename with extension as string.)
 */
string File::get_filename(string request) {
    string filename;
    char delim = ' ';

    request.erase(0, request.find(delim) + 1);
    filename = request.substr(0, request.find(delim));
    filename = filename.substr(0, filename.find_first_of('?'));

    //remove first char
    filename.erase(0, 1);

    if (filename.empty()) {
        filename = "index.html";
    }

    return filename;
}

/**
 * @brief method to get the file extension without file name.
 *
 * This method returns the file extension without a file name for a
 * string in which the file name with the extension is stored.
 *
 * @param filename (The file name with extension as string.)
 * @return filename (The file extension without file name as string.)
 */
string File::get_file_ending(string filename) {
    char delim = '.';

    filename = filename.substr(0, filename.find_first_of('?'));
    filename.erase(0, filename.find_last_of(delim) + 1);

    return filename;
}

/**
 * @brief this method checks whether a file exists
 *
 * @param filename (File name to be checked.)
 * @return file_f (A boolean variable that specifies whether the file exists or not.)
 */
bool File::file_exists(string filename) {
    ifstream file_f(filename.c_str());
    file_f.close();
    return (bool) file_f;
}

/**
 * @brief method to open file as a string
 *
 * This method opens a file and returns its contents as a string.
 *
 * @param filename (Name of the given file.)
 * @return data (Content of the file as string, if it exists. Otherwise "file not found".)
 */
string File::open_file(string filename) {

    if (filename.empty()) {
        filename = "index.html";
    }

    string file_path;

    if (is_installed) {
        if (filename == "websiteConfig.json") {
            file_path = HOME + INSTALLED_CONFIG_PATH;
        }
        else {
            file_path = HOME + INSTALLED_STATIC_PATH;
        }
    }
    else {
        if (filename == "websiteConfig.json") {
            file_path = CONFIG_PATH;
        }
        else {
            file_path = STATIC_PATH;
        }
    }

    if(file_exists(file_path + filename)){
        string data;
        ifstream infile;
        string path = file_path + filename;
        infile.open(path.c_str());

        data.assign((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

        infile.close();
        return data;
    }
    else {
#ifdef DEBUG_MODE
        cout << FILE_CPP << "file does not exist" << endl;
#endif

        if(filename == "websiteConfig.json") {
            return "{\"port\":9999}";
        }
        else if(filename == "deviceConfig.json") {
            return "{\n"
                   "  \"devices\": [\n"
                   "    {\n"
                   "      \"ipAddress\": \"localhost\",\n"
                   "      \"port\": \"9999\"\n"
                   "    }\n"
                   "  ]\n"
                   "}";
        }
        else {
            return "file not found";
        }
    }
}

/**
 * @brief method to write a string to a file
 *
 * This method saves a string in a file.
 *
 * @param filename
 * @param content
 * @return data
 */
string File::write_file(string filename, string content) {

    string data;
    string file_path;

    if (filename.empty()) {
        filename = "index.html";
    }

    if(is_installed){
        if (filename == "deviceConfig.json") {
            file_path = HOME + INSTALLED_STATIC_PATH;
        }
        else {
            file_path = HOME + INSTALLED_CONFIG_PATH;
        }
    }
    else {
        if (filename == "deviceConfig.json") {
            file_path = STATIC_PATH;
        }
        else {
            file_path = CONFIG_PATH;
        }
    }

    if (file_exists(file_path + filename))
        data = "Added to existing file";
    else
        data = "Created new file";

    ofstream outfile;
    outfile.open(file_path + filename);
    outfile << content;
    outfile.close();

    return data;
}
