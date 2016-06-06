

typedef struct{
    int score;
    char* date;
    char* name;
} Score;

void displayHighscore();

void addHighscore(int score, char* name);

void initHighscores();