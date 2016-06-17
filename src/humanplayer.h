#include <stdbool.h>


/**
 * Precondition: The current turn is the user
 * Postcondition: User decided to Roll again, end turn, quit game, or display probability
 * Return: True if the user wants to keep rolling, false otherwise.
 */
bool playHumanTurn(Game *game, Player* yourPlayer, Player* opponent);