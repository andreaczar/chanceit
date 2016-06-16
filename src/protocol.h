typedef struct {
    int roundScore;
    int gameScore;
    int roundNumber;
    int roll;
} TurnInfo;


int connectPlayer(char *name);

int getOpponent(char **opponent);

int isGameOver(char *response);

int getInitialRolls(int *p1, int *p2);

int getTurnStart(int *p1Score, int *p2Score);

int getYourRoll(int *dieOne, int *dieTwo);

int getTurnNumber(int *turnNum);

int readTurn(int *rollTotal, int *currentTurn, int *roundScore, int *p1Score, int *p2Score);

int waitForPrompt();

int getFinalScore(int *p1, int *p2);