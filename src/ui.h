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
 * Precondition: N/A
 * Postcondition: Prints the current round and comparing that to the round they put in.
 * Return: Returns number of rounds
 */
void startGame(Game *game);

/**
 * Precondition: N/A
 * Postcondition: Displays the rounds.
 * Return: N/A
 */
//void displayPlayer(Player* player);


void displayPlayer(Player* current, Player* opponent);

/**
 * Precondition: N/A
 * Postcondition: Displays who's turn it is.
 */
void startRound(Game* game);

/**
 * Precondition: two players
 * Postcondition: N/A
 * Return: N/A
 */
void firstPlayer(Player* currentPlayer, Player* otherPlayer);

/**
 * Precondition: N/A
 * Postcondition: Displays a message saying you've rolled the initial roll.
 */
void loseRound();

/**
 * Precondition: N/A
 * Postcondition: Displays a message saying the current player's round is over.
 */
void roundOver();

/**
 * Precondition: N/A
 * Postcondition: Displays what the user has rolled along with their round score.
 */
void roundScore(Player* player);

/**
 * Precondition:N/A
 * Postcondition: Displays the first roll.
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
 * Returns: A character (upper or lowercase y, n, p, q) or an error message.
 */
char rollAgain();

/**
 * Precondition: N/A
 * Postcondition: Displays whose won the game.
 */
void win(Player* player);

/**
 * Precondition: N/A
 * Postcondition: Displays the score for both players.
 */
void gameSummary(Player* p1, Player* p2);

/**
 * Precondition: User wants the high score table
 * Postcondition: Displays the text file of the high score table.
 */
void highScore();
/**
 * Precondition: A game has been finished.
 * Postcondition: Displays a prompt asking if you want to play again.

 */
bool playAgain();
/**
 * Precondition: N/A
 * Postcondition: Displays a prompt asking if you want to play again.
 */
void leadingRound(Player* winner, Player* loser);
/**
*  Precondition: N/A
*  Postcondition: Displays a response saying that you got a high score
*/
void highScore();
/**
*  Precondition: N/A
*  Postcondition: Displays ascii art for the highscore table.
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
*  Precondition: Game is over
*  Postcondition: Re-Displays main menu screen
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