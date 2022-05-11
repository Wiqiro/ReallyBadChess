#include <display.h>



#ifdef _WIN32
    bool OS = 0;
#else
    bool OS = 1;  //assuming that the non-windows systems will handle special characters
#endif

void Clean() {

    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }

}

bool GamemodeInput() {
    char gamemode;

    do {
    printf("\nQuel mode de jeu choisissez-vous ? (B: Really bad chest, C: classic)\n");
    scanf("%c",&gamemode);
    gamemode = toupper(gamemode);

    } while (gamemode != 'B' && gamemode != 'C');

    if (gamemode == 'B') {
        return true;
    } else {
        return false;
    }

}


int ChessBoardSizeInput() {
    char input[100];
    int size=0;
    do {

        if (OS == 0) {
            printf("\nChoisissez %c pr%csent la taille de l'%cchiquer (de 6x6 %c 12x12)\n",133,130,130,133);
        } else {
            printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)\n");
        }


        fflush(stdin);
        scanf("%s",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}