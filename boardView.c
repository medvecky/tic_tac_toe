//
// Created by Alexey Medvecky on 20/07/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "tic_tac_toe.h"

void showBoardData(int highlight);

int getUserInput(WINDOW *footerwin);

void endParty(WINDOW *footerWin);

void showMenu(void);

WINDOW *boardWin;

void showBoard(void) {
    do {
        showHeader();
        drawBoard();
    } while (showFooter() == 1);
    clear();
    initGame();
}

void showHeader(void) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *headerWin = newwin(5, 50, yMax / 2 - 12, xMax / 2 - 25); //show on center of screen
    box(headerWin, 0, 0);
    wbkgd(headerWin, COLOR_PAIR(2));
    wmove(headerWin, 1, 17);
    wattron(headerWin, A_BOLD);
    wprintw(headerWin, "Tic  Tac  Toe");
    wmove(headerWin, 2, 9);
    wprintw(headerWin, "Player 1 (X)  -  Player 2 (O)");
    wattroff(headerWin, A_BOLD);
    refresh();
    wrefresh(headerWin);
}

void drawBoard(void) {
    int i, h;

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    boardWin = newwin(15, 30, yMax / 2 - 7, xMax / 2 - 15); //show on center of screen
    box(boardWin, 0, 0);
    wbkgd(boardWin, COLOR_PAIR(3));

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

    showBoardData(0);
    refresh();
    wrefresh(boardWin);
}

int showFooter(void) {

    int input;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *footerWin = newwin(5, 50, yMax / 2 + 8, xMax / 2 - 25); //show on center of screen
    box(footerWin, 0, 0);
    wbkgd(footerWin, COLOR_PAIR(2));

    if (isGameOn()) {
        if (isPlayerOneTurn()) {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "Player 1, enter a number or use arrow keys:  ");
            wmove(footerWin, 2, 1);
            wprintw(footerWin, "Enter q for exit:  ");
            wattroff(footerWin, A_BOLD);
            refresh();
            wrefresh(footerWin);
            input = getUserInput(footerWin);
            if (input == -1) {
                return -1;
            }
            handleTurn(input);
        } else {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "Player 2, enter a number or use arrow keys:  ");
            wmove(footerWin, 2, 1);
            wprintw(footerWin, "Enter q for exit:  ");
            wattroff(footerWin, A_BOLD);
            refresh();
            wrefresh(footerWin);
            input = getUserInput(footerWin);
            if (input == -1) {
                return -1;
            }
            handleTurn(input);
        }
        while (!isTurnValid()) {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "Invalid move.                                   ");
            wattroff(footerWin, A_BOLD);
            refresh();
            wrefresh(footerWin);
            input = getUserInput(footerWin);
            if (input == -1) {
                return -1;
            }
            handleTurn(input);
        }
        return 1;
    } else {
        if (isPlayerOneWin()) {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "==>Player 1 win");
            wmove(footerWin, 2, 1);
            wprintw(footerWin, "Press any key to continue");
            wattroff(footerWin, A_BOLD);
            wrefresh(footerWin);
            refresh();
            getch();
            endParty(footerWin);
            return -1;

        } else if (isPlayerTwoWin()) {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "==>Player 2 win");
            wmove(footerWin, 2, 1);
            wprintw(footerWin, "Press any key to continue");
            wattroff(footerWin, A_BOLD);
            wrefresh(footerWin);
            refresh();
            getch();
            endParty(footerWin);
            return -1;
        } else {
            wmove(footerWin, 1, 1);
            wattron(footerWin, A_BOLD);
            wprintw(footerWin, "==>Nobody win");
            wmove(footerWin, 2, 1);
            wprintw(footerWin, "Press any key to continue");
            wattroff(footerWin, A_BOLD);
            wrefresh(footerWin);
            refresh();
            getch();
            endParty(footerWin);
            return -1;
        }
    }
}

int getUserInput(WINDOW *footerWin) {
    int highlight = 0;
    keypad(footerWin, true);
    while (1) {
        showBoardData(highlight);
        wrefresh(boardWin);
        refresh();
        int input = wgetch(footerWin);
        switch (input) {
            case KEY_RIGHT :
                highlight++;
                if (highlight > 9) {
                    highlight = 9;
                }
                break;
            case KEY_LEFT:
                highlight--;
                if (highlight < 1) {
                    highlight = 1;
                }
                break;
            case KEY_UP:
                highlight -= 3;
                if (highlight < 1) {
                    highlight = 1;
                }
                break;
            case KEY_DOWN:
                highlight += 3;
                if (highlight > 9) {
                    highlight = 9;
                }
                break;
            default:
                break;
        }
        if (input == 10) {
            break;
        } else if ((char) input == 'q') {
            return -1;
        } else if ((input - '0') > 0 && (input - '0') < 10) {
            return input - '0';
        }
    }
    return highlight;
}

void initNcurses(void) {
    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);
    init_pair(3, COLOR_YELLOW, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    curs_set(0);
}

void showBoardData(int highlight) {
    int i = 0;
    int x = 8;
    int y = 3;
    while (i < 10) {
        wmove(boardWin, y, x);
        if (i + 1 == highlight) {
            wattron(boardWin, A_REVERSE);
        }
        if (getField(i + 1) == 'X') {
            wattron(boardWin, A_BOLD);
            wattron(boardWin, COLOR_PAIR(4));
        }
        if (getField(i + 1) == 'O') {
            wattron(boardWin, A_BOLD);
            wattron(boardWin, COLOR_PAIR(1));
        }
        mvwaddch(boardWin, y, x, getField(i + 1));
        wattroff(boardWin, A_REVERSE);
        wattroff(boardWin, COLOR_PAIR(4));
        wattroff(boardWin, COLOR_PAIR(1));
        wattroff(boardWin, A_BOLD);
        i++;
        x += 6;
        if (i % 3 == 0) {
            x = 8;
            y += 4;
        }
    }
}

void endParty(WINDOW *footerWin) {
    wmove(footerWin, 2, 1);
    wattron(footerWin, A_BOLD);
    wprintw(footerWin, "Press any key to exit");
    wattroff(footerWin, A_BOLD);
    refresh();
    wrefresh(footerWin);
}

void showMenu(void) {
    initGame();
    initNcurses();
    while (1) {
        int choice;
        int highlight = 0;
        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        WINDOW *menuWin = newwin(15, 30, yMax / 2 - 7, xMax / 2 - 15); //show on center of screen
        box(menuWin, 0, 0);
        wbkgd(menuWin, COLOR_PAIR(3));
        refresh();
        wrefresh(menuWin);
        keypad(menuWin, true);
        char choices[2][50] = {"*\tGame against human.", "*\tQuit."};
        while (1) {
            for (int i = 0; i < 2; i++) {
                wattron(menuWin, A_BOLD);
                if (i == highlight) {
                    wattron(menuWin, A_REVERSE);
                }
                mvwprintw(menuWin, i + 1, 1, choices[i]);
                wattroff(menuWin, A_REVERSE);
                wattroff(menuWin, A_BOLD);
            }
            refresh();
            wrefresh(menuWin);
            choice = wgetch(menuWin);
            switch (choice) {
                case KEY_UP :
                    highlight--;
                    if (highlight < 0) {
                        highlight = 0;
                    }
                    break;
                case KEY_DOWN :
                    highlight++;
                    if (highlight > 1) {
                        highlight = 1;
                    }
                    break;
                default:
                    break;
            }
            if (choice == 10) {
                break;
            }
        }
        switch (highlight) {
            case 0 :
                clear();
                showBoard();
                continue;
            case 1:
                endwin();
                exit(0);
        }
    }
}