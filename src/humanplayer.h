#include <stdbool.h>


/**
 * Precondition: The current turn is the user
 * Postcondition: Will either roll again or not depending on user input.
 * Return: True if the user wants to keep rolling, false otherwise.
 */
bool playHumanTurn(Game *game, Player* yourPlayer, Player* opponent);