#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui.h"
#include "input.h"

//added
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
    printf("1 - Play Single Player vs AI\n");
    printf("2 - Play against an opponent on the same machine\n");
    printf("3 - Play against a network opponent\n");
    printf("4 - Play as AI over a network\n");
    printf("5 - View high scores\n");
    printf("6 - Exit program\n");
    printf("-----------------------------------------------------------\n");

    return getInt("\n");
}
//added
int amtRounds(){

    int rounds = 0;

    while (rounds < 1 || rounds > 20) {
        printf("-----------------------------------------------------------\n");
        printf("Enter the number of rounds (20 is the max):\n");
        rounds = getInt("-----------------------------------------------------------\n");
    }

    return rounds;
}
// Added -- Displays the start of the game and the number of rounds in the game
void startGame(Game *game){
    printf("Starting game.  %d rounds.\n\n", game->totalRounds);
    printf("Rules: [Y] - roll again. [N] - end the round. [P] - view probability, [Q] to quit\n\n");
}
// added -- Displays player name
void displayPlayer(Player* player){
    printf("Player %s's round\n", player->name);
}

//added -- displays round number
void startRound(Game* game) {

    printf("-----------------------------------------------------------\n");
    printf("START, Round %d of %d (Q to quit)\n", game->roundNumber, game->totalRounds);
    printf("-----------------------------------------------------------\n");
}

// added Determines first player
void firstPlayer(Player* currentPlayer, Player* otherPlayer){
    printf("%s rolled %d. ", currentPlayer->name, currentPlayer->lastRoll);
    printf("%s rolled %d. ", otherPlayer->name, otherPlayer->lastRoll);
    printf("%s goes first.\n", currentPlayer->name);
}


//
//    if(player_roll > opponent_roll){
//        printf("You rolled %d. Opponent rolled %d. You go first!\n", player_roll, opponent_roll);
//    } else {
//        printf("You rolled %d. Opponent rolled %d. Opponent goes first!\n", player_roll, opponent_roll);
//    }
//}

// Needs to be added to humanplayer.c

void displayProbability(Player* player, int probability){

    printf("The probability of rolling %d again is: %d%%\n", roll, probability);
}

//added -- lose rounds message
void loseRound(Player* player){
    printf("Turn over. You rolled your 'First Roll' %d.\n", player->point);
}
//added displays round over game summary for current player
void roundOver(Player* player){

    printf("\n\n=== Round Summary ===\n\n");
    printf("Your Total round score = %d\n", player->roundScore);
    printf("Your Total game score = %d\n\n", player->totalScore);
}

//added -- displays player name, last roll, and updated round score
void roundScore(Player* player){
    printf("%s rolled %d. Round Score: %d.\n", player->name, player->lastRoll, player->roundScore);
}


// MUST ADD: Add in playRound
void pointSet(Player* player){
    printf("Player %s - Point set: %d.\n", player->name, player->point);
}

/// Added to humanplayer.c
char rollAgain(){

    while(1){


        printf("Roll again? (Y/N)\n");

        char* input = getInput("Enter your choice: ");

        char firstChar = input[0];

        if(firstChar == 'y' || firstChar == 'Y'){
            return 'y';
        } else if(firstChar == 'n' || firstChar == 'N'){
            return 'n';
        } else if(firstChar == 'q' || firstChar == 'Q'){
            return 'q';
        } else if(firstChar == 'P' || firstChar == 'p'){
            return 'p';
        } else {
            printf("Invalid option.\n");
        }
    }
}
//added -- Displays the winner
void win(Player* player){
    printf("%s score is: %d. YOU WIN!\n", player->name, player->totalScore);
}
// added -- displays score for both players at the end of the game
void gameSummary(Player* p1, Player* p2){

    printf("\n\n==== Game Summary ====\n\n");
    printf("Player 1: %s\t Total Score: %d\n", p1->name, p1->totalScore);
    printf("Player 2: %s\t Total Score: %d\n", p2->name, p2->totalScore);
    printf("\n");

}

// **Not added yet
void highScore(){
    printf("-----------------------------------------------------------\n");
    printf("Congratulations, you have a high score!\nPlease enter your name: \n");
    printf("-----------------------------------------------------------\n");
}
// ** Not added
bool playAgain(){

//    printf("Would you like to play another game? (Y/n)\n");
    char* input = getInput("Would you like to play another game? (Y/n): ");

    if(input[0] == 'y' || input[0] == 'Y') return true;
    else if(input[0] == 'n' || input[0] == 'N') return false;
}

/// *** NOT ADDED
void leadingRound(Player* winner, Player* loser){
    int lead = winner->roundScore + winner->totalScore - loser->roundScore - loser->totalScore;

    printf("You rolled %d. Round Score: %d. You are in the lead by %d!\n",
           winner->lastRoll, winner->roundScore, lead);
}
