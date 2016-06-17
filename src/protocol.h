typedef struct {
    int roundScore;
    int gameScore;
    int roundNumber;
    int roll;
} TurnInfo;

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays that the connection has been made 
* Cleanup: Frees up the message recieved.
* Returns: N/A
*/
int connectPlayer(char *name);

/*
* Precondition: Connection has been made from the server
* Postcondition: Gets an opponent from the server
* Cleanup: Frees up the message recieved.
* Returns: 1 if successful and zero otherwise
*/
int getOpponent(char **opponent);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the winner of the game
* Cleanup: Frees up the message recieved.
* Returns: A one if it was successful and a zero if not
*/
int isGameOver(char *response);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the initial rolls to determine who goes first 
* Cleanup: Frees up the message recieved.
* Returns: A zero if succesful and nothing otherwise
*/
int getInitialRolls(int *p1, int *p2);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the starting score of both players
* Cleanup: Frees up the message recieved
* Returns: integer 0 if ok, nothing otherwise
*/
int getTurnStart(int *p1Score, int *p2Score);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the roll you made 
* Cleanup: Frees up the message recieved
* Returns: A zero if successful and nothing otherwise
*/
int getYourRoll(int *dieOne, int *dieTwo);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the turn number
* Cleanup: Frees up the message recieved
* Returns: A 0 if successful. Nothing otherwise
*/
int getTurnNumber(int *turnNum);

/*
* Precondition: Connection has been made from the server
* Postcondition: Continously parses through the information on the server 
* until it hit's the 'chance-it' string
* Cleanup: Frees up the message recieved
* Returns: An integer of zero if it worked and nothing otherwise 
*/
int readTurn(int *rollTotal, int *currentTurn, int *roundScore, int *p1Score, int *p2Score);

/*
* Precondition: Connection has been made from the server
* Postcondition: Displays the 'chance it?' message
* Cleanup: Frees up the message recieved.
* Returns: An integer of zero if it worked and nothing otherwise 
*/
int waitForPrompt();