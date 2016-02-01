/***********************
 * SEYS & MAUGER Nicolas
 * Tomchapache
 * 01 feb. 2016
 * socket.c
***********************/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "socket.h"

int creer_serveur(int port) {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET; /* Socket ipv4 */
    saddr.sin_port = htons(port); /* Port d'écoute */
    saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */

    int socket_serveur;
    int socket_client;
    socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socket_serveur == -1) {
        perror("socket_serveur");
        return -1; 
    }

    if (bind(socket_serveur, (struct sockaddr *)& saddr, sizeof(saddr)) == -1) {
        perror("bind socker_serveur");
        return -2;
    }

    if (listen(socket_serveur, 10) == -1) {
        perror("listen socket_serveur");
        return -3;
    }

   socket_client = accept( socket_serveur , NULL, NULL );
   if (socket_client == -1) {
       perror("accept");
       return -4;
   }
   /* On peut maintenant dialoguer avec le client */
   const char * message_bienvenue = "Bonjour, bienvenue sur mon serveur \n ";
   write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));

   return 0;
}


