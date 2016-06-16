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
} PlayerTurnState;

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


int waitForPrompt(){
    int bytes;
    char* reply;
    reply = malloc(2048);

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "chance-it? [Y/n]", 16) == 0){
            return 0;
        }
    }
    return 0;
}

int checkPlayerTurn(int *rollTotal, int *turnScore, int *currentTurn){
	

//    PlayerTurnState currentState = initialState == 0 ? waitTurnStartingScore : waitTurn;
    PlayerTurnState currentState = waitTurn;

	int bytes;

	char* reply;
	reply = malloc(sizeof(char)*2048);
 
	while(1){


//        printf("Recving for player turn:\n");
        bytes = clientRecv(reply);



        if(strncmp("Running Turn Score: 0", reply, 21) == 0){
            printf("Got player score zero, round over\n");
            *turnScore = 0;
            free(reply);
            return -1;

        } else {

//            printf("State: %d\n", currentState);

            switch(currentState){

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
                        sscanf(reply, "Running Turn Score: %d", turnScore);
                        currentState = waitRollDone;
                    }
                    break;

                case waitRollDone:
                    if(strncmp("--", reply, 2) == 0){
                        // if turn score is zero, player lost, end turn
                        free(reply);

                        if(*turnScore == 0){
                            return -1;
                        }

                        return 0;
                    }
            }
        }

	}

    return 0;
}
int checkOpponentTurn(int *p1, int *p2){
	int bytes;

	char* reply;
	reply = malloc(sizeof(char)*2048);

	while(1){
        bytes = clientRecv(reply);

		if(strncmp("Turn Starting Score: ", reply, 21) == 0){
			sscanf(reply, "Turn Starting Score: %d-%d", p1, p2);
            free(reply);
			return 0;
		}
	}

    return 0;
	
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
        printf("Getting turn start..\n");
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

int getTurnNumber(int *turnNum){

    int bytes;
    char* reply;	
    reply = malloc(2048);
    while(1){
        bytes = clientRecv(reply);
		
        if(strncmp(reply, "Turn#: ", 7) == 0){
            sscanf(reply, "Turn#: %d", turnNum);
            return 0;
        }
    }


}

int getRollNumber(int *rollNumber){

    int bytes;
    char* reply;
    reply = malloc(2048);

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "Roll#: ", 20) == 0){
            sscanf(reply, "Roll#: %d.", rollNumber);
            return 0;
        }
    }


}

int getYourRoll(int *dieOne, int *dieTwo){

    int bytes;
    char* reply;
    reply = malloc(2048);

    while(1){
        bytes = clientRecv(reply);

        if(strncmp(reply, "You Rolled: ", 12) == 0){
            sscanf(reply, "You Rolled: [%d,%d]", dieOne, dieTwo);
            return 0;
        }
    }


}