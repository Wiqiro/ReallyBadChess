#include <stdio.h>
#include <stdlib.h>

#include <board.h>
#include <display.h>
#include <moves.h>
#include <save.h>


int main(int argc, char* argv[]) {
    int size = 8;
    srand(time(NULL));

    square** board = CreateBoard(size);
    InitializeBoardRandom(board, size);
    SimplePrint(board, size);

    //printf("\n%d",PawnMoveTest(board, size, 7,7,8,5));
    return EXIT_SUCCESS;
}