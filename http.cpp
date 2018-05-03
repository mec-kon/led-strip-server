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
    string fileending = file_f.get_fileending(filename);
    string response;

    if (mode == "POST" && !filename.empty()) {
        string content = request.substr(request.find("\x0D\x0A\x0D\x0A")) + "\n\0";
        string message = file_f.write_file(filename, content);
        string content_type = "";
        response = create_header(message, content_type, "HTTP/1.1 200 OK");

    } else if (mode == "GET") {
        string message = file_f.open_file(filename);
        string content_type;

        if (message != "file not found") {
            if (fileending == "html") {
                content_type = "text/html";
            } else if (fileending == "json") {
                content_type = "application/json";
            }

            response = create_header(message, content_type, "HTTP/1.1 200 OK") + message;

        } else {
            response = create_header(message, content_type, "HTTP/1.1 404 NOT Found") + message;
        }

    } else {
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