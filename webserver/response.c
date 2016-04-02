/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 11 mar. 2016
 * response.h
 **************************/

#include <stdio.h>
#include <sys/stat.h>
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

int get_file_size (int fd) {
    struct stat st;
    if (fstat(fd, &st) == 0)
        return st.st_size;
    return -1;
}

int copy(int in, int out) {
    return dup2(in, out);
}
