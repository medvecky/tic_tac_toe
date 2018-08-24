//
// Created by Alexey Medvecky on 13/08/2018.
//

#ifndef TIC_TAC_TOE_TIC_TAC_TOE_H
#define TIC_TAC_TOE_TIC_TAC_TOE_H
#endif //TIC_TAC_TOE_TIC_TAC_TOE_H

char getField(int fieldNumber);

void setField(int fieldNumber, char value);

int isPlayerOneTurn(void);

void setPlayerOneTurn(int state);

int isTurnValid(void);

void setTurnIsValid(int state);

int isGameOn(void);

void setIsGameOn(int value);

int isPlayerOneWin(void);

void setPlayerOneWin(int state);

int isPlayerTwoWin(void);

void setPlayerTwoWin(int state);

void handleTurn(int fieldNumber);

int checkTurn(int fieldNumber);

void checkForWin(void);

int trinityCheck(int field1, int field2, int field3);

void deadHeatCheck(void);

void clearScreen(void);

void showHeader(void);

void drawBoard(void);

int showFooter();

int getUserInput(void);

void refreshScreen(void);

void initGame(void);
