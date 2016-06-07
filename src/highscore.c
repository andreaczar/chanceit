#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#include "highscore.h"
#include "ui.h"

#define HSFILENAME "highscores.csv"
#define NUM_SCORES 10


// Read the high scores from the file
Score* readHighscores() {

    char* line = NULL;          /* pointer to use with getline */
    ssize_t read = 0;           /* characters read by getline ()    */
    size_t n = 0;               /* number of bytes to allocate      */
    char *sp = NULL;            /* start pointer for parsing line   */
    char *p = NULL;             /* end pointer to use parsing line  */
    int field = 0;              /* counter for field in line         */
    int it = 0;
    int cnt = 0;
    Score* scores = NULL;
    FILE *fp;

    fp = fopen(HSFILENAME, "r");

    if (!fp) {
        fprintf(stderr, "Failed to open file for reading\n");
        return;
    }

    scores = malloc(NUM_SCORES * sizeof(Score));

    while ((read = getline(&line, &n, fp)) != -1) {    /* read each line in input file */

        sp = p = line;      /* set start ptr and ptr to beginning of line */
        field = 0;          /* set/reset field to 0 */

        Score* score = malloc(sizeof(Score));

        while (*p) {
            if (*p == ','){

                *p = 0;     /* set as null-term char (temp) */

                if (field == 0){
                    score->score = atoi(sp);
                }
                if (field == 1) {
                    score->name = strdup(sp); /*allocate new string for name and save to score */
                }

                *p = ',';   /* replace with original ','    */
                sp = p + 1; /* set new start ptr start pos  */
                field++;    /* update field count           */
            }
            p++;            /* increment pointer p          */
        }

        char* date = strdup(sp);

        date[strlen(date)-1] = '\0'; // strip newline character and replace will null terminator

        score->date = date;

        scores[cnt] = *score;
        cnt++;
    }

    fclose(fp);            /* close file stream            */

    if (line)               /* free memory allocated by getline     */
        free(line);

    return scores;

}

int compareScores(const void *a, const void *b){

    // cast pointers to dynamic types to pointers to Score structs
    Score* score1 = (Score*)a;
    Score* score2 = (Score*)b;

    if(score1->score < score2->score){
        return 1;
    } else if(score1->score > score2->score){
        return -1;
    } else {
        return 0;
    }
}


void writeHighscores(Score* scores) {

    int i;
    FILE * fp;

    //sort scores
    qsort(scores, NUM_SCORES, sizeof(Score), compareScores);

    fp = fopen (HSFILENAME, "w+");

    for(i = 0; i < NUM_SCORES; i++){
        fprintf(fp, "%d,%s,%s\n", scores[i].score, scores[i].name, scores[i].date);
    }
    fclose(fp);


}

// Setup empty high score table
void initHighscores(){

    int i;
    Score* initialScores;

    if(access(HSFILENAME, F_OK) != -1){
        return;
    }


    initialScores = malloc(NUM_SCORES * sizeof(Score));

    for(i = 0; i < NUM_SCORES; i++){
        initialScores[i].name = "Empty";
        initialScores[i].date = "---/--/----";
        initialScores[i].score = 0;
    }

    writeHighscores(initialScores);
    free(initialScores);
}

void displayHighscores() {

    Score* scores;

    scores = readHighscores();

    highScoreTable(scores);

    free(scores);

}

bool isHighscore(int score){
    Score* scores;
    scores = readHighscores();

    if(score >= scores[9].score){
        return true;
    }
    return false;
}


void addHighscore(int score, char *name) {

    char dateString[12];
    struct tm *info;
    time_t rawtime;

    time(&rawtime);
    info = localtime(&rawtime);

    strftime(dateString, 12, "%b/%d/%Y", info);

    Score* scores;
    scores = readHighscores();

    scores[9].score = score;
    scores[9].name = name;
    scores[9].date = dateString;
//    scores[9].date = "JUN/06/2016";

    writeHighscores(scores);

}