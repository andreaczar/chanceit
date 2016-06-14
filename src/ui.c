#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui.h"
#include "input.h"
#include "highscore.h"
#include <unistd.h>

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
    printf("*\t %-48s*\n", "[Y]-Roll Again.\t[N]-End Round.");
    printf("*\t %-54s*\n", "[P]-View Probability.\t[Q]-Quit Game.");
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
        printSide();
        printBar();
        rounds = getInt("");
    }
    return rounds;
}
// Added -- Displays the start of the game and the number of rounds in the game
void startGame(Game *game){
    printf("\nInitializing Game:  %d Rounds.\n\n", game->totalRounds);
}

// added -- Displays player name
void displayPlayer(Player* current, Player* opponent){
    printf("\t\t   %12s's Round\t\t       \n\n", current->name);
    printf("\t\t     Running Game Score: %d-%d\t\t       \n\n", current->totalScore, opponent->totalScore);
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
    printf("Determining First Player:\n\n");
    printf("\t%s\t rolled: %d. \n", currentPlayer->name, currentPlayer->lastRoll);
    printf("\t%s\t rolled: %d. \n\n", otherPlayer->name, otherPlayer->lastRoll);
    printf("\t>>>>> %s goes first <<<<<\n\n", currentPlayer->name);
}


// added to humanplayer.c
void displayProbability(Player* player, double probability){
    printf("The probability of rolling %d again is: %.2f%%\n", player->point, probability);
}

//added -- lose rounds message
void loseRound(Player* player){
    printf("%s rolled %2d.  Round Score: %d.\n", player->name, player->lastRoll, player->roundScore);
    printf("\nTurn over! \nYou rolled your 'First Roll': %d.\n", player->point);
	sleep(4);
}
//added displays round over game summary for current player
void roundOver(Player* player){

    printf("\n\n\t _________________Round Summary__________________\n");
    printf("\t| %-46s|\n", "");
    printf("\t|    %-12s  Total Round Score = %-4d     |\n", player->name, player->roundScore);
    printf("\t|    %-12s  Total Game Score = %-4d      |\n", player->name, player->totalScore);
    printf("\t|_______________________________________________|\n\n\n");
}

//added -- displays player name, last roll, and updated round score
void roundScore(Player* player){
    printf("%s rolled %2d.  Round Score: %d.\n", player->name, player->lastRoll, player->roundScore);
}


// n playRound
void pointSet(Player* player){
    printf("%s rolled %2d.  Point Set: %d.\n", player->name, player->point, player->point);
}

/// Added to humanplayer.c
char rollAgain(){

    while(1){

        char* input = getInput("Roll again? (Y/N/P/Q)\n");

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
    printf("Congratulations!! %s, you WON with %d points!\n", player->name, player->totalScore);
}

void returnToMainMenu(){
    printf("Press any key to return to the Main Menu.\n");
    getchar();
}

// added -- displays score for both players at the end of the game
void gameSummary(Player* p1, Player* p2){
    printf("\n\t __________________Game Summary__________________\n");
    printf("\t| %-46s|\n", "");
    printf("\t|     Player 1: %-12s Total Score = %-4d |\n", p1->name, p1->totalScore);
    printf("\t|     Player 2: %-12s Total Score = %-4d |\n", p2->name, p2->totalScore);
    printf("\t|_______________________________________________|\n\n\n");
    }

// Get player names
char* getPlayerName(){
    char* nameInput = getInput("\nPlayer enter your name: ");
    return nameInput;
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
    printf("*\t %-4s\t%-22s %-5s  %-17s *\n", "Rank", "Name", "Score", "Date");
    printSide();

    int i;
    for(i = 0; i < 10; i++){
        printf("*\t %3d:\t%-22s %5d  %-17s *\n", i+1, scores[i].name, scores[i].score, scores[i].date);
    }
    printSide();
    printBar();
}

void highScore(){
    printf("You have a high score!\n");
}


void gameOver() {
    printf("\n\t  __                       __                \n"
                   "\t /                        /  |               \n"
                   "\t( __  ___  _ _  ___      (   |      ___  ___ \n"
                   "\t|   )|   )| | )|___)     |   ) \\  )|___)|   )\n"
                   "\t|__/ |__/||  / |__       |__/   \\/ |__  |    \n"
                   "\t______________________________________________\n"
                   "\t                                             \n");
}