#include <stdio.h>
#include <stdlib.h>
//#include anything else here
int  input (){
	char yesNo;
	printf("Enter either y for yes, n for no, p for probability or q to quit.\n");
	scanf(" %c", &yesNo);

	if (yesNo == 'y' || yesNo == 'Y'){

		return 1;
	}
	else if (yesNo == 'n' || yesNo == 'N'){
		
		return 2;
	}

	else if (yesNo == 'p' || yesNo == 'P'){	
		return 3;
	}
	else if (yesNo == 'q' || yesNo == 'Q'){
		return 4;
	}
	return 0;
}
int player (bool boolFirstRoll, int first_roll, int roll){
	initialRoll = roll(2);
		int updated_total_score = round_sum + game_score;
		int lead = updated_total_score - opponentSum;

		if(boolFirstRoll){
			//firstRoll();
			boolFirstRoll == false;
			

		} else if (first_roll == roll){
			printf("Turn over. You rolled your 'First Roll'.\n");
			printf("Round Score: 0.\n");
			printf("Total Score: %d.\n", game_score);


		} else {
			printf("You rolled %d. Round Score: %d.\n", roll, round_sum);
		}

		if(first_roll != roll){
			printf("Roll again? (Y/n)\n");
		} 
}
/*
int main(){
	 
	int decision = input();
	if (decision == 1){
		printf("you said yes");
	}
	else if (decision == 2){
		printf("you said no");
	}
	else if (decision == 3){
		printf("you said probability");
	}
	else if (decision == 4){
		printf("you wanna leave");
	}
	else{
		printf("Invalid input, dumbass");
	}
	return 0;	
}*/
