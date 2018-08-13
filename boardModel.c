//
// Created by Alexey Medvecky on 20/07/2018.
//

#include "tic_tac_toe.h"

char field[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

int playerOneTurn = 1;

int turnIsValid = 1;

int gameOn = 1;

int playerOneWin = 0;

int playerTwoWin = 0;

char getField(int fieldNumber) {
    return field[fieldNumber - 1];
}

void setField(int fieldNumber, char value) {
    field[fieldNumber - 1] = value;
}

int isPlayerOneTurn(void) {
    return playerOneTurn;
}

void setPlayerOneTurn(int state) {
    playerOneTurn = state;
}

int isTurnValid(void) {
    return turnIsValid;
}

void setTurnIsValid(int state) {
    turnIsValid = state;
}

int isGameOn(void) {
    return gameOn;
}

void setIsGameOn(int value) {
    gameOn = value;
}

int isPlayerOneWin(void) {
    return playerOneWin;
}

void setPlayerOneWin(int state) {
    playerOneWin = state;
}

int isPlayerTwoWin(void) {
    return playerTwoWin;
}

void setPlayerTwoWin(int state) {
    playerTwoWin = state;
}


