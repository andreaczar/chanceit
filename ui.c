#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui.h"

void displayMenu(){
    printf("***********************************************************\n");
    printf("*                                                         *\n");   
    printf("*                      CHANCE-IT!                         *\n");
    printf("*                                                         *\n"); 
    printf("***********************************************************\n");

    printf("-----------------------------------------------------------\n");
    printf("MAIN MENU\n");
    printf("\n");
    printf("Enter a number to select an action: \n");
    printf("\n");
    printf("1 - Play single player against AI\n");
    printf("2 - Play against an opponent on the same machine\n");
    printf("3 - Play against a network opponent\n");
    printf("4 - Play as AI over a network\n");
    printf("5 - View high scores\n");
    printf("6 - Exit program\n");
    printf("-----------------------------------------------------------\n");
    printf("\n"); 
}

void amtRounds(){

    printf("-----------------------------------------------------------\n");
    printf("Enter the number of rounds (20 is the default):\n");
    printf("-----------------------------------------------------------\n");
}

void startRound(int player_roll, int opponent_roll, int roundNum, int totalRound){


    printf("-----------------------------------------------------------\n");
    printf("START, Round %d/%d (Q to quit)\n", roundNum, totalRound);
    printf("-----------------------------------------------------------\n");

    if(player_roll > opponent_roll){
        printf("You rolled %d. Opponent rolled %d. You go first!\n", player_roll, opponent_roll);
    } else {
        printf("You rolled %d. Opponent rolled %d. Opponent goes first!\n", player_roll, opponent_roll);
    }
}

void displayProbability(int roll, int probability){

    printf("The probability of rolling %d again is: %d%%\n", roll, probability);
}


void playAgain(){

    printf("Would you like to play another game? (Y/n)\n");
}

void rollStatus(bool boolFirstRoll, int first_roll, int roll, int round_sum, int game_score, int opponentSum){

    int updated_total_score = round_sum + game_score;
    int lead = updated_total_score - opponentSum;

    if(boolFirstRoll){
        printf("You rolled %d. First roll set to: %d.\n", first_roll, first_roll);

    } else if (first_roll == roll){
        printf("Turn over. You rolled your 'First Roll'.\n");
        printf("Round Score: 0.\n");
        printf("Total Score: %d.\n", game_score);

    } else if (updated_total_score > opponentSum){
        printf("You rolled %d. Round Score: %d. You are in the lead by %d!\n", roll, round_sum, lead);

    } else {
        printf("You rolled %d. Round Score: %d.\n", roll, round_sum);
    }

    if(first_roll != roll){
        printf("Roll again? (Y/n)\n");
    }
}

void turnOver(){
    printf("Turn Over\n");
}

void win(int score){
    printf("Your score is: %d. YOU WIN!\n", score);
}

void highScore(){
    printf("-----------------------------------------------------------\n");
    printf("Congratulations, you have a high score!\nPlease enter your name: \n");
    printf("-----------------------------------------------------------\n");
}



