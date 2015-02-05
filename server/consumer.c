#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "consumer.h"
#include "colorlog.h"
#include "Queue.h"

#define BUFFER_SIZE 256

extern Queue* waiting;

void* consumer(void* arg) {
	VERBOSE("CONSUMER","start");
	int *client;
	while(true) {
		//~ VERBOSE("CONSUMER","new try");
		client = dequeue(waiting);
		VERBOSE("CONSUMER","new try %p",client);
		if(client != NULL) {
			//~ printf("\tCONSUMER dequeue(%d)\n",*val);
			INFO("CONSUMER","new client");

			char buffer[BUFFER_SIZE];
			int longueur = 0;
			while(longueur <= BUFFER_SIZE) {
				if ((longueur = read(*client, buffer, sizeof(buffer))) <= 0) {
					ALERT("CONSUMER","can't read more");
					break;
				}
				SUCCESS("CONSUMER","received : >%s<(%d)",buffer,longueur);
				if(longueur == 1)
					break;
			}
			SUCCESS("CONSUMER","end reading");
			buffer[0] = 'O';
			buffer[1] = 'K';
			buffer[2] = '\0';
			write(*client,buffer,3);
			close(*client);
		} else {
			//~ printf("\tCONSUMER dequeue(NULL)\n");
			INFO("CONSUMER","no waiting client");
			sleep(1);
		}
	}
	VERBOSE("CONSUMER","end");
	return NULL;
}
