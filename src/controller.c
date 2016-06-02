#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "ui.h"
#include "prob.h"
#include "roll.h"
#include "input.h"

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
    yourPlayer->rollCount = 0;
    yourPlayer->roundScore = 0;

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

        if(yourPlayer->lastRoll == yourPlayer->point){
            //print round reset and lost
            yourPlayer->roundScore = 0;
            loseRound(yourPlayer);

            break;
        } else {
            yourPlayer->roundScore += yourPlayer->point;

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

    // determine current player and other player
    if (p1Roll > p2Roll) {
        currentPlayer = p1;
        otherPlayer = p2;

    } else {
        currentPlayer = p2;
        otherPlayer = p1;
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


        //print current round over

        // go to next turn
        game->roundNumber++;
    }


    // print game over, determine and show winner
    printf("GAME OVER!\n");

//    gameSummary(p1, p2);

    if(p1->totalScore > p2->totalScore) {
        win(p1);
    } else if (p1->totalScore == p2->totalScore){
        printf("It's a tie!");
    }else{
        win(p2);
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

    // create a new game
    Game *game;
    game = malloc(sizeof(Game));

    // create 2 different players
    Player *p1;
    Player *p2;

    playMode = displayMenu();

    switch (playMode) {
        case 1:

            game->totalRounds = amtRounds();
            game->roundNumber = 1;

            p1 = getHumanPlayer("Player 1");
            p2 = getAIPlayer("AI Player 2");

            playGame(game, p1, p2);

            break;

        case 2:
            game->totalRounds = amtRounds();
            game->roundNumber = 1;

            p1 = getHumanPlayer("Player 1");
            p2 = getHumanPlayer("Player 2");

            playGame(game, p1, p2);

            break;

        case 3:
            printf("Player vs Network\n");
            break;
        case 4:
            printf("AI vs Network\n");
            break;
        case 5:
            printf("High score table\n");
            break;
        default:
            printf("INVALID INPUT!");

    }

}