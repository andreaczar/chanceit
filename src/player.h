#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"


/*
 * Struct to hold a player of any type.
 * get<PlayerType>Player() must set the function pointer for playTurn appropriately
 * for the type of player being created.
 */
typedef struct {
    bool (*playTurn)(Game *game, Player* yourPlayer, Player* opponent); // function pointer
    int totalScore;
    int roundScore;
    int point;
    int lastRoll;
    char* name;
} Player;


// Sets up and returns a Human player
Player* getHumanPlayer(char* name);


// Sets up and returns a Network player
Player* getNetworkPlayer(char* name);


// Sets up and returns an AI player
Player* getAIPlayer(char* name);
