#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PASS IN FIRST ROLL, RETURN STRING(chance of rolling again)
const char * prob(int firstRoll)
{
    switch(firstRoll){
        case 2:
            return "There is a 1/36 chance of rolling 2.";
        case 3:
            return "There is a 2/36 chance of rolling 3.";
        case 4:
            return "There is a 3/36 chance of rolling 4.";
        case 5:
            return "There is a 4/36 chance of rolling 5.";
        case 6:
            return "There is a 5/36 chance of rolling 6.";
        case 7:
            return "There is a 6/36 chance of rolling 7.";
        case 8:
            return "There is a 5/36 chance of rolling 8.";
        case 9:
            return "There is a 4/36 chance of rolling 9.";
        case 10:
            return "There is a 3/36 chance of rolling 10.";
        case 11:
            return "There is a 2/36 chance of rolling 11.";
        case 12:
            return "There is a 1/36 chance of rolling 12.";
    }
}
