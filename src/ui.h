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
 * Postcondition: Number of rounds is entered by user.
 * Return: number of rounds
 */
int amtRounds();

/**
 * Precondition: N/A
 * Postcondition: Displays the number of rounds selected by the user.
 */
void startGame(Game *game);

/**
 * Precondition: N/A
 * Postcondition: Displays whose round it is. Displays the game score in the format (player - opponent)
 * Return: N/A
 */
void displayPlayer(Player* current, Player* opponent);

/**
 * Precondition: N/A
 * Postcondition: Displays the beginning of the round.
 */
void startRound(Game* game);

/**
 * Precondition: two players
 * Postcondition: Shows both players initial rolls and displays who plays first.
 * Return: N/A
 */
void firstPlayer(Player* currentPlayer, Player* otherPlayer);

/**
 * Precondition: current player lost the round.
 * Postcondition: Displays roll, round score, and that the players turn is over.
 */
void loseRound();

/**
 * Precondition: Player finished a round
 * Postcondition: Round summary displaying current players total round score and game score.
 */
void roundOver();

/**
 * Precondition: N/A
 * Postcondition: Displays the users roll along with their updated round score.
 */
void roundScore(Player* player);

/**
 * Precondition:N/A
 * Postcondition: Displays the first roll (the roll to avoid again).
 */
void pointSet(Player* player);

/**
* Precondition: Game has been started
* Postcondition: Gets a username from the user
* Returns: the username that was entered by the user
**/
char* getPlayerName();

/**
 * Precondition: N/A
 * Postcondition: Gets the input from player and will pass the info to the controller.
 * Returns: A character (upper or lowercase) y to roll again, n to stop rolling,
 *          p to view probability, or q to quit) or an error message.
 */
char rollAgain();

/**
 * Precondition: a player has won the game.
 * Postcondition: Displays who has won the game.
 */
void win(Player* player);

/**
 * Precondition: Both players have finished playing a round.
 * Postcondition: Displays the updated game score for both players at the end of each round..
 */
void gameSummary(Player* p1, Player* p2);

/**
 * Precondition: Player received a high score.
 * Postcondition: Displays to the user that they have a high score.
 */
void highScore();

/**
*  Precondition: N/A
*  Postcondition: Displays the high score table.
*/
void highScoreTable();

/**
*  Precondition: Game has been ended
*  Postcondition: Displays ASCII art for the gave over screen
*/
void gameOver();

/**
*  Precondition: Probability has been called
*  Postcondition: Displays probability of rolling first roll again.
*/
void displayProbability(Player* player, double probability);

/**
*  Precondition: Game ended.
*  Postcondition: Re-Displays main menu screen when user presses any key.
**/
void returnToMainMenu();

/**
*  Precondition: N/A
*  Postcondition: Prints a side at the beginning and end of the screen
**/
void printSide();

/**
*  Precondition: N/A
*  Postcondition: Prints a asterisk bar
**/
void printBar();