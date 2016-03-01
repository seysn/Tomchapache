/**************************
* MAUGER & SEYS - Nicolas
* Tomchapache
* 01 mar. 201
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

//request_line =GET http://www.wesh.com/ HTTP/1.0\n
int parse_http_request (const char *request_line, http_request *request) {
    char *parser = (char *) request_line; //oblige de faire sa c'est une const
    parser = strtok(parser, " ");
    //TODO faudrait tester à chaque fois si on est pa arrive à la fin
    if (strcmp("GET",parser) != 0) { // Si le premier mot n'est pas GET
        return 0;
    }
    request->method = HTTP_GET;
    parser = strtok(NULL, " ");
    request->url = parser; //TODO je test pas l'URL #thug
    parser = strtok(NULL, " ");
    if (strcmp("HTTP/1.0", parser) != 0 || strcmp("HTTP/1.1", parser) != 0) {
        return 0;
    }
    request->minor_version = 1;
    parser = strtok(NULL, "\n");
    if (parser != NULL) { //si il reste encore des choses après ça ne va pas
        return 0;
    }
    return 1;
}

/*
void skip_header (FILE *client);

void send_status (FILE *client, int code, const char *reason_phrase);
void send_reponse (FILE *client, int code, const char *reason_phrase,
const char *message_body);
*/
