//Protocol.c
//#include stuff here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

int connectPlayer(char* name){
	printf("Connecting player...\n");

	char* hello;
	hello = malloc(sizeof(char) * strlen(name));
	sprintf(hello, "HELLO:%s\n", name);

	printf("Sending: %s\n", hello);

	clientSend(hello);
	free(hello);
	printf("Sent\n");
}


int getOpponent(char **opponent){
    int bytes;

	char* reply;
	reply = malloc(sizeof(char)*2048);

    *opponent = malloc(sizeof(char)*bytes);

	while(1){

        bytes = clientRecv(reply);

		if(strncmp("Opponent:", reply, 9) == 0){
			sscanf(reply, "Opponent: %s", *opponent);
            free(reply);
			return 1;
		}
	}

    return 0;
}

int getInitialRolls(int *p1, int *p2){

    int bytes;
    char* reply;
    reply = malloc(2048);

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "Your roll was ", 13) == 0){
            sscanf(reply, "Your roll was: %d. Opponent roll was: %d. %*s.", p1, p2);
            return 0;
        }
    }


}

int getTurnStart(int *p1Score, int *p2Score){

    int bytes;
    char* reply;
    reply = malloc(2048);

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "Turn Starting Score: ", 20) == 0){
            sscanf(reply, "Turn Starting Score: %d-%d.", p1Score, p2Score);
            return 0;
        }
    }


}

int isGameOver (char *response){
	if (strncmp(response, "You win!", 8) == 0 || strncmp(response, "You Lose", 8) == 0){
		return 1;
	} 
	return 0;
}