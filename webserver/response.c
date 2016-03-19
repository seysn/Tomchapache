/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 11 mar. 2016
 * response.h
 **************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "response.h"

void send_status (FILE *client, int code, const char *reason_phrase){
    fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
}

void send_response (FILE *client, int code, const char *reason_phrase, const char *message_body){
    send_status(client, code, reason_phrase);
    fprintf(client, "Connection: close\r\nContent-length: %zu\r\n\r\n%s", strlen(message_body), message_body);
}
