#include <stdbool.h>

typedef struct{
    int score;
    char* date;
    char* name;
} Score;

void displayHighscores();

void addHighscore(int score, char* name);

void initHighscores();

bool isHighscore(int score);