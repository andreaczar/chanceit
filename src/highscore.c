#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void writeHighscores(Score *scores) {

    int i;
    FILE * fp;

    //sort scores

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

void displayHighscore() {

    Score* scores;

    scores = readHighscores();

    int i;

    for(i=0; i<NUM_SCORES; i++){
        printf("score: %d, user: %s, Date: %s\n", scores[i].score, scores[i].name, scores[i].date);
    }

    free(scores);

}



void addHighscore(int score, char *name) {

    Score* scores;
    scores = readHighscores();

    scores[9].score = score;
    scores[9].name = name;
    scores[9].date = "JUN/06/2016";

    writeHighscores(scores);

}
