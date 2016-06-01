#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "ui.h"
#include "prob.h"
#include "roll.h"
#include "input.h"


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
 *
 * DO NOT PROMPT IN HERE.  player->playTurn(game) PROMPTS.
 *
 * Order of operations:
 *
 * while(turn not over){
 *      int roll = currentPayer->playTurn(game);
 * }
 *
 *
 * switchPlayer(...);
 * currentPlayer->playTurn(game);
 */

void playRound(Game* game, Player* yourPlayer, Player* otherPlayer){

    bool doRoll;
    int playerRoll;

    // set the point and initialize round variables
    playerRoll = roll(2);
    yourPlayer->point = playerRoll;
    yourPlayer->rollCount = 0;
    yourPlayer->roundScore = 0;

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
            //TODO: print round reset and lost
            break;
        } else {
            yourPlayer->roundScore += yourPlayer->lastRoll;
            //TODO: print current round info
        }

        yourPlayer->rollCount++;
    }

    yourPlayer->totalScore += yourPlayer->roundScore;

    //TODO: print round over summary for current player
}


void playGame(Game* game, Player* p1, Player* p2){

    time_t t;
    srand((unsigned) time(&t));

    Player* currentPlayer;
    Player* otherPlayer;

    //TODO: print game information (Number of rounds, player names?)

    int p1Roll = roll(1);
    int p2Roll = roll(1);

    // keep rollin rollin rollin rollin
    while(p1Roll == p2Roll){
        p1Roll = roll(1);
        p2Roll = roll(1);
    }

    // determine current player and other player
    if (p1Roll > p2Roll) {
        currentPlayer = p1;
        otherPlayer = p2;
    } else {
        currentPlayer = p2;
        otherPlayer = p1;
    }

    //TODO: print game start (who's going first)

    while(game->roundNumber <= game->totalRounds){

        // print current round start

        // player the first players round
        playRound(game, currentPlayer, otherPlayer);
        switchPlayer(&currentPlayer, &otherPlayer, &p1, &p2);

        // play second players round
        playRound(game, currentPlayer, otherPlayer);

        //TODO: print current round over

        // go to next turn
        game->roundNumber++;
    }

    return;

    //TODO: print game over, determine and show winner

}


int main() {
    int playMode, playerRoll, opponentRoll, turnPlayer, turnOpponent, initialRoll;
//    int currRound = 1;
    int lastRoll=0;
    int scoreRound = 0;
    int totalScore = 0;
    bool quitRound = false;
    bool again;

    // create a new game
    Game* game;
    game = malloc(sizeof(Game));

    // create 2 different players
    Player* p1;
    Player* p2;

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
            printf("INVALID INPUT, DUMBFUCK!");

    }
}