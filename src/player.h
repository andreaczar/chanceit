#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"


/*
 * Struct to hold a player of any type.
 * get<PlayerType>Player() must set the function pointer for playTurn appropriately
 * for the type of player being created.
 */

struct gamePlayer;
typedef struct gamePlayer Player;

struct gamePlayer {
    bool (* playTurn)(Game* game, Player* yourPlayer, Player* opponent); // function pointer
    int totalScore;
    int roundScore;
    int point;
    int lastRoll;
    int rollCount;
    char* name;
};


/**
 * Precondition: A game has been established
 * Postcondition: Sets up and makes a human player
 * Return: A human player
 */
Player* getHumanPlayer(char* name);


/**
 * Precondition: A game has been established
 * Postcondition: Sets up and makes a network player
 * Return: A network player
 */
Player* getNetworkPlayer(char* name);


/**
 * Precondition: A game has been established
 * Postcondition: Sets up and makes a AI player
 * Return: An AI player
 */
Player* getAIPlayer(char* name);
