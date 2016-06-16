#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

#include "ui.h"
#include "roll.h"
#include "highscore.h"
#include "socket.h"
#include "protocol.h"
#include "prob.h"

// switch player
void switchPlayer(Player** currentPlayer, Player** otherPlayer, Player** p1, Player** p2){
    if(*currentPlayer == *p1){
        *currentPlayer = *p2;
        *otherPlayer = *p1;
    } else {
        *currentPlayer = *p1;
        *otherPlayer = *p2;
    }
}

/**
 * Play the game (all rounds) for the players tha were setup
 * Return the winning player.
 */

void playRound(Game* game, Player* yourPlayer, Player* otherPlayer){

    bool doRoll;
    int playerRoll;

    // set the point and initialize round variables
    playerRoll = roll(2);
    yourPlayer->point = playerRoll;
    yourPlayer->rollCount = 1;
    yourPlayer->roundScore = yourPlayer->point;

    displayPlayer(yourPlayer, otherPlayer);

    pointSet(yourPlayer);

    while(true){

        // call the function pointer for this type of player to
        // determine if they want to roll again.
        doRoll = yourPlayer->playTurn(game, yourPlayer, otherPlayer);

        // player does not want to roll, end round for player
        if(!doRoll){
            break;
        }

        yourPlayer->lastRoll = roll(2);

        if(yourPlayer->lastRoll == yourPlayer->point) {

            //print round reset and lost
            yourPlayer->roundScore = 0;
            loseRound(yourPlayer);

            break;

        } else {

            yourPlayer->roundScore += yourPlayer->lastRoll;

            // print current round info
            roundScore(yourPlayer);
        }
        yourPlayer->rollCount++;
    }

    yourPlayer->totalScore += yourPlayer->roundScore;

    // print round over summary for current player
    roundOver(yourPlayer);
}


void playGame(Game* game, Player* p1, Player* p2){

    time_t t;
    srand((unsigned) time(&t));



    Player* currentPlayer;
    Player* otherPlayer;

    //print game information (Number of rounds, player names?)
    startGame(game);

    int p1Roll = roll(1);
    int p2Roll = roll(1);

    // keep rollin rollin rollin rollin
    while(p1Roll == p2Roll){
        p1Roll = roll(1);
        p2Roll = roll(1);
    }

    p1->lastRoll = p1Roll;
    p2->lastRoll = p2Roll;

    // determine current player(player 1) and other player(player 2)
    // set first turn to true for player who rolled highest
    if (p1Roll > p2Roll) {
        currentPlayer = p1;
        otherPlayer = p2;
        p1->firstTurn = true;

    } else {
        currentPlayer = p2;
        otherPlayer = p1;
        p2->firstTurn = true;
    }

    //print game start (who's going first)
    firstPlayer(currentPlayer, otherPlayer);

    while(game->roundNumber <= game->totalRounds){

        // print current round start
        startRound(game);
        // player the first players round
        playRound(game, currentPlayer, otherPlayer);
        switchPlayer(&currentPlayer, &otherPlayer, &p1, &p2);

        // play second players round
        playRound(game, currentPlayer, otherPlayer);

        // summary of game score


        switchPlayer(&currentPlayer, &otherPlayer, &p1, &p2);

        // go to next turn
        game->roundNumber++;
    }
    gameSummary(p1, p2);
    gameOver();

    if(p1->totalScore > p2->totalScore) {
        win(p1);

        if(isHighscore(p1->totalScore)){
            highScore();
            addHighscore(p1->totalScore, p1->name);
        }
    } else if (p1->totalScore == p2->totalScore){
        printf("It's a tie!");
    }else{
        win(p2);
        if(isHighscore(p2->totalScore)){
            highScore();
            addHighscore(p2->totalScore, p2->name);
        }
    }
    returnToMainMenu();
    return;
}

int playNetworkOpponentTurn(Player *p){
	
	int p1Score, p2Score, returnCode;
	returnCode = checkOpponentTurn(&p1Score, &p2Score);
	p->totalScore = p1Score;
	return returnCode;
	
}


