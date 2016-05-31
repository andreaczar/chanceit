#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ui.c"
#include "prob.h"
#include "roll.h"
#include "player.h"
#include <ctype.h>



int main(){
       int mode, totalRounds, playerRoll, opponentRoll, turnP, turnO, initialRoll;
       int currRound = 1;
       bool firstRoll = true;
       time_t t;
       //Seed
       srand((unsigned) time(&t));
      
       displayMenu();
       scanf(" %d", &mode);
   
       switch(mode){
       		case 1: 
			
			amtRounds();
			scanf("%d", &totalRounds);
			//if (isdigit(totalRounds)){
				while (totalRounds < 1 || totalRounds > 20){
					printf("Enter number between 1 and 20\n");
					scanf(" %d", &totalRounds);
				}
				
				turnP = roll(1);
				turnO = roll(1);
				printf("%d\n", turnP);
				printf("%d\n", turnO);
				startRound(turnP, turnO, currRound, totalRounds);
				if (turnP > turnO){
					//Function call stuff in UI and player.
				}
			//while (game isn't over)			

			//}
				//printf("Invalid input, dumbass\n");


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
