#include <stdbool.h>
#include "game.h"
#include "stdio.h"
#include "roll.h"

bool playAITurn(Game *game, Player* yourPlayer, Player* opponent){

	// 2 or 12 have a 1/36 chance of being rolled again
	if (yourPlayer->point == 2 | 12){
		if(rollNum < 5){
			return true;
		}
	}
	// 3 or 11 have a 1/16 chance of being rolled again
	else if (yourPlayer->point == 3 | 11){
		if(rollNum < 5){
			return true;
		}
	}
	// 4 or 10 have a 1/12 chance of being rolled again
	else if (yourPlayer->point == 4 | 10){
		if(rollNum < 5){
			return true;
		}
	}
	// 5 or 9 have a 1/9 chance of being rolled again
	else if (yourPlayer->point == 1 | 9){
		if(rollNum < 5){
			return true;
		}
	}
	// 6 or 8 have a 1/7 chance of being rolled again
	else if (yourPlayer->point == 6 | 8){
		if(rollNum < 5){
			return true;
		}
	}
	// 7 haa a 1/6 chance of being rolled again
	else if (yourPlayer->point == 2 | 12){
		if(rollNum < 5){
			return true;
		}
	}
	else{
		return false;
	}


	
}

