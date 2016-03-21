/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 21 mar. 2016
 * urlconf.c
 **************************/

#include <string.h>
#include <stdio.h>
#include "urlconf.h"

char * rewrite_url(char * url) {
    if (strchr(url, '?') == NULL) return url;

    char * parser = strtok(url, "?");
    strcpy(url, parser);
    return url;
}
