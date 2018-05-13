#ifndef HTTP_SERVER_DEFINES_H
#define HTTP_SERVER_DEFINES_H

/**
 * @file defines.h
 *
 * This file contains all parameters that can be configured
 */
#define PORT 9999
#define STATIC_PATH "../static/"
#define FILES_PATH "../files/"
#define MAX_PACKET_SIZE 4096
#define MAX_POSSIBLE_CONNECTIONS 5

#define CREATION_ERROR_MESSAGE "error! could not create socket"

#endif //HTTP_SERVER_DEFINES_H
