#include <stdbool.h>
#include "player.h"
// pre and post conditions here
int displayMenu();

// pre and post conditions here
int amtRounds();

// pre and post conditions here
void startRound(int player_roll, int opponent_roll, int roundNum, int totalRound);

// pre and post conditions here
void displayProbability(int roll, int probability);

// pre and post conditions here
void turnOver();

//
void roundOver();
void roundScore(Player* player);
void leadingRound(Player* winner, Player* loser);
void pointSet(Player* player);

// pre and post conditions here
void win(int score);

// pre and post conditions here
void highScore();

// pre and post conditions here
bool playAgain();

char rollAgain();