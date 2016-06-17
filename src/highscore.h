#include <stdbool.h>

typedef struct{
    int score;
    char* date;
    char* name;
} Score;

/**
* Precondition: Highscore table option has been selected from the menu
* Post-Condition: The highscore table is displayed with the current high scores
* Returns: N/A
**/
void displayHighscores();

/**
* Precondition: A score has managed to be big enough to get onto the highscore table
* Post-Condition: The highscore table has a new entry with the username's name and their score.
* Returns: N/A
**/
void addHighscore(int score, char* name);

/**
* Precondition: N/A
* Post-Condition: An highscore table with (initially empty but will change) locally saved/stored high scores
* Returns: N/A
**/
void initHighscores();

/**
* Precondition: Game has ended and there are final scores from both players
* Post-Condition: The highscore table is either updated if it was bigger than the smallest one or not at all if it wasn't
* Returns: True if the score is bigger than the smallest score in the high score.
**/
bool isHighscore(int score);