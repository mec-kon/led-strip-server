#include "http.h"

http::http() {
    server_s.create_server();
}

void http::do_GET() {
    while(true){
        string request = server_s.receive_data();
        send_response(request);
    }
}

void http::do_POST(){

}

void http::send_response(string request) {
    string filename = file_f.get_filename(request);
    string fileending = file_f.get_fileending(filename);
    string message = file_f.open_file(filename);
    string content_type;

    if(message != "file not found"){
        if (fileending == "html") {
            content_type = "text/html";
        } else if (fileending == "json") {
            content_type = "application/json";
        }

        string response = create_header(message, content_type) + message;

        server_s.send_data(response);
    } else {

    }

}

string http::create_header(string message, string content_type) {

    string header_text = "HTTP/1.1 200 OK\nContent-Type: "
                         + content_type + "; charset=UTF-8\n"
                                          "Content-Encoding: UTF-8\nContent-Length: " +
                         to_string(message.length()) +
                         "\nServer: C++Server/1.0 (Linux)\n\n";

    return header_text;
}