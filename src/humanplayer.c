#include <stdbool.h>
#include <stdlib.h>
#include "roll.h"
#include "ui.h"
#include "prob.h"
/*
 * Play the human turn.
 *
 * this should probably talk to the ui.
 *
 * Should probably present some kind of output to the player (roll infos, probabilities, etc),
 * accept input then return the roll (or the skip with ??roll == 0??)
 */
bool playHumanTurn(Game *game, Player* yourPlayer, Player* opponent){


    char response;

    while(true){
        response = rollAgain();

        if(response == 'q'){
            exit(0);
        } else if(response == 'y'){
            return true;
        } else if(response == 'n'){
            return false;
        } else if(response == 'p') {
            //show probability
            double p = prob(yourPlayer);
            displayProbability(yourPlayer, p);

        }
    }


}
