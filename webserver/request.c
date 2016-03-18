/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 01 mar. 2016
 * request.c
 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"

#define BUFF_SIZE 1024

char *fgets_or_exit (char *buffer, int size, FILE *stream) {
    if (fgets(buffer, size, stream) != NULL) {
        return buffer;
    }
    //fclose(stream);
     exit(1);
}

int parse_http_request (const char *request_line, http_request *request) {
    char *parser = strdup(request_line);
    int word = 0;

    parser = strtok (parser, " \r");
    while (parser != NULL) {
        word++;
        switch (word) {

            case 1:
                if (strcmp("GET",parser) != 0) {
                    return 0;
                }
                request->method = HTTP_GET;
                break;
            case 2:
                //if (strcmp("/", parser) != 0 ) {
                if (parser[0] == '/') {
                    return 0;
                }
                strcpy(request->url, parser);
                break;
            case 3:
                if (strcmp("HTTP/1.0", parser) != 0 && strcmp("HTTP/1.1", parser) != 0) {
                    return 0;
                }
                request->minor_version = 1;
                break;
            case 4:
                if(strcmp("\n", parser) !=0) {
                    return 0;
                }
                break;
            default :
                return 1;
                break;
        }
        parser = strtok (NULL, " \r");
    }
    return 1;
}


void skip_header (FILE *client) {
    char buf[BUFF_SIZE];
    // TODO Il faut réutiliser gets_or_exit ?
    while (fgets_or_exit(buf, BUFF_SIZE, client) != NULL && !strcmp(buf, "\r\n") && !strcmp(buf, "\n"));
}
