#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <game.h>


void Clean();

void InitializeOutputOptions();

void StdinClear();

char MenuInput();

bool GamemodeInput();

int ChessBoardSizeInput();

void MoveInput(square** board, int* startcoords, int* targcoords, int size, bool turn, int kingposx, int kingposy);

char ActionInput();

void PrintPiece(square piece, bool fancyprint);

void BoardPrint(square** board, int size, bool fancyprint);

void SaveNameInput(char* string);

bool QuitConfirmation();

int PrintSaves();

void EasterEgg();



//ALT+219 to get a full character (ASCII 256)
//https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus  board example



#endif