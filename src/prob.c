#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prob.h"

// PASS IN FIRST ROLL, RETURN STRING(chance of rolling again)
double prob(Player* player)
{
    switch(player->point){
        case 2:
        case 12:
            return 2.8;
        case 3:
        case 11:
            return 5.6;
        case 4:
        case 10:
            return 8.3;
        case 5:
        case 9:
            return 11.1;
        case 6:
        case 8:
            return 13.9;
        case 7:
            return 16.7;
    }
}
