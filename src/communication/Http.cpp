#include "Http.h"

/**
 * @brief constructor
 *
 * This is the constructor of the http class.
 * Here, the object server_s is initially configured using the method create_server.
 *
 * @return void
 */
Http::Http() {
    string config = file.open_file("websiteConfig.json");
    Json json;

#ifdef DEBUG_MODE
        cout << HTTP << "constructor method called" << endl;
#endif

    try {
        json = Json::parse(config);
        port = json["port"];

    }
    catch (exception &e) {
        cerr << HTTP << "could not read websiteConfig.json" << endl;
        cerr << HTTP << "error: " << e.what() << endl;
#ifdef DEBUG_MODE
        cout << HTTP << "Server created with default port 9999" << endl;
#endif
        port = 9999;
    }
    server.create_server(port);

}

/**
 * @brief main method for handling requests
 *
 * In this method, requests are processed in an endless loop.
 *
 * @return void
 *
 */
void Http::RUN(sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write,
               string *message) {
    while (true) {
        string request = server.receive_data();
        string mode = get_request_mode(request);
        string data = handle_request(request, mode);
        bool new_message;

        if (!data.empty()) {
            new_message = true;

            sem_wait(network_connection_write);
            sem_wait(network_connection_access);


            *message = data;
#ifdef DEBUG_MODE
            cout << HTTP << "data received in run()" << endl;
            cout << HTTP << data << endl;
#endif
        }
        else {
            new_message = false;
        }

        server.close_connection();

        if (new_message) {
            sem_post(network_connection_access);
            sem_post(network_connection_read);
        }

    }
}

/**
 * @brief method for processing requests from the RUN function
 *
 * This method processes the requests received in the RUN method.
 * It is checked whether it is an HTTP-GET or HTTP-POST.
 * With a POST the content is written to a file, with a GET the requested file is read.
 * A suitable header is then created for an answer.
 *
 * @param request (In this variable, the HTTP request is passed to the method.)
 * @param mode (This variable determines whether it is an HTTP GET or an HTTP POST.)
 *
 * @return void
 */
string Http::handle_request(string request, string mode) {
    string filename = file.get_filename(request);
    string file_ending = file.get_file_ending(filename);
    string response;
    string content = "";

    if (mode == "POST" && !filename.empty()) {
        int content_len = get_content_length(request);
        content = get_content(request, content_len);

        string message;
        if (filename == "colors.json") {
            message = "color received";
        }
        else {
            message = file.write_file(filename, content);
            content = "";
        }

        string content_type = "text/plain";
        response = create_header(static_cast<int>(message.length()), content_type, "HTTP/1.1 200 OK") + message;

    }
    else if (mode == "GET") {
        string message = file.open_file(filename);
        string content_type;

        if (message != "file not found") {

            content_type = get_content_type(file_ending);

            response = create_header(static_cast<int>(message.length()), content_type, "HTTP/1.1 200 OK") + message;

        }
        else {
            response = create_header(static_cast<int>(message.length()), content_type, "HTTP/1.1 404 NOT Found") + message;
        }
    }
    else if (mode == "OPTIONS") {
        response = create_cors_header("*");
    }
    else {
        response = create_header(0, "text/html", "HTTP/1.1 404 NOT Found");
    }

    server.send_data(response);

    return content;
}

/**
 * @brief method to create a HTTP-Header
 *
 * @param message_length (The length of the content is stored in this variable.)
 * @param content_type
 * @param status_code
 * @return header_text (The text of the header as string.)
 *
 */
string Http::create_header(int message_length, string content_type, string status_code) {

    string header_text = status_code +
                         "\nContent-Type: " + content_type + "; charset=UTF-8" +
                         "\nContent-Encoding: UTF-8" +
                         "\nContent-Length: " + to_string(message_length) +
                         "\nServer: mec-kon's C++Server/1.0 (Linux)" +
                         "\r\n\r\n";

    return header_text;
}

string Http::create_cors_header(string cors_ip_address) {
    string header_text = "HTTP/1.1 200 OK"
                         "\nContent-Type: text/plain; charset=UTF-8"
                         "\nContent-Encoding: UTF-8"
                         "\nContent-Length: 0"
                         "\nServer: mec-kon's C++Server/1.0 (Linux)"
                         "\nAccess-Control-Allow-Origin: " + cors_ip_address +
                         "\nAccess-Control-Allow-Methods: POST" +
                         "\nAccess-Control-Allow-Headers: Content-Type" +
                         "\r\n\r\n";
    return header_text;
}

string Http::get_content(string request, int content_length) {

    string content = request.substr(request.find("\r\n\r\n") + 4);
    content = content.substr(0, static_cast<unsigned long>(content_length));

    return content;
}

int Http::get_content_length(string request) {
    request.erase(0, request.find("Content-Length:") + 16);
    request = request.substr(0, request.find_first_of(' '));

    int len = stoi(request);

    return len;
}

/**
 * @brief method to separate the ending of a given string
 *
 * This method separates the ending after a dot from a given string.
 *
 * @param request
 * @return mode
 */
string Http::get_request_mode(string request) {
    string mode = request.substr(0, request.find(' '));
    return mode;
}

/**
 * @brief method for creating a matching content type for asked file
 *
 * This method returns a matching string for the HTTP header of the response for a given file extension.
 *
 * @param file_ending
 * @return content_type
 */
string Http::get_content_type(string file_ending) {

    string content_type = "text/plain";

    switch (file_ending[0]) {
        case 'b':
            if (file_ending == "bmp")
                content_type = "image/bmp";
            if (file_ending == "bin")
                content_type = "application/octet-stream";

            break;
        case 'c':
            if (file_ending == "csh")
                content_type = "application/csh";
            if (file_ending == "css")
                content_type = "text/css";

            break;
        case 'd':
            if (file_ending == "doc")
                content_type = "application/msword";
            if (file_ending == "dtd")
                content_type = "application/xml-dtd";
            break;
        case 'e':
            if (file_ending == "exe")
                content_type = "application/octet-stream";
            break;
        case 'h':
            if (file_ending == "html" || file_ending == "htm")
                content_type = "text/html";
            break;
        case 'i':
            if (file_ending == "ico")
                content_type = "image/x-icon";
            break;
        case 'g':
            if (file_ending == "gif")
                content_type = "image/gif";
            break;
        case 'j':
            if (file_ending == "jpeg" || file_ending == "jpg")
                content_type = "image/jpeg";
            if (file_ending == "js")
                content_type = "text/javascript";
            break;
        case 'l':
            if (file_ending == "latex")
                content_type = "application/x-latex";
            break;
        case 'p':
            if (file_ending == "png")
                content_type = "image/png";
            if (file_ending == "pgm")
                content_type = "image/x-portable-graymap";
            break;
        case 'r':
            if (file_ending == "rtf")
                content_type = "text/rtf";
            break;
        case 's':
            if (file_ending == "svg")
                content_type = "image/svg+xml";
            if (file_ending == "sh")
                content_type = "application/x-sh";
            break;
        case 't':
            if (file_ending == "tar")
                content_type = "application/x-tar";
            if (file_ending == "tex")
                content_type = "application/x-tex";
            if (file_ending == "tif" || file_ending == "tiff")
                content_type = "image/tiff";
            if (file_ending == "txt")
                content_type = "text/plain";
            break;
        case 'x':
            if (file_ending == "xml")
                content_type = "application/xml";
            break;
        default:
            break;
    }

    return content_type;
}
