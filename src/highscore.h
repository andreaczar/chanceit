#include <stdbool.h>

typedef struct{
    int score;
    char* date;
    char* name;
} Score;

/**
* Precondition: High score table option has been selected from the main menu
* Post-Condition: Calls the UI to display the high score table (top ten scores)
 * Cleanup: frees memory allocatd to scores
* Returns: N/A
**/
void displayHighscores();

/**
* Precondition: Player has received a high score.
* Post-Condition: writeHighscores was called. Player's score was added in sorted (decending)
 * order to the high score table text file along with their score, name, and date.
* Returns: N/A
**/
void addHighscore(int score, char* name);

/**
* Precondition: No high score table exists yet.
* Post-Condition: Empty high score table template was created (holds 10 scores).
* Returns: N/A
 * Cleanup: free memory
**/
void initHighscores();

/**
* Precondition: Game has ended
* Post-Condition: N/A
* Returns: True if the score is higher than the lowest score in the table, false otherwise
**/
bool isHighscore(int score);