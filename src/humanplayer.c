#include "game.h"
#include "stdio.h"
#include "roll.h"
/*
 * Play the human turn.
 *
 * this should probably talk to the ui.
 *
 * Should probably present some kind of output to the player (roll infos, probabilities, etc),
 * accept input then return the roll (or the skip)
 */
int playHumanTurn(Game *game){
    // talk to ui to see if user wants to roll
    // if the user wants to roll, return a new roll
    // otherwise return zero, or whatever.

    return roll(2);
}