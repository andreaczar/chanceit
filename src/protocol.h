
typedef struct {
    int roundScore;
    int gameScore;
    int roundNumber;
    int roll;
} TurnInfo;


int connectPlayer(char* name);
int getOpponent(char** opponent);
int isGameOver (char* response);
int getInitialRolls(int *p1, int *p2);
int getTurnStart(int *p1Score, int *p2Score);
int getYourRoll(int *dieOne, int *dieTwo);
int getTurnNumber(int *turnNum);
int checkOpponentTurn(int *p1, int *p2);