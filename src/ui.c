#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui.h"
#include "input.h"
#include "prob.h"
#include "highscore.h"

void printBar(){
    printf("*****************************************************************\n");
}

//print stars on both sides of empty line
void printSide(){
    printf("*\t %-55s*\n", "");
}
//added
int displayMenu(){
    printf("\n\n\n");
    printBar();
    printf("*\t   _____ _                          _____ _   \t\t*\n"
           "*\t  / ____| |                        |_   _| |  \t\t*\n"
           "*\t | |    | |__   __ _ _ __   ___ ___  | | | |_ \t\t*\n"
           "*\t | |    | '_ \\ / _` | '_ \\ / __/ _ \\ | | | __|\t\t*\n"
           "*\t | |____| | | | (_| | | | | (_|  __/_| |_| |_ \t\t*\n"
           "*\t  \\_____|_| |_|\\__,_|_| |_|\\___\\___|_____|\\__|\t\t*\n"
           "*\t                                              \t\t*\n"
           "*\t                                              \t\t*\n");
    printBar();
    printf("*\t %-55s*\n", "MAIN MENU");
    printSide();
    printf("*\t %-55s*\n", "Enter a number to select an action:");
    printSide();
    printf("*\t %-55s*\n", "1 - Play Single Player vs AI");
    printf("*\t %-55s*\n", "2 - Play 2-Player on the same computer");
    printf("*\t %-55s*\n", "3 - Play Single Player vs Network Opponent");
    printf("*\t %-55s*\n", "4 - Play AI vs Network Opponent");
    printf("*\t %-55s*\n", "5 - View High Scores");
    printf("*\t %-55s*\n", "6 - Exit Game");
    printSide();
    printSide();
    printf("*\t %-55s*\n", "Legend");
    printf("*\t %-48s*\n", "[Y]-roll again.\t[N]-end the round.");
    printf("*\t %-54s*\n", "[P]-view probability.\t[Q]- quit game)");
    printSide();
    printBar();

    return getInt("\n");
}
//added
int amtRounds(){

    int rounds = 0;

    while (rounds < 1 || rounds > 20) {
        printBar();
        printSide();
        printf("*\t %-55s*\n", "Enter the number of rounds (20 is the max):");
//        printf("\tEnter the number of rounds (20 is the max):\n\n");
        printSide();
        printBar();
        rounds = getInt("");
    }

    return rounds;
}
// Added -- Displays the start of the game and the number of rounds in the game
void startGame(Game *game){
    printf("Starting Game:  %d rounds.\n\n", game->totalRounds);
}
// added -- Displays player name
void displayPlayer(Player* player){
    printf("**Player %s's round**\n\n", player->name);
}

//added -- displays round number
void startRound(Game* game) {

    printBar();
    printSide();
    printf("*\t START, Round %2d of %-2d (Q to Quit) %21s*\n", game->roundNumber, game->totalRounds, "");
    printSide();
    printBar();
    printf("\n");
}

// added Determines first player
void firstPlayer(Player* currentPlayer, Player* otherPlayer){
    printf("%s\t rolled: %d. \n", currentPlayer->name, currentPlayer->lastRoll);
    printf("%s\t rolled: %d. \n\n", otherPlayer->name, otherPlayer->lastRoll);
    printf("**%s goes first.**\n\n", currentPlayer->name);
}


// Needs to be added to humanplayer.c

//void displayProbability(Player* player, int probability){
//
//    printf("The probability of rolling %d again is: %d%%\n", roll, probability);
//}

//added -- lose rounds message
void loseRound(Player* player){
    printf("%s rolled %d. \tRound Score: %d.\n", player->name, player->lastRoll, player->roundScore);
    printf("\nTurn over! \nYou rolled your 'First Roll': %d.\n", player->point);
}
//added displays round over game summary for current player
void roundOver(Player* player){


    printf("\n\n\t _________________Round Summary__________________\n");
    printf("\t| %-46s|\n", "");
    printf("\t|     %12s Total Round Score = %-4d     |\n", player->name, player->roundScore);
    printf("\t|     %12s Total Game Score = %-4d      |\n", player->name, player->totalScore);
    printf("\t| %-46s|\n", "");
    printf("\t|_______________________________________________|\n\n\n");
}

//added -- displays player name, last roll, and updated round score
void roundScore(Player* player){
    printf("%s rolled %d. \tRound Score: %d.\n", player->name, player->lastRoll, player->roundScore);
}


// MUST ADD: Add in playRound
void pointSet(Player* player){
    printf("%s rolled %d. \tPoint Set: %d.\n", player->name, player->point, player->point);
}

/// Added to humanplayer.c
char rollAgain(){

    while(1){


        printf("Roll again? (Y/N/P/Q)\n");

        char* input = getInput(" ");

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
    printf("%s score is: %d. \tYOU WIN!\n\n", player->name, player->totalScore);
}
// added -- displays score for both players at the end of the game
void gameSummary(Player* p1, Player* p2){

    printf("\n\n============== Game Summary =============\n\n");
    printf("Player 1: %s\t Total Score: %d\n", p1->name, p1->totalScore);
    printf("Player 2: %s\t Total Score: %d\n", p2->name, p2->totalScore);
    printf("=============================================\n\n");

}

// **Not added yet
void highScore(){
    printBar();
    printf("Congratulations, you have a high score!\nPlease enter your name: \n");
    printBar();
    char* input = getInput(" ");
}
// ** Not added
bool playAgain(){

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

void highScoreTable(Score* scores){
    printf("\n\n");
    printBar();
    printSide();
    printf("*     _    _ _       _        _____                         \t*\n"
           "*    | |  | (_)     | |      / ____|                        \t*\n"
           "*    | |__| |_  __ _| |__   | (___   ___ ___  _ __ ___  ___ \t*\n"
           "*    |  __  | |/ _` | '_ \\   \\___ \\ / __/ _ \\| '__/ _ \\/ __|\t*\n"
           "*    | |  | | | (_| | | | |  ____) | (_| (_) | | |  __/\\__ \\\t*\n"
           "*    |_|  |_|_|\\__, |_| |_| |_____/ \\___\\___/|_|  \\___||___/\t*\n"
           "*               __/ |                                       \t*\n"
           "*              |___/                                        \t*\n");
    printSide();
    printBar();
    printSide();

    //Just for fun Edit later
    printf("*\t %-4s\t%-28s %-5s  %-11s *\n", "Rank", "Name", "Score", "Date");
    printSide();
    printf("*\t %-4s\t%-28s %-5s  %-11s *\n", "1:", "asdf", "klll", "asbbcc");
    printf("*\t %-4s\t%-28s %-5s  %-11s *\n", "10:", "asdf", "klll", "asbbcc");

}