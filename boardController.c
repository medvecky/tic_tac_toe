//
// Created by Alexey Medvecky on 20/07/2018.
//

#include <stdio.h>

#include "tic_tac_toe.h"

void handleTurn(void) {
    int fieldNumber;
    char turnValue;
    scanf("%d", &fieldNumber);
    if (isPlayerOneTurn()) {
        turnValue = 'X';
    } else {
        turnValue = 'O';
    }

    if (checkTurn(fieldNumber)) {
        setField(fieldNumber, turnValue);
        setTurnIsValid(1);
        checkForWin();
        deadHeatCheck();
        if (isPlayerOneTurn()) {
            setPlayerOneTurn(0);
        } else {
            setPlayerOneTurn(1);
        }
    } else {
        setTurnIsValid(0);
    }
}

int checkTurn(int fieldNumber) {
    if (fieldNumber < 1 || fieldNumber > 9) {
        while (getchar() != '\n');
        return 0;
    }
    char value = getField(fieldNumber);
    if (value == 'O' || value == 'X') {
        return 0;
    }

    return 1;
}

int trinityCheck(int field1, int field2, int field3) {
    char value1 = getField(field1);
    char value2 = getField(field2);
    char value3 = getField(field3);

    if (value1 == 'X' && value2 == 'X' && value3 == 'X') {
        setPlayerOneWin(1);
        setIsGameOn(0);
        return 1;
    } else if (value1 == 'O' && value2 == 'O' && value3 == 'O') {
        setPlayerTwoWin(1);
        setIsGameOn(0);
        return 1;
    }
    return 0;
}

void checkForWin(void) {
    if (trinityCheck(1, 2, 3)) {
        return;
    }
    if (trinityCheck(4, 5, 6)) {
        return;
    }
    if (trinityCheck(7, 8, 9)) {
        return;
    }
    if (trinityCheck(1, 4, 7)) {
        return;
    }
    if (trinityCheck(2, 5, 8)) {
        return;
    }
    if (trinityCheck(3, 6, 9)) {
        return;
    }
    if (trinityCheck(1, 5, 9)) {
        return;
    }
    if (trinityCheck(3, 5, 7)) {
        return;
    }
}

void deadHeatCheck(void) {
    for (int i = 1; i <= 9; i++) {
        char value = getField(i);
        if (value != 'X' &&  value != 'O') {
            return;
        }
    }
    setIsGameOn(0);
}


