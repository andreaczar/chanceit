//Protocol.c
//#include stuff here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"



int getOpponent(char *opp){
	char reply [200];
	int bytes = readLine(reply);
	if (bytes > 0){
		return sscanf(reply, "Opponent: %s\n", opp);
	}
	return 0;
}

int isGameOver (char *response){
	if (strncmp(response, "You win!", 8) == 0 || strncmp(response, "You Lose", 8) == 0){
		return 1;
	} 
	return 0;
}