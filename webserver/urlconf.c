/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 21 mar. 2016
 * urlconf.c
 **************************/

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "urlconf.h"

char * rewrite_url(char * url) {
    if (strchr(url, '?') == NULL) return url;

    char * parser = strtok(url, "?");
    strcpy(url, parser);
    return url;
}

int check_and_open(const char * url, const char * document_root) {
    char tmp[strlen(document_root) + strlen(url) + 1];
    sprintf(tmp, "%s%s", document_root, url);

    struct stat fstat;
    stat(tmp, &fstat);

    if (!S_ISREG(fstat.st_mode))
	return -1;
    return open(tmp, O_RDONLY);
}
