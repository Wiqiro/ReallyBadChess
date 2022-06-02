#include <interface.h>



#ifdef _WIN32
    bool OS = 0;
    #include <windows.h>
#else
    bool OS = 1;  //assuming that the non-windows systems are linux-based
#endif

void Clean() {
    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }
}

void InitializeOutputOptions() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
}

void StdinClear() {
    char buffer;
    while ((buffer = getchar()) != '\n');
}

char MenuInput() {

    char buffer;
    do {
        StdinClear();
        printf("\nChoisissez une option ! (N: nouvelle partie  I: importer une sauvegarde  O: options  Q: quitter)  ");
        buffer = toupper(getchar());
    } while (buffer != 'N' && buffer != 'I' && buffer != 'Q' && buffer != 'O');
    return buffer;
}

bool GamemodeInput() {
    char gamemode;
    do {
        StdinClear();
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
        printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)\n");

        StdinClear();
        scanf("%s",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}

void MoveInput(square** board, int* startcoords, int* targcoords, int size, bool turn, int kingposx, int kingposy) {

    bool okmove = false;

    char input[3];

    do {
        do {
            printf("\nEntrez les coordonnées de la pièce que vous souhaitez bouger: ");
            StdinClear();
            scanf("%3s", input);

            startcoords[0] = toupper(input[0]) - 'A';
            if (input[2] == '\0') {
                startcoords[1] = size - input[1] + '0';
            } else {
                startcoords[1] = size - input[2] + '0' - 10;
            }
            if (startcoords[0] < 0 || startcoords[0] >= size || startcoords[1] < 0 || startcoords[1] >= size) {
                printf("\nCette pièce ne fait pas partie de l'échiquier !");                            
            } else if (board[startcoords[0]][startcoords[1]].color != turn) {
                printf("\nCe n'est pas votre tour");
            } else {
                okmove = true;
            }

        } while (!okmove);
        okmove = true;
        StdinClear();
        printf("\nEntrez les coordonnées de la case où vous souhaitez bouger la pièce: ");
        scanf("%3s", input);
        
        targcoords[0] = toupper(input[0]) - 'A';
        if (input[2] == '\0') {
            targcoords[1] = size - input[1] + '0';
        } else {
            targcoords[1] = size - input[2] + '0' - 10;
        }
        
        if (MoveTest(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1]) == false) {
            printf("\nCe mouvement est interdit !");
            okmove = false;
        } else if (board[targcoords[0]][targcoords[1]].color == turn && board[targcoords[0]][targcoords[1]].type != empty) {
            printf("\nVous ne pouvez pas prendre vos propres pièces !");
            okmove = false;
        } else if (board[startcoords[0]][startcoords[1]].type == king && CheckTest(board, size, targcoords[0], targcoords[1], board[kingposx][kingposy].color) == true) {
            printf("\nVous ne pouvez pas mettre votre roi en échec !");
            okmove = false;
        } /* else {
            printf("kqjsksdg");
            if (CheckTest(board, size, kingposx, kingposy) == true) {
                printf("\nVous ne pouvez pas mettre votre roi en échec !");
                okmove = false;
            }
        } */
    } while (!okmove);

}

char ActionInput() {

    char buffer;
    do {
        StdinClear();
        printf("Que voulez-vous faire ? (J: jouer  S: sauvegarder  X: abandonner)  ");
        buffer = toupper(getchar());


    } while (buffer != 'J' && buffer != 'S' && buffer != 'X');
    return buffer;
}


void PrintPiece(square piece, bool fancyprint) {

    if (fancyprint) {
        if (piece.color == black) {
            switch (piece.type) {
            case pawn:
                printf("♙");
                break;
            case bishop:
                printf("♗");
                break;
            case knight:
                printf("♘");
                break;
            case rook:
                printf("♖");
                break;
            case queen:
                printf("♕");
                break;
            case king:
                printf("♔");
                break;
            default:
                printf(" ");
                break;
            }
        } else {
            switch (piece.type) {
            case pawn:
                printf("♟");
                break;
            case bishop:
                printf("♝");
                break;
            case knight:
                printf("♞");
                break;
            case rook:
                printf("♜");
                break;
            case queen:
                printf("♛");
                break;
            case king:
                printf("♚");
                break;
                    
            default:
                printf(" ");
                break;
            }
        }
        printf(" ");
    } else {
        if (piece.type != empty) {
            switch (piece.type) {
            case pawn:
                printf("P");
                break;
            case bishop:
                printf("F");
                break;
            case knight:
                printf("C");
                break;
            case rook:
                printf("T");
                break;
            case queen:
                printf("Q");
                break;
            case king:
                printf("R");
                break;
            default:
                break;
            }
            if (piece.color == white) {
                printf("B");
            } else {
                printf("N");
            }
        } else {
            printf("  ");
        }
    }
}

