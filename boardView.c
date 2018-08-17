//
// Created by Alexey Medvecky on 20/07/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "tic_tac_toe.h"

void showBoardData(WINDOW *window, int highlight);

void showBoard(void) {
    initNcurses();
    showHeader();
    drawBoard();
    showFooter();
}

void clearScreen(void) {
    system("@cls||clear");
}

void showHeader(void) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *headerWin = newwin(5, 50, yMax / 2 - 12, xMax / 2 - 25); //show on center of screen
    box(headerWin, 0, 0);
    wbkgd(headerWin,COLOR_PAIR(2));
    wmove(headerWin,1,17);
    wprintw(headerWin,"Tic  Tac  Toe");
    wmove(headerWin,2,9);
    wprintw(headerWin,"Player 1 (X)  -  Player 2 (O)");
    refresh();
    wrefresh(headerWin);
}

void drawBoard(void) {
    int i, h;

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *boardWin = newwin(15, 30, yMax / 2 - 7, xMax / 2 - 15); //show on center of screen
    box(boardWin, 0, 0);
    wbkgd(boardWin,COLOR_PAIR(3));

    refresh();
    wrefresh(boardWin);

    for (i = 0; i <= 12; i++) {
//        add shifts from parent window borders
        mvwaddch(boardWin, i + 1, 0 + 5, ACS_VLINE);
        mvwaddch(boardWin, i + 1, 6 + 5, ACS_VLINE);
        mvwaddch(boardWin, i + 1, 12 + 5, ACS_VLINE);
        mvwaddch(boardWin, i + 1, 18 + 5, ACS_VLINE);

        if (i % 4 == 0) {
            for (h = 0; h <= 18; h++) {
                mvwaddch(boardWin, i + 1, h + 5, ACS_HLINE);
            }
        }
    }

    showBoardData(boardWin, 0);
    wmove(boardWin, 3, 8);
    refresh();
    wrefresh(boardWin);

    showBoardData(boardWin, 2);
    refresh();
    wrefresh(boardWin);
}

void showFooter(void) {

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *footerWin = newwin(5, 50, yMax / 2 + 8, xMax / 2 - 25); //show on center of screen
    box(footerWin, 0, 0);
    wbkgd(footerWin,COLOR_PAIR(2));

    refresh();
    wrefresh(footerWin);

   getch();

   endwin();

//    if (isGameOn()) {
//        if (isPlayerOneTurn()) {
//            printf("\nPlayer 1, enter a number or q for exit:  ");
//            handleTurn(getUserInput());
//        } else {
//            printf("\nPlayer 2, enter a number or q for exit:  ");
//            handleTurn(getUserInput());
//        }
//        while (!isTurnValid()) {
//            refreshScreen();
//            printf("\nInvalid move. ");
//            handleTurn(getUserInput());
//        }
//        showBoard();
//    } else {
//        if (isPlayerOneWin()) {
//            printf("\n==>Player 1 win\n");
//        } else if (isPlayerTwoWin()) {
//            printf("\n==>Player 2 win\n");
//        } else {
//            printf("\n==>Nobody win\n");
//        }
//    }
}

int getUserInput(void) {
    char input = getchar();
    if (input != '\n') {
        while (getchar() != '\n'); //remove non valid symbols from input stream
    }
    if (input == 'q') {
        exit(0);
    }
    return input - '0';
}

void refreshScreen(void) {
    clearScreen();
    showHeader();
    drawBoard();
}

void initNcurses(void) {
    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_GREEN,COLOR_BLUE);
    init_pair(3,COLOR_YELLOW,COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    curs_set(0);
}

void showBoardData(WINDOW *window, int highlight) {
    int i = 0;
    int x = 8;
    int y = 3;
    while (i < 10) {
        wmove(window, y, x);
        if (i + 1 == highlight) {
            wattron(window, A_REVERSE);
        }
        mvwaddch(window, y, x, getField(i + 1));
        wattroff(window, A_REVERSE);
        i++;
        x += 6;
        if (i % 3 == 0) {
            x = 8;
            y += 4;
        }
    }
}



