typedef struct {
    int roundScore;
    int gameScore;
    int roundNumber;
    int roll;
} TurnInfo;

/*
* Precondition: N/A
* Postcondition: a connection is made
* Cleanup: Frees up the message sent to server.
* Returns: N/A
*/
int connectPlayer(char *name);

/*
* Precondition: Connection has been made to the server
* Postcondition: Gets the opponent's name from the server
* Returns: 1 if successful, 0 otherwise
*/
int getOpponent(char **opponent);


/*
* Precondition: Connection has been made to the server
* Postcondition: Initial rolls for both players is stored in parameters p1 and p2
* Returns: A zero if succesful and nothing otherwise
*/
int getInitialRolls(int *p1, int *p2);

/*
* Precondition: A turn is waiting in the buffer
* Postcondition: Turn information is stored in passed parameters
* Returns: -1 if round score is 0,
 *          0 if round score > 0
 *          2 if game ended
*/
int readTurn(int *rollTotal, int *currentTurn, int *roundScore, int *p1Score, int *p2Score);

/*
* Precondition: A game has ended and input has not been read.
* Postcondition: Final score stored in parameters p1 and p2.
* Returns: 0 if successful
*/
int getFinalScore(int *p1, int *p2);