void BoardPrint(square** board, int size, bool fancyprint) {

    
    printf("\n ╭");

    for (int x=0; x<size; x++) {
        printf("────┬");
    }
    printf("────╮\n │");

    for (int y=0; y<size-1; y++) {
        printf(" ");
        if (size < 10 || y > (size-10)) {
                printf("0");
        }
        printf("%d", size-y);
        for (int x=0; x<size; x++) {
            printf(" │ ");
            PrintPiece(board[x][y], fancyprint);
        }
        
        printf(" │ \n ├");
        for (int x=0; x<size; x++) {
        printf("────┼");
        }
        printf("────┤\n │");
    }

    printf(" 01");
    for (int x=0; x<size; x++) {
        printf(" │ ");
        PrintPiece(board[x][size-1], fancyprint);
 
    }

    printf(" │\n ╰");
    for (int x=0; x<size; x++) {
        printf("────┼");
    }
    printf("────┤\n      │");

    for (int x=0; x<size; x++) {
        printf(" %c  │",x+'A');
    }
    printf("  \n      ╰");
    for (int x=0; x<size-1; x++) {
        printf("────┴");
    }
    printf("────╯\n");


}

void SaveNameInput(char* string) {

    char buffer[20];

    StdinClear();
    printf("Sous quel nom voulez-vous sauvegarder votre partie ?  ");
    fgets(buffer, 20, stdin);
    strncpy(string, buffer, strlen(buffer)-1);
}

bool QuitConfirmation() {
    char buffer;
    do {
        printf("Voulez-vous vraiment quitter ? (O: oui N: non) \n");
        StdinClear();
        buffer = toupper(getchar());
    } while (buffer != 'O' && buffer != 'N');
    if (buffer == 'O') {
        return true;
    } else {
        return false;
    }
}

int PrintSaves() {

    Clean();
    printf("Gestion des sauvegardes\n");

    char buffer[3][50];
    int i = 1;
    long long int time;
    FILE* index = fopen("saves.txt","r");
    if (index != NULL) {
        while (fscanf(index, "%50s\t%50s\t%50s\n", buffer[0], buffer[1], buffer[2]) != EOF) {
            time = strtoll(buffer[2], NULL, 10);

            printf("%d: %s\t\t(%sx%s)  \t%lld\n", i, buffer[0], buffer[1], buffer[1], time);
            i++;
        }
    }
    fclose(index);

    if (i == 1) {
        printf("Aucune sauvegarde n'a été trouvée !\n"); 
        return -1;
    } else {
        char input[10];
        int savenumber;
        do {
            StdinClear();

            printf("\nEntrez le numéro de la sauvegarde que vous souhaitez importer  ");
            fgets(input, 3, stdin);
            savenumber = strtol(input, NULL, 10);
        } while (savenumber < 1 || savenumber>= i);
        printf("%d", savenumber);  
        return savenumber;
    }
}

void EasterEgg() {
    Clean();
    printf("                                      ......................................     \n");
    printf("                                      ......................................      \n");
    printf("                                      ......................................      \n");
    printf("                                      ......................................      \n");
     printf("                                            .........................    \n");
     printf("                                            .........................     \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................     \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                            .........................      \n");
     printf("                                      ...................................... \n");
     printf("                                      ......................................   \n");
     printf("                                      ......................................    \n");
     printf("                                      ......................................      \n\n\n\n");

    printf("                                 ............                          .............      \n");
    printf("                              ..................                   .....................    \n");
    printf("                           ........................              .........................   \n");
    printf("                         ...........................           ............................   \n");
    printf("                        .............................         ..............................  \n");
    printf("                       ...............................       ................................   \n");
    printf("                       ................................     ..................................    \n");
    printf("                       .................................   ...................................   \n");
    printf("                       .......................................................................    \n");
    printf("                        .....................................................................     \n");
    printf("                         ...................................................................       \n");
    printf("                          .................................................................       \n");
    printf("                           ..............................................................      \n");
    printf("                             ..........................................................        \n");
    printf("                               ......................................................         \n");
    printf("                                   ...............................................         \n");
    printf("                                      ..........................................        \n");
    printf("                                         ..................................         \n");
    printf("                                             ..........................             \n");
    printf("                                                ....................        \n");
    printf("                                                  ...............       \n");
    printf("                                                     .........          \n");
    printf("                                                       .....            \n");
    printf("                                                        ...         \n");
    printf("                                                         .  \n\n\n\n");

    printf("             ......................................               ......................................................  \n");
    printf("             ......................................               ......................................................  \n");
    printf("             ......................................               ......................................................  \n");
    printf("             ......................................               ......................................................  \n");
    printf("                    .........................                         ..................................................  \n");
    printf("                    .........................                         ..................................................  \n");
    printf("                    .........................                         .......................   \n");
    printf("                    .........................                         .......................  \n");
    printf("                    .........................                         .......................   \n");
    printf("                    .........................                         .......................   \n");
    printf("                    .........................                         .......................  \n");
    printf("                    .........................                         ....................... \n");
    printf("                    .........................                         ....................... \n");
    printf("                    .........................                         .................................\n");
    printf("                    .........................                         .................................\n");
    printf("                    .........................                         .................................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("                    .........................                         .......................\n");
    printf("              ......................................             ..................................\n");
    printf("              ......................................             ..................................\n");
    printf("              ......................................             ..................................\n");
    printf("              ......................................             ..................................\n");

    printf("\nPressez entrer pour quitter");
    StdinClear();
    getchar();
}