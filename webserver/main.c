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
                
                fgets(buf, BUF_SIZE, fsocket);

		/* On teste si la premiere ligne est correcte */
		int words = 0, ok = 1;
		unsigned int i;
		for (i = 0; i < strlen(buf); i++) {
		    if (buf[i] == ' ' || buf[i] == '\n') {
			words++;
		    }
		}

		if (words != 3) {
		    ok = 0;
		}

		char * tmp = NULL;
		tmp = strstr(buf, "HTTP/1");
		if (tmp == NULL) {
		    ok = 0;
		} else {
		    if (tmp[7] != '0' && tmp[7] != '1') {
			ok = 0;
		    }
		}
		while(fgets(buf, BUF_SIZE, fsocket) != NULL && !strcmp(buf, "\r\n") && !strcmp(buf, "\n"));
                
		if (!ok) {
		    /* La première ligne est incorrecte */
		    char * msg = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
		    write(socket_client, msg, strlen(msg));
		} else {
		    /* La première ligne est correcte */
		    char * msg = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 8\r\n\r\n200 OK\r\n";
		    write(socket_client, msg, strlen(msg));
		}
		
                return EXIT_SUCCESS;
            default:
                close(socket_client);
        }
    }

    return EXIT_SUCCESS;
}
