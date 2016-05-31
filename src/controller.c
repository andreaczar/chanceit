#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "ui.h"
#include "prob.h"
#include "roll.h"
#include "player.h"


int main() {
    int playMode, playerRoll, opponentRoll, turnPlayer, turnOpponent, initialRoll;
    int currRound = 1;
    bool firstRoll = true;
    time_t t;
    //Seed
    srand((unsigned) time(&t));

    playMode = displayMenu();

    // create a new game
    Game* game;
    game = malloc(sizeof(Game));

    game->roundNumber = 1;

    // create 2 different players
    Player* p1;
    Player* p2;

    bool again = rollAgain();

    Player* currentPlayer;

    int p1Roll, p2Roll;

    switch (playMode) {
        case 1:

            game->totalRounds = amtRounds();


            p1 = getHumanPlayer("Player 1");
            p2 = getAIPlayer("AI Player 2");

            p1Roll = p1->roll(1);
            p2Roll = p2->roll(1);

            // keep rollin rollin rollin rollin
            while(p1Roll == p2Roll){
                p1Roll = p1->roll(1);
                p2Roll = p2->roll(1);
            }

            // print who's going first and round count details
            startRound(p1Roll, p2Roll, currRound, game->totalRounds);

            if (p1Roll > p2Roll) {
                currentPlayer = p1;
            } else {
                currentPlayer = p2;
            }
            break;

        case 2:
            printf("Player vs Player\n");
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