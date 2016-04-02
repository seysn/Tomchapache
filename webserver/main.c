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
#include "request.h"
#include "response.h"

#define BUF_SIZE 1024

int main()
{
    char buf[BUF_SIZE];
    int socket_serveur, socket_client;
    if((socket_serveur = creer_serveur(8080)) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    initialiser_signaux();
    const char * message_bienvenue = "Bonjour, bienvenue sur le serveur\nle plus parfait du monde.\nSur votre droite, vous pourrez voir\nrien qui n\'est plus parfait que\nle serveur qui defie la perfection.\nSur votre gauche, pareil.\nNenufar.\nOgnon.\r\n";

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

	    fgets_or_exit(buf, BUF_SIZE, fsocket);
	    http_request request;

	    int bad_request = parse_http_request(buf, &request);
	    skip_header(fsocket);

	    if (bad_request == 0) {
		send_response(fsocket, 400, "Bad Request", "Bad Request\r\n");
	    }
	    else if (request.method == HTTP_UNSUPPORTED) {
		send_response(fsocket, 405, "Method not allowed", "Method not allowed\r\n");
	    }
	    else if (strcmp(request.url, "/") == 0) {
		send_response(fsocket, 200, "OK", message_bienvenue);
	    }
	    else {
		send_response(fsocket, 404, "Not Found", "Not Found\r\n");
	    }

        // Servir du vrai contenu
        int pid;
        if ((pid = check_and_open(request.url, "/")) < 0){
            send_response(fsocket, 404, "Not Found", "File Not Found\r\n");
        } else {
            // transmission du fichier au client
            send_response(fsocket, 200, "OK", message_bienvenue);
        }

	    fclose(fsocket);
	    return EXIT_SUCCESS;
	default:
	    fclose(fsocket);
	    close(socket_client);
        }
    }

    return EXIT_SUCCESS;
}
