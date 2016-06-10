#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "ui.h"
#include "prob.h"
#include "roll.h"
#include "input.h"
#include "highscore.h"

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

    displayPlayer(yourPlayer);

//    printf("Player %s - point set: %d\n", yourPlayer->name, yourPlayer->point);
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
        gameSummary(p1, p2);

        switchPlayer(&currentPlayer, &otherPlayer, &p1, &p2);

        // go to next turn
        game->roundNumber++;
    }

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

    return;
}


int main() {
    int playMode, playerRoll, opponentRoll, turnPlayer, turnOpponent, initialRoll;
    int lastRoll = 0;
    int scoreRound = 0;
    int totalScore = 0;
    bool quitRound = false;
    bool again;

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
                printf("Player vs Network\n");
                break;
            case 4:
                printf("AI vs Network\n");
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