#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui.h"
#include "input.h"
#include "player.h"

int displayMenu(){
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

    return getInt("\n");
}

int amtRounds(){

    int rounds = 0;

    while (rounds < 1 || rounds > 20) {
        printf("-----------------------------------------------------------\n");
        printf("Enter the number of rounds (20 is the max):\n");
        rounds = getInt("-----------------------------------------------------------\n");
    }

    return rounds;
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

void roundOver(Player* player){
    printf("Turn over. You rolled your 'First Roll'.\n");
    printf("Round Score: 0.\n");
    printf("Total Score: %d.\n", player->totalScore);
}

void roundScore(Player* player){
    printf("%s rolled %d. Round Score: %d.\n", player->name, player->lastRoll, player->roundScore);
}

void leadingRound(Player* winner, Player* loser){
    int lead = winner->roundScore + winner->totalScore - loser->roundScore - loser->totalScore;

    printf("You rolled %d. Round Score: %d. You are in the lead by %d!\n",
           winner->lastRoll, winner->roundScore, lead);

}

void pointSet(Player* player){
    printf("You rolled %d. First roll set to: %d.\n", player->lastRoll, player->lastRoll);
}

bool rollAgain(){

    while(1){
        char* input = getInput("Roll again? (Y/N): ");

        if(input[0] == 'y' || input[0] == 'Y') return true;
        else if(input[0] == 'n' || input[0] == 'N') return false;
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