void playNetworkGame(Game* game, Player* p1, Player* p2){
    int p1Roll, p2Roll;
    Player* currentPlayer;
    Player* otherPlayer;

    startGame(game);
    getInitialRolls(&p1Roll, &p2Roll);


    p1->lastRoll = p1Roll;
    p2->lastRoll = p2Roll;

    // determine current player(player 1) and other player(player 2)
    // set first turn to true for player who rolled highest
    if (p1Roll > p2Roll) {
        currentPlayer = p1;
        otherPlayer = p2;
        p1->firstTurn = true;

    } else {
        currentPlayer = p2;
        otherPlayer = p1;
        p2->firstTurn = true;
    }

    firstPlayer(currentPlayer, otherPlayer);

    int p1Score, p2Score;

    getTurnStart(&p1Score, &p2Score);

    printf("P1 Score: %d\n", p1Score);
    printf("P2 Score: %d\n", p2Score);
	
	
	while(currRound < maxRounds){
		
		if(p1->firstTurn){
			//play network player turn
			handlePlayerTurn(p1);
			//play network opponent turn
			playNetworkOpponentTurn(p2);
			//
		}
		else{
			//Play network opponent turn
			playNetworkOpponentTurn(p2);
			//Play network player turn
			handlePlayerTurn(p1);
		}
		
	}

    exit(0);
}
int currRound = 1;
int maxRounds = 20;
int turnNum = 0;
int roll = 0;
int dieOne = 0;
int dieTwo = 0;
int dieSum = 0;
int theFirstTurn = 1;
char input;
char name;
double probability;
int firstRoll;
int rollCount = 1;

int handlePlayerTurn(Player *p){
	/*
		dieSum = dieOne + dieTwo;
		//currentPlayer->totalScore += dieSum;
		
		
		if (rollCount == 1){
			p->point = dieSum;
		}
		if (p->point == dieSum && rollCount > 1){
			printf("You rolled the first roll\n");
			rollCount = 1;
			p->roundScore = 0;
			currRound++;		
		}
		
		
		else{
		getTurnNumber(&turnNum);
		getYourRoll(&dieOne, &dieTwo);
		
		printf("You rolled: %d\n", currentPlayer->point);
			
		input = rollAgain();
		printf("%c\n", input);
		if(input == 'y' || input == 'Y'){
			clientSend("Y\n");
			rollCount++;
		}
		else if (input == 'n' || input == 'N'){
			clientSend("n\n");
			roundScore(currentPlayer);
			currRound++;
			
		}
		else if (input == 'q' || input == 'Q'){
			
			clientSend(("GOODBYE: %s\n", currentPlayer->name));
		}
		else if (input == 'p' || input == 'P'){
			probability = prob(currentPlayer);
			displayProbability(currentPlayer, probability);
		}
		//clientSend(input + 26);
		//clientRecv(output);
		
		}
	}
*/


}

int main() {
    int playMode, playerRoll, opponentRoll, turnPlayer, turnOpponent, initialRoll;

    //connection stuff
    char *IP = "52.38.98.137";
    int port = 1099;
    char *msg;
    struct sockaddr_in server;

    initHighscores();

    // create a new game
    Game *game;
    game = malloc(sizeof(Game));

    // create 2 different players
    Player *p1;
    Player *p2;

    char* name;
    char* name2;

    while(1) {
        playMode = displayMenu();

        switch (playMode) {
            case 1:

                name = getPlayerName();

                game->totalRounds = amtRounds();
                game->roundNumber = 1;

                p1 = getHumanPlayer(name);
                p2 = getAIPlayer("AI Bob");

                playGame(game, p1, p2);

                break;

            case 2:

                name = getPlayerName();
                name2 = getPlayerName();

                game->totalRounds = amtRounds();
                game->roundNumber = 1;

                p1 = getHumanPlayer(name);
                p2 = getHumanPlayer(name2);

                playGame(game, p1, p2);

                break;

            case 3:
                game->totalRounds = 20;
                game->roundNumber = 1;

                printf("Player vs Network\n");
                name = getPlayerName();
                p1 = getHumanPlayer(name);
                printf("Got human player\n");


                serverConnect(IP, port);

                connectPlayer(name);

                char* opponent;
                getOpponent(&opponent);
                p2 = getRemotePlayer(opponent);

                playNetworkGame(game, p1, p2);

                break;
            case 4:
                game->totalRounds = 20;
                game->roundNumber = 1;

                printf("AI vs Network\n");
                name = getPlayerName();
                p1 = getAIPlayer(name);
                printf("Got AI player\n");


                serverConnect(IP, port);

                connectPlayer(name);

                //char* opponent;
                getOpponent(&opponent);
                p2 = getRemotePlayer(opponent);

                playNetworkGame(game, p1, p2);

                break;				

            case 5:
                displayHighscores();
                break;

            case 6:
                printf("Thanks for playing. Goodbye.\n");
                exit(0);

            default:
                printf("Invalid Input! Enter a number: 1-6\n");

        }
    }
}