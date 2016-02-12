/***********************
 * SEYS & MAUGER Nicolas
 * Tomchapache
 * 01 feb. 2016
 * socket.c
***********************/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#include "socket.h"

int creer_serveur(int port) {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET; /* Socket ipv4 */
    saddr.sin_port = htons(port); /* Port d'écoute */
    saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */

    int socket_serveur;
    socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socket_serveur == -1) {
        perror("socket_serveur");
        return EXIT_FAILURE; 
    }

    int optval = 1;
    if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
	perror("Can not set SO_REUSEADDR option");
    
    if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
        perror("bind socker_serveur");
        return EXIT_FAILURE;
    }

    if (listen(socket_serveur, 10) == -1) {
        perror("listen socket_serveur");
        return EXIT_FAILURE;
    }

    return socket_serveur;
}
