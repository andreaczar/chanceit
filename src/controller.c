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

int playLocalPlayerTurn(Game *game, Player *p, Player *opponent){

    int returnCode = 0;
    p->point = 0;

    int rollTotal, turnScore, currentTurn;
    char input;


    // do a fake turn to get the point
    returnCode = readTurn(&rollTotal,
                          &turnScore,
                          &currentTurn,
                          &p->totalScore,
                          &opponent->totalScore);

    p->point = rollTotal;
    p->roundScore = rollTotal;
    p->rollCount++;

    displayPlayer(p, opponent);
    pointSet(p);

    // keep asking if they want to roll again until we get
    // something that breaks us out of the loop.
    while(1){

        input = rollAgain();

        if(input == 'y'){

            // keep rollin rollin rollin rollin
            clientSend("Y\n");

            returnCode = readTurn(&rollTotal,
                                  &turnScore,
                                  &currentTurn,
                                  &p->totalScore,
                                  &opponent->totalScore);

            if(returnCode == -1){
                p->roundScore = 0;
                loseRound(p);
                break;
            }

            p->roundScore += rollTotal;
            p->lastRoll = rollTotal;
            p->rollCount++;

            roundScore(p);


        } else if(input == 'n'){
            printf("End turn and break\n");
            clientSend("n\n");
            break;

        } else if(input == 'p'){
            printf("Show probability\n");

        } else if(input == 'q'){
            printf("Stop game\n");

        } else {
            printf("Invalid input: %c", input);
        }
    }

    p->totalScore += p->roundScore;

    roundOver(p);

    return 0;

}

int playNetworkAITurn(Game *game, Player *p, Player *opponent){

    int returnCode = 0;
    p->point = 0;

    int rollTotal, turnScore, currentTurn;
    bool again;

    p->rollCount = 0;

    // do a fake turn to get the point
    returnCode = readTurn(&rollTotal,
                          &turnScore,
                          &currentTurn,
                          &p->totalScore,
                          &opponent->totalScore);

    p->point = rollTotal;
    p->roundScore = rollTotal;
    p->rollCount++;

    displayPlayer(p, opponent);
    pointSet(p);

    // keep asking if they want to roll again until we get
    // something that breaks us out of the loop.
    while(1){

        if(p->playTurn(game, p, opponent)){

            // keep rollin rollin rollin rollin
            clientSend("Y\n");

            returnCode = readTurn(&rollTotal,
                                  &turnScore,
                                  &currentTurn,
                                  &p->totalScore,
                                  &opponent->totalScore);

            if(returnCode == -1){
                p->roundScore = 0;
                loseRound(p);
                break;
            }

            p->roundScore += rollTotal;
            p->lastRoll = rollTotal;
            p->rollCount++;
        } else {
            clientSend("n\n");
            break;
        }

        roundScore(p);

    }

    p->totalScore += p->roundScore;

    roundOver(p);

    return 0;

}

void playNetworkGame(Game* game, Player* p1, Player* p2, bool ai){

    int currRound = 1;
    int maxRounds = 20;
    int p1Roll, p2Roll;
    bool firstRound = true;
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

	
	while(currRound <= maxRounds){

        displayPlayer(p1, p2);

        pointSet(p1);

        startRound(game);

		if(p1->firstTurn){

            if(ai){
                playNetworkAITurn(game, p1, p2);
            } else {
                playLocalPlayerTurn(game, p1, p2);
            }
            printf("\n\nWaiting for player 2 to complete their turn ..\n\n");

		} else {

            printf("\n\nWaiting for player 2 to complete their turn ..\n\n");
            if(ai){
                playNetworkAITurn(game, p1, p2);
            } else {
                playLocalPlayerTurn(game, p1, p2);
            }
		}

        game->playerOneScore = p1->totalScore;
        game->playerTwoScore = p2->totalScore;
        game->roundNumber += 1;

	}

    gameSummary(p1, p2);
    gameOver();

    exit(0);
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

                playNetworkGame(game, p1, p2, false);

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

                playNetworkGame(game, p1, p2, true);

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