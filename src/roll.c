#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "roll.h"

int roll(int numDice) {

    if(numDice == 2)
    {
        return(rand() % (13-2)+2);
    }
    if(numDice == 1)
    {
        return(rand() % (7-1)+1);
    }
}
