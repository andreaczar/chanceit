#include <stdbool.h>


/**
 * Precondition: An AI mode has been selected.
 * Postcondition: Keeps rolling depending on the roll and the intial roll.
 * Return: True if it wants to keep rolling or false if it doesn't.
 */
bool playAITurn(Game *game, Player* yourPlayer, Player* opponent);