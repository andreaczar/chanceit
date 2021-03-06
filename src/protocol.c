//Protocol.c
//#include stuff here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"


typedef enum {
    waitTurnStartingScore,
    waitTurn,
    waitRoll,
    waitYouRolled,
    waitRunningTurnScore,
    waitRollDone,
    waitChanceIt,
} PlayerTurnState;

int connectPlayer(char* name){
	printf("Connecting player...\n");

	char* hello;
	hello = malloc(sizeof(char) * strlen(name));
	sprintf(hello, "HELLO:%s\n", name);

	clientSend(hello);
	free(hello);
}


int readTurn(int *rollTotal,  int *currentTurn, int *roundScore, int *p1Score, int *p2Score){

    PlayerTurnState currentState = waitTurnStartingScore;

    int bytes;

    char reply[2048];

    while(1){

        bytes = clientRecv(reply);

        if(strncmp(reply, "You Win!", 7) == 0 || strncmp(reply, "You Lose", 7) == 0){
            return 2;
        }

        switch(currentState){

            case waitTurnStartingScore:

                if(strncmp("Turn Starting Score: ", reply, 21) == 0){
                    sscanf(reply, "Turn Starting Score: %d-%d.", p1Score, p2Score);
                    currentState = waitTurn;
                }
                break;

            case waitTurn:

                if(strncmp("Turn#: ", reply, 6) == 0){
                    sscanf(reply, "Turn#: %d", currentTurn);
                    currentState = waitRoll;
                }
                break;

            case waitRoll:
                if(strncmp("Roll#: ", reply, 7) == 0){
                    sscanf(reply, "Roll#: %d", rollTotal);
                    currentState = waitYouRolled;
                }
                break;

            case waitYouRolled:
                if(strncmp("You Rolled: ", reply, 12) == 0){
                    int rollA = 0;
                    int rollB = 0;
                    sscanf(reply, "You Rolled: [%d,%d]", &rollA, &rollB);
                    *rollTotal = rollA + rollB;

                    currentState = waitRunningTurnScore;
                }
                break;

            case waitRunningTurnScore:
                if(strncmp("Running Turn Score: ", reply, 20) == 0){
                    sscanf(reply, "Running Turn Score: %d", roundScore);
                    currentState = waitRollDone;
                }
                break;

            case waitRollDone:
                if(strncmp("--", reply, 2) == 0){
                    if(*roundScore == 0) return -1;
                    currentState = waitChanceIt;
                }

            case waitChanceIt:
                if(strncmp(reply, "chance-it? [Y/n]", 16) == 0){
                    return 0;
                }
        }
    }
}


int getOpponent(char **opponent){
    int bytes;

	char reply[2048];

    *opponent = malloc(sizeof(char)*bytes);

	while(1){

        bytes = clientRecv(reply);

		if(strncmp("Opponent:", reply, 9) == 0){
			sscanf(reply, "Opponent: %s", *opponent);
			return 1;
		}
	}
    return 0;
}

int getInitialRolls(int *p1, int *p2){

    int bytes;
    char reply[2048];

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "Your roll was ", 13) == 0){
            sscanf(reply, "Your roll was: %d. Opponent roll was: %d. %*s.", p1, p2);
            return 0;
        }
    }
}
int getFinalScore(int *p1, int *p2){

    int bytes;
    char reply[2048];

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "Final Score: ", 13) == 0){
            sscanf(reply, "Final Score: %*s %d, %*s %d", p1, p2);

            return 0;
        }
    }
}

