#include <stdbool.h>
#include "stdio.h"
#include "roll.h"
#include "player.h"

bool playAITurn(Game *game, Player* yourPlayer, Player* opponent){

	// 2 or 12 have a 1/36 chance of being rolled again
	if (yourPlayer->point == 2 || yourPlayer->point == 12){
		if(yourPlayer->rollCount < 20){
			return true;
		}
	}
	// 3 or 11 have a 1/16 chance of being rolled again
	else if (yourPlayer->point == 3 || yourPlayer->point == 11){
		if(yourPlayer->rollCount < 9){
			return true;
		}
	}
	// 4 or 10 have a 1/12 chance of being rolled again
	else if (yourPlayer->point == 4 || yourPlayer->point == 10){
		if(yourPlayer->rollCount < 7){
			return true;
		}
	}
	// 5 or 9 have a 1/9 chance of being rolled again
	else if (yourPlayer->point == 1 || yourPlayer->point == 9){
		if(yourPlayer->rollCount < 5){
			return true;
		}
	}
	// 6 or 8 have a 1/7 chance of being rolled again
	else if (yourPlayer->point == 6 || yourPlayer->point == 8){
		if(yourPlayer->rollCount < 5){
			return true;
		}
	}
	// 7 haa a 1/6 chance of being rolled again
	else if (yourPlayer->point == 7){
		if(yourPlayer->rollCount < 4){
			return true;
		}
	}
	else{
		return false;
	}


	
}

