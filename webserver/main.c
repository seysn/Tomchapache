/**************************
 * MAUGER & SEYS - Nicolas
 * Tomchapache
 * 01 feb. 2016
 * main.c
**************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"

int main() 
{
    if(creer_serveur(8080) < 0) 
    {
        printf("REKT");
    }
  	return 0;
}
