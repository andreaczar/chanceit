#include <stdbool.h>
#include "player.h"
// pre and post conditions here
int displayMenu();

// pre and post conditions here
int amtRounds();

// pre and post conditions here
//void startRound(int player_roll, int opponent_roll, int roundNum, int totalRound);
void startRound(Game* game);
// pre and post conditions here
void displayProbability(int roll, int probability);

// pre and post conditions here
void roundOver();

void startGame(Game *game);

void displayPlayer(Player* player);

void gameSummary(Player* p1, Player* p2);

void firstPlayer(Player* currentPlayer, Player* otherPlayer);

//
void loseRound();
void roundScore(Player* player);
void leadingRound(Player* winner, Player* loser);
void pointSet(Player* player);

// pre and post conditions here
void win(Player* player);

// pre and post conditions here
void highScore();

// pre and post conditions here
bool playAgain();

char rollAgain();