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

char *fgets_or_exit (char *buffer, int size, FILE *stream) {
    char* temp;
    if ((temp = fgets(buffer, size, stream)) != NULL) {
        return temp;
    }
    fclose(stream);
    exit(0);
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
                if (strncmp("/", parser, 1) != 0 ) {
                    return 0;
                }
                request->url = parser;
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

/*
   void skip_header (FILE *client);

   void send_status (FILE *client, int code, const char *reason_phrase);
   void send_reponse (FILE *client, int code, const char *reason_phrase,
   const char *message_body);
   */
