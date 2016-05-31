#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

#define true 1
#define false 0


// Discard remaining input on EOF or newline
void discardInput() {
    int tmp;
    do {
        tmp = getc(stdin);
    } while (tmp != EOF && tmp != '\n');
}
// Collect an integer entered on the command line and check if it is valid
int getInt(char *prompt) {

    printf("%s: ", prompt);

    int tmp = 0;
    bool isNegative = false;
    int counter = 0;
    int number = 0;

    while (true) {
        // Check input length, discard and reset if invalid
        if (counter > 9) {
            discardInput();
            counter = 0;
            number = 0;
            isNegative = false;
            continue;
        }

        tmp = getc(stdin);

        // Leave input loop if EOF or newline
        if (tmp == EOF || tmp == '\n') {

            break;

            // If first character is `-` set negative flag
        } else if (counter == 0 && tmp == '-' && !isNegative) {

            isNegative = true;

            // If valid integer character
        } else if('0' <= tmp && tmp <= '9')  {
            //shift number left and add ascii code - 48
            number = number * 10;
            number = number + tmp - '0';
            counter++;

            // otherwise input is invalid, discard and reset
        } else {
            discardInput();
            isNegative = false;
            counter = 0;
            number = 0;
        }
    }
    if (isNegative == true) {
        number = number * (-1);
    }
    return number;
}

long getLong(char *prompt)
{
    long tmp = 0;
    bool isNegative = false;
    int counter = 0;
    long number = 0;

    printf("%s: ", prompt);

    while (true) {
        // Check input length, discard and reset if invalid
        if (counter > 10) {
            discardInput();
            counter = 0;
            number = 0;
            isNegative = false;
            continue;
        }

        tmp = getc(stdin);

        // Leave input loop if EOF or newline
        if (tmp == EOF || tmp == '\n') {

            break;

            // If first character is `-` set negative flag
        } else if (counter == 0 && tmp == '-' && !isNegative) {

            isNegative = true;

            // If valid integer character
        } else if('0' <= tmp && tmp <= '9')  {
            //shift number left and add ascii code - 48
            number = number * 10;
            number = number + tmp - '0';
            counter++;

            // otherwise input is invalid, discard and reset
        } else {
            discardInput();
            isNegative = false;
            counter = 0;
            number = 0;
        }
    }
    if (isNegative == true) {
        number = number * (-1);
    }
    return number;
}

unsigned getUnsigned(char *prompt)
{
    int counter = 0;
    unsigned tmp = 0;
    unsigned number = 0;

    printf("%s: ", prompt);

    while (true) {
        // Check input length, discard and reset if invalid
        if (counter > 9) {
            discardInput();
            counter = 0;
            number = 0;
            continue;
        }

        tmp = getc(stdin);

        // Leave input loop if EOF or newline
        if (tmp == EOF || tmp == '\n') {
            break;

        } if('0' <= tmp && tmp <= '9')  {
            //shift number left and add ascii code - 48
            number = number * 10;
            number = number + tmp - '0';
            counter++;

            // otherwise input is invalid, discard and reset
        } else {
            discardInput();
            counter = 0;
            number = 0;
        }
    }

    return number;
}


//Collects input string and allocates memory one character at a time
char *getInput(char *prompt){

    char *collectedInput, *tmp; // initialize input and tmp string variables
    size_t size = 1;
    int index = 0;
    int ch = EOF; // start with EOF to enter loop

    collectedInput = calloc(size, sizeof(char)); // allocate memory for input

    printf("%s: ", prompt);

    while(ch){
        ch = getc(stdin);

        // if EOF or newline found, we're done, leave loop
        if(ch == EOF || ch == '\n'){
            break;
        }

        // new char for string!  increase string size.
        size++;

        //allocate new array for tmp with new size
        tmp = calloc(size, sizeof(char));


        int i;
        // copy existing input input tmp
        for(i = 0; collectedInput[i] != '\0'; i++){
            tmp[i] = collectedInput[i];
        }

        // copy new character into tmp
        tmp[index] = ch;
        index++;

        // free memory for existing collected input to stop memory leaking
        free(collectedInput);

        // assign new input into collected input array
        collectedInput = tmp;

    }

    return collectedInput;
}