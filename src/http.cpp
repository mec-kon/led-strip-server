#include "http.h"

http::http() {
    server_s.create_server();
}

void http::RUN() {
    while (true) {
        string request = server_s.receive_data();
        string mode = get_request_mode(request);

        handle_request(request, mode);

        server_s.close_connection();
    }
}

void http::handle_request(string request, string mode) {
    string filename = file_f.get_filename(request);
    string file_ending = file_f.get_file_ending(filename);
    string response;

    if (mode == "POST" && !filename.empty()) {
        string content = request.substr(request.find("\x0D\x0A\x0D\x0A")) + "\n\0";
        string message = file_f.write_file(filename, content);
        string content_type = "text/plain";
        response = create_header(message, content_type, "HTTP/1.1 200 OK");

    }
    else if (mode == "GET") {
        string message = file_f.open_file(filename);
        string content_type;

        if (message != "file not found") {

            content_type = get_content_type(file_ending);

            response = create_header(message, content_type, "HTTP/1.1 200 OK") + message;

        }
        else {
            response = create_header(message, content_type, "HTTP/1.1 404 NOT Found") + message;
        }

    }
    else {
        response = create_header("", "text/html", "HTTP/1.1 404 NOT Found");
    }

    server_s.send_data(response);
}

string http::create_header(string message, string content_type, string status_code) {

    string header_text = status_code + "\nContent-Type: "
                         + content_type + "; charset=UTF-8\n"
                                          "Content-Encoding: UTF-8\nContent-Length: " +
                         to_string(message.length()) +
                         "\nServer: C++Server/1.0 (Linux)\n\n";

    return header_text;
}

string http::get_request_mode(string request) {
    string mode = request.substr(0, request.find(" "));
    return mode;
}

string http::get_content_type(string file_ending) {

    string mime_type = "text/plain";

    switch (file_ending[0]) {
        case 'b':
            if (file_ending == "bmp")
                mime_type = "image/bmp";
            if (file_ending == "bin")
                mime_type = "application/octet-stream";

            break;
        case 'c':
            if (file_ending == "csh")
                mime_type = "application/csh";
            if (file_ending == "css")
                mime_type = "text/css";

            break;
        case 'd':
            if (file_ending == "doc")
                mime_type = "application/msword";
            if (file_ending == "dtd")
                mime_type = "application/xml-dtd";
            break;
        case 'e':
            if (file_ending == "exe")
                mime_type = "application/octet-stream";
            break;
        case 'h':
            if (file_ending == "html" || file_ending == "htm")
                mime_type = "text/html";
            break;
        case 'i':
            if (file_ending == "ico")
                mime_type = "image/x-icon";
            break;
        case 'g':
            if (file_ending == "gif")
                mime_type = "image/gif";
            break;
        case 'j':
            if (file_ending == "jpeg" || file_ending == "jpg")
                mime_type = "image/jpeg";
            break;
        case 'l':
            if (file_ending == "latex")
                mime_type = "application/x-latex";
            break;
        case 'p':
            if (file_ending == "png")
                mime_type = "image/png";
            if (file_ending == "pgm")
                mime_type = "image/x-portable-graymap";
            break;
        case 'r':
            if (file_ending == "rtf")
                mime_type = "text/rtf";
            break;
        case 's':
            if (file_ending == "svg")
                mime_type = "image/svg+xml";
            if (file_ending == "sh")
                mime_type = "application/x-sh";
            break;
        case 't':
            if (file_ending == "tar")
                mime_type = "application/x-tar";
            if (file_ending == "tex")
                mime_type = "application/x-tex";
            if (file_ending == "tif" || file_ending == "tiff")
                mime_type = "image/tiff";
            if (file_ending == "txt")
                mime_type = "text/plain";
            break;
        case 'x':
            if (file_ending == "xml")
                mime_type = "application/xml";
            break;
        default:
            break;
    }

    return mime_type;
}
