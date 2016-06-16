#include <stdbool.h>
#include "stdio.h"
#include "roll.h"
#include "player.h"
#include <unistd.h>

bool playAITurn(Game *game, Player* yourPlayer, Player* opponent){
	sleep(1);

	printf("AI Point: %d, rollCount: %d\n", yourPlayer->point, yourPlayer->rollCount);
	printf("Your score: %d, opponent: %d\n", yourPlayer->totalScore, opponent->totalScore);

	// 2 or 12 have a 1/36 chance of being rolled again
	if (yourPlayer->point == 2 || yourPlayer->point == 12){
		if(yourPlayer->rollCount < 19){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 27){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
	// 3 or 11 have a 1/16 chance of being rolled again
	else if (yourPlayer->point == 3 || yourPlayer->point == 11){
		if(yourPlayer->rollCount < 9){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 13){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
	// 4 or 10 have a 1/12 chance of being rolled again
	else if (yourPlayer->point == 4 || yourPlayer->point == 10){
		if(yourPlayer->rollCount < 7){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 10){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
	// 5 or 9 have a 1/9 chance of being rolled again
	else if (yourPlayer->point == 5 || yourPlayer->point == 9){
		if(yourPlayer->rollCount < 5){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 8){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
	// 6 or 8 have a 1/7 chance of being rolled again
	else if (yourPlayer->point == 6 || yourPlayer->point == 8){
		if(yourPlayer->rollCount < 5){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 6){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
	// 7 haa a 1/6 chance of being rolled again
	else if (yourPlayer->point == 7){
		if(yourPlayer->rollCount < 4){
			return true;
		}
		if(yourPlayer->totalScore < opponent->totalScore){
			if(yourPlayer->rollCount < 6){
				printf("Desperation mode enabled\n");
				return true;
			}
		}
	}
//	else if (game->roundNumber == game->totalRounds && yourPlayer->totalScore < opponent->totalScore && yourPlayer->firstTurn == false){
//		return true;
//	}

	printf("\n\nAI decided to hold....\n\n");
	sleep(3);

	return false;

	
}

