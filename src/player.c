#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include "roll.h"


/**
 * Initialize common player attributes
 */
Player* initPlayer(char* name){
    Player* player;
    player = malloc(sizeof(Player));
    player->totalScore = 0;
    player->point = 0;
    player->lastRoll = 0;
    player->rollCount = 0;
    player->name = name;
    player->firstTurn = false;
    return player;
}


Player* getHumanPlayer(char* name){
    Player* player = initPlayer(name);
    player->playTurn = playHumanTurn;
    return player;
}

Player* getNetworkPlayer(char* name){
    Player* player = initPlayer(name);
    return player;
}

Player* getAIPlayer(char* name){
    Player* player = initPlayer(name);
    player->playTurn = playAITurn;
    return player;
}


Player* getRemotePlayer(char* name){
    Player* player = initPlayer(name);
    player->playTurn = NULL;
    return player;
}