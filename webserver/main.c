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
#include <ctype.h>

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
    const char * message_bienvenue = "Bonjour, bienvenue sur le serveur\nle plus parfait du monde.\nSur votre droite, vous pourrez voir\nrien qui n\'est plus parfait que\nserveur qui defie la perfection.\nSur votre gauche, pareil.\nNenufar.\nOgnon.\n";
    const char * message_404 = "404 Not Found";
    const char * message_400 = "400 Bad Request";

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
                fgets(buf, BUF_SIZE, fsocket);

		/* On teste si la premiere ligne est correcte */
		int words = 0, ok = 1, notfound = 0;
		char * currentWord = strtok(buf, " ");

		/* On teste chaque mot de la première ligne*/
		while (currentWord != NULL) {
		    words++;
		    switch(words) {
		    case 1:
			if (strcmp(currentWord, "GET") != 0)
			    ok = 0;
			break;
		    case 2:
			if (strcmp(currentWord, "/") != 0) {
			    notfound = 1;
			}
			break;
		    case 3:
			if (strstr(currentWord, "HTTP/1") == NULL || (currentWord[7] != '0' && currentWord[7] != '1')) {
			    ok = 0;
			}
			break;
		    default:
			break;
		    }
		    
		    currentWord = strtok(NULL, " ");
		}

		if (words != 3)
		    ok = 0;

		/* On ignore les autres lignes */
		while(fgets(buf, BUF_SIZE, fsocket) != NULL && !strcmp(buf, "\r\n") && !strcmp(buf, "\n"));
		
		if (ok == 0) {
		    /* La première ligne est incorrecte */
		    char msg[BUF_SIZE];
		    int len = strlen(message_404);
		    sprintf(msg, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s\r\n", len, message_400);
		    write(socket_client, msg, strlen(msg));
		} else {
		    /* La première ligne est correcte */
		    if (notfound == 1) {
			char msg[BUF_SIZE];
			int len = strlen(message_404);
			sprintf(msg, "HTTP/1.1 404 Not Found\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s\r\n", len, message_404);
			write(socket_client, msg, strlen(msg));
		    } else {
			char msg[BUF_SIZE];
			int len = strlen(message_bienvenue);
			sprintf(msg, "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s\r\n", len, message_bienvenue);
			write(socket_client, msg, strlen(msg));
		    }
		}
		
                return EXIT_SUCCESS;
            default:
                close(socket_client);
        }
    }

    return EXIT_SUCCESS;
}
