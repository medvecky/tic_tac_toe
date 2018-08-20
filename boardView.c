//
// Created by Alexey Medvecky on 20/07/2018.
//
#include <stdio.h>
#include <stdlib.h>

#include "tic_tac_toe.h"

void showMenu(void);

void showBoard(void) {
    clearScreen();
    showHeader();
    drawBoard();
    showFooter();
}

void clearScreen(void) {
    system("@cls||clear");
}

void showHeader(void) {
    printf("\n\tTic  Tac  Toe\n\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n");
}

void drawBoard(void) {
    for (int i = 1; i <= 9; i += 3) {
        printf("     |     |     \n");
        printf("  %c  |  %c  |  %c   \n", getField(i), getField(i + 1), getField(i + 2));
        if (i < 5) {
            printf("_____|_____|_____ \n");
        } else {
            printf("     |     |      \n");
        }
    }
}

void showFooter(void) {
    if (isGameOn()) {
        if (isPlayerOneTurn()) {
            printf("\nPlayer 1, enter a number or q for exit:  ");
            handleTurn(getUserInput());
        } else {
            printf("\nPlayer 2, enter a number or q for exit:  ");
            handleTurn(getUserInput());
        }
        while (!isTurnValid()) {
            refreshScreen();
            printf("\nInvalid move. ");
            handleTurn(getUserInput());
        }
        showBoard();
    } else {
        if (isPlayerOneWin()) {
            printf("\n==>Player 1 win\n");
            printf("Press any key to continue.\n");
            getchar();
        } else if (isPlayerTwoWin()) {
            printf("\n==>Player 2 win\n");
            printf("Press any key to continue.\n");
            getchar();
        } else {
            printf("\n==>Nobody win\n");
            printf("Press any key to continue.\n");
            getchar();
        }
    }
}

int getUserInput(void) {
    char input = getchar();
    if (input != '\n') {
        while (getchar() != '\n'); //remove invalid symbols from input stream
    }
    if (input == 'q') {
        showMenu();
    }
    return input - '0';
}

void refreshScreen(void){
    clearScreen();
    showHeader();
    drawBoard();
}

void showMenu(void) {
    int input;
    while(1) {
        clearScreen();
        printf("\n\tTic  Tac  Toe\n\n");
        printf("1. Game against human.\n");
        printf("q. Exit.\n");
        input = getchar();
        switch (input) {
            case '1' :
                while (getchar() != '\n');
                clearScreen();
                showBoard();
                continue;
            case 'q': exit(0);
            default:
                while (getchar() != '\n');
                continue;

        }
    }
}



