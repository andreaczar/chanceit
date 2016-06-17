#include <stdlib.h>
#include <stdbool.h>
#include "roll.h"
#include "ui.h"
#include "prob.h"


bool playHumanTurn(Game *game, Player* yourPlayer, Player* opponent){


    char response;

    while(true){
        response = rollAgain();

        if(response == 'q'){
            gameOver();
            win(opponent);
            printf("%s quit the game.\n", yourPlayer->name);
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
