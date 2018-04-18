#include <iostream>
#include <fstream>
#include "server.h"

void server::create_server() {
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET; //internet ip protocol v4
    my_addr.sin_port = htons(PORT); //PORT
    my_addr.sin_addr.s_addr = INADDR_ANY; //network byte order

    //create socket
    if ((socket_s = socket(my_addr.sin_family, SOCK_STREAM, 0)) == -1) {
        cout << CREATION_ERROR_MESSAGE << endl;
    }

    //bind socket to a PORT
    bind(socket_s, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));

    // listen up to MAX_POSSIBLE_CONNECTIONS connections
    listen(socket_s, MAX_POSSIBLE_CONNECTIONS);
}

void server::receive_data() {
    socklen_t sock_size = sizeof(struct sockaddr_in);

    struct sockaddr_in host_addr;

    //waiting for connection
    connection_c = accept(socket_s, (struct sockaddr *) &host_addr, &sock_size);

    //receive_data contend
    char request[MAX_PACKET_SIZE];
    recv(connection_c, request, MAX_PACKET_SIZE, 0);  //GET / HTTP/1.1

    send_response(request);
}

void server::send_response(string request){
    string filename = get_filename(request);
    string fileending = get_fileending(filename);
    string message = open_file(filename);
    string content_type;

    if(fileending == "html"){
        content_type = "text/html";
    }
    else if(fileending == "json"){
        content_type = "application/json";
    }

    string response = create_header(message, content_type) + message;

    send_data(response);
}

void server::send_data(string message) {
    send(connection_c, message.c_str(), message.length(), 0);
}

void server::detach() {
    close(socket_s);
    close(connection_c);
}

string server::create_header(string message, string content_type) {

    string header_text = "HTTP/1.1 200 OK\nContent-Type: " + content_type +"; charset=UTF-8\n"
                         "Content-Encoding: UTF-8\nContent-Length: " + to_string(message.length()) +
                         "\nServer: C++Server/1.0 (Linux)\n\n";

    return header_text;
}

string server::get_filename(string request){
    string filename;
    char delim = ' ';

    request.erase(0, request.find(delim) + 1);
    filename = request.substr(0, request.find(delim));

    //remove first char
    filename.erase(0,1);

    return filename;
}

string server::get_fileending(string filename){
    char delim = '.';
    filename.erase(0, filename.find(delim)+1);
    return filename;
}

string server::open_file(string filename){

    if(filename == ""){
        filename == "index.html";
    }

    string temporary_data;
    string data;
    ifstream infile;
    infile.open(FILE_PATH + filename);

    getline(infile,temporary_data);
    data = temporary_data;
    while(infile)
    {
        getline(infile,temporary_data);
        data = data + temporary_data;
    }
    infile.close();

    return data;
}