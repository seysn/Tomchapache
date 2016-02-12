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
#include "signal.h"

#define BUF_SIZE 1024

int main() 
{   
    char buf[BUF_SIZE];
    int socket_serveur, socket_client;
    if((socket_serveur = creer_serveur(8080)) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    initialiser_signaux();
    const char * message_bienvenue = "Bonjour, bienvenue sur le serveur\nle plus parfait du monde.\nSur votre droite, vous pourrez voir\nrien qui n\'est plus parfait que\nserveur qui defie la perfection.\nSur votre gauche, pareil.\nNenufar.\nOgnon.";

    while (1) {
        socket_client = accept(socket_serveur, NULL, NULL);
        if (socket_client == -1) {
            perror("accept");
            return EXIT_FAILURE;
        }
        FILE *fsocket = fdopen(socket_client, "w+");
        switch (fork()) {
            case -1:
                perror("fork");
                return EXIT_FAILURE;
            case 0:
                /* On peut maintenant dialoguer avec le client */
                sleep(1);
                write(socket_client, message_bienvenue, strlen(message_bienvenue) + 1);
                
                while(fgets(buf, BUF_SIZE, fsocket) != NULL){
                    fprintf(fsocket, "<Tomchapache> %s",buf);
                }
                return EXIT_SUCCESS;
            default:
                close(socket_client);
        }
    }

    return EXIT_SUCCESS;
}
