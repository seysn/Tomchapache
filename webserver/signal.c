/***********************
 * MAUGER & SEYS Nicolas
 * Tomchapache
 * 01 feb. 2016
 * signal.c
***********************/

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "signal.h"

void traitement_signal(int sig) {
    int status;
    switch(sig) {
    case SIGCHLD:
	while (waitpid(-1, &status, WNOHANG) > 0);
    }
}

void initialiser_signaux(void) {
    struct sigaction sa;
    sa.sa_handler = traitement_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
	perror("sigaction(SIGCHLD)");
    }
    
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
	perror("signal");
    }
}
