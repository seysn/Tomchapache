/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 01 feb. 2016
 * main.c
**************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"

int main() 
{
    int socket_serveur, socket_client;
    if((socket_serveur = creer_serveur(8080)) == EXIT_FAILURE) {
	return EXIT_FAILURE;
    }

    socket_client = accept(socket_serveur, NULL, NULL);
    if (socket_client == -1) {
	perror("accept");
	return EXIT_FAILURE;
    }

    /* On peut maintenant dialoguer avec le client */
    const char * message_bienvenue = "Bonjour, bienvenue sur le serveur\nle plus parfait du monde.\nSur votre droite, vous pourrez voir\nrien qui n\'est plus parfait que\nserveur qui defie la perfection.\nSur votre gauche, pareil.\nNenufar.\nOgnon.";

    sleep(1);
    write(socket_client, message_bienvenue, strlen(message_bienvenue));
    
    while (1) {
	// TODO
    }

    return EXIT_SUCCESS;
}
