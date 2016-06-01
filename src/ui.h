#include <stdbool.h>
#include "player.h"

/**
 * Precondition: N/A
 * Postcondition: N/A
 * Return: integer to select play mode
 */
int displayMenu();

/**
 * Precondition: N/A
 * Postcondition: N/A
 * Return: number of rounds
 */
int amtRounds();

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void startGame(Game *game);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void displayPlayer(Player* player);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void startRound(Game* game);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void firstPlayer(Player* currentPlayer, Player* otherPlayer);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void displayProbability(int roll, int probability);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void loseRound();

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void roundOver();

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void roundScore(Player* player);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void pointSet(Player* player);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
char rollAgain();

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void win(Player* player);

/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void gameSummary(Player* p1, Player* p2);


//Not implemented yet
/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void highScore();
/**
 * Precondition:
 * Postcondition:
 * Return:
 */
bool playAgain();
/**
 * Precondition:
 * Postcondition:
 * Return:
 */
void leadingRound(Player* winner, Player* loser);
