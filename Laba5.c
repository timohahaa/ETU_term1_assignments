#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define BACKSPACE 8
#define TAB 9

unsigned char playfield[29][29] = {{0}};
int length = 3, height = 3;
int num = 1;
int winExes = 3, winZeroes = 3;
int ptrI = -1, ptrJ = -1; //курсор
int count = 0; //считает заполненное место на поле, как только все место заполнено - игра заканчивается ничьей
// также считает, чей сейчас ход

//заполнение поля (дизайн)
void fill_playfield () {
    // ЧТОБЫ НИЧЕГО НЕ СЛОМАЛОСЬ (не удалять цикл...)
    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 29; j++) {
            playfield[i][j] = 32;
        }
    }
    //не удалять цикл выше, серьезно!
    int i, j, k;
    int AMOGUS = (length > height) ? length : height;
    j = 0;
    for (i = 0; i < 2 * AMOGUS + 1; i++) {
        for (k = 0; k < 2 * AMOGUS + 1; k += 2) {
            playfield[i][j + k] = 124;
        }
    }
    i = 0;
    for (j = 0; j < 2 * AMOGUS + 1; j++) {
        for (k = 0; k < 2 * AMOGUS + 1; k += 2) {
            if (playfield[i + k][j] != 124) {
                playfield[i + k][j] = 45;
            } else {playfield[i + k][j] = 249;}
        }
    }

}
//вывод игрового поля в консоль
void draw_playfield() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,j;
    for (i = 0; i < 2 * height + 1; i++) {
        for (j = 0; j < 2 * length + 1; j++) {
            if (playfield[i][j] == 'X') {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf(" %c", playfield[i][j]);
            } else if (playfield[i][j] == 'O') {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf(" %c", playfield[i][j]);
            } else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf(" %c", playfield[i][j]);
            }
            if (j == 2 * length) {printf("\n");}
        }
    }
}
//меню
void logo() { //много строк, зато красиво!!!
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("====================> ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    printf("С");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("у");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("п");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("е");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
    printf("р");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf(" Крестики");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("-");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("нолики");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf(" <====================\n");
}
void menu() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    logo();
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("Выберите номер команды и нажмите ENTER\n");
    printf("1) Ввести длинну поля:  %d", length);
    if (num == 1) {printf("     <<<");}
    printf("\n");
    printf("2) Ввести ширину поля:  %d", height);
    if (num == 2) {printf("     <<<");}
    printf("\n");
    printf("3) Ввести условие победы крестиков:  ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%d", winExes);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (num == 3) {printf("     <<<");}
    printf("\n");
    printf("4) Ввести условие победы ноликов:  ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("%d", winZeroes);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (num == 4) {printf("     <<<");}
    printf("\n");
    printf("5) Начать игру");
    if (num == 5) {printf("     <<<");}
    printf("\n");
    printf("6) Сбросить параметры игры");
    if (num == 6) {printf("     <<<");}
    printf("\n");
    printf("7) Выход");
    if (num == 7) {printf("     <<<");}
    printf("\n");
    printf("=================================================================\n");
}
//ввод числа с клавиатуры
int input_number() {
    int value = 0;
    int count_symbols, value_helper, get_number_key;
    int leave_function = 0;
    int number = 0;
    system("cls");
    while (leave_function != 1) {
        count_symbols = 0;
        value_helper = value;
        while (value_helper != 0) {
            value_helper /= 10;
            count_symbols++;
        }
        if (count_symbols < 2) {
            printf("Введите число от 2 до 14\n");
            printf("==================================================\n");
            printf("%d\n", value);
            printf("==================================================\n");
            if (value > 1) {printf("Для подтверждения выбранного числа нажмите ENTER\n");}
            get_number_key = getch();
            switch (get_number_key) {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '0':
                    number = get_number_key - 48;
                    value = value * 10 + number;
                    system("cls");
                    break;
                case BACKSPACE:
                    value /= 10;
                    system("cls");
                    break;
                case ENTER:
                    if (value > 1) {leave_function = 1;} else {system("cls");}
                    break;
                default:
                    system("cls");
                    break;
            }
        } else if (count_symbols == 2) {
            printf("Введите число от 2 до 14\n");
            printf("==================================================\n");
            printf("%d\n", value);
            printf("==================================================\n");
            if (value < 15) {printf("Для подтверждения выбранного числа нажмите ENTER\n");}
            get_number_key = getch();
            switch (get_number_key) {
                case BACKSPACE:
                    value /= 10;
                    system("cls");
                    break;
                case ENTER:
                    if (value < 15) {leave_function = 1;} else {system("cls");}
                    break;
                default:
                    system("cls");
                    break;
            }
        }
    }
    return(value);
}
//проверка победы
_Bool IsThereAWin() {
    _Bool WinOrNah;
    int vertical = 1, horizontal = 1, MainDiagonal = 1, SecondaryDiagonal = 1;
    int i,j;
    if (count % 2 == 0) { //проверяем, выиграли ли крестики
        //вертикаль вниз
        i = ptrI + 2;
        while ((playfield[i][ptrJ] == 'X') && (playfield[i - 2][ptrJ] == 'X') && (i != 2 * height + 1)) {
            vertical++;
            i += 2;
        }
        //вертикаль вверх
        i = ptrI - 2;
        while ((playfield[i][ptrJ] == 'X') && (playfield[i + 2][ptrJ] == 'X') && (i != -1)) {
            vertical++;
            i -= 2;
        }
        //горизонталь вправо
        j = ptrJ + 2;
        while ((playfield[ptrI][j] == 'X') && (playfield[ptrI][j - 2] == 'X') && (j != 2 * length + 1)) {
            horizontal++;
            j += 2;
        }
        //горизонталь влево
        j = ptrJ - 2;
        while ((playfield[ptrI][j] == 'X') && (playfield[ptrI][j + 2] == 'X') && (j != -1)) {
            horizontal++;
            j -= 2;
        }
        //ПОБОЧНАЯ ДИАГОНАЛЬ
        //диагональ вверх вправо
        i = ptrI - 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'X') && (playfield[i + 2][j - 2] == 'X') && (i != -1) && (j != 2 * length + 1)) {
            SecondaryDiagonal++;
            i -= 2;
            j += 2;
        }
        //диагональ вниз влево
        i = ptrI + 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'X') && (playfield[i - 2][j + 2] == 'X') && (i != 2 * height + 1) && (j != -1)) {
            SecondaryDiagonal++;
            i += 2;
            j -= 2;
        }
        //ГЛАВНАЯ ДИАГОНАЛЬ
        //диагональ вверх влево
        i = ptrI - 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'X') && (playfield[i + 2][j + 2] == 'X') && (i != -1) && (j != -1)) {
            MainDiagonal++;
            i -= 2;
            j -= 2;
        }
        //диагональ вниз вправо
        i = ptrI + 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'X') && (playfield[i - 2][j - 2] == 'X') && (i != 2 * height + 1) && (j != 2 * length + 1)) {
            MainDiagonal++;
            i += 2;
            j += 2;
        }
        WinOrNah = (vertical >=  winExes) || (horizontal >= winExes) || (MainDiagonal >= winExes) || (SecondaryDiagonal >= winExes);
    } else { //проверяем, выиграли ли нолики
        //вертикаль вниз
        i = ptrI + 2;
        while ((playfield[i][ptrJ] == 'O') && (playfield[i - 2][ptrJ] == 'O') && (i != 2 * height + 1)) {
            vertical++;
            i += 2;
        }
        //вертикаль вверх
        i = ptrI - 2;
        while ((playfield[i][ptrJ] == 'O') && (playfield[i + 2][ptrJ] == 'O') && (i != -1)) {
            vertical++;
            i -= 2;
        }
        //горизонталь вправо
        j = ptrJ + 2;
        while ((playfield[ptrI][j] == 'O') && (playfield[ptrI][j - 2] == 'O') && (j != 2 * length + 1)) {
            horizontal++;
            j += 2;
        }
        //горизонталь влево
        j = ptrJ - 2;
        while ((playfield[ptrI][j] == 'O') && (playfield[ptrI][j + 2] == 'O') && (j != -1)) {
            horizontal++;
            j -= 2;
        }
        //ПОБОЧНАЯ ДИАГОНАЛЬ
        //диагональ вверх вправо
        i = ptrI - 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'O') && (playfield[i + 2][j - 2] == 'O') && (i != -1) && (j != 2 * length + 1)) {
            SecondaryDiagonal++;
            i -= 2;
            j += 2;
        }
        //диагональ вниз влево
        i = ptrI + 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'O') && (playfield[i - 2][j + 2] == 'O') && (i != 2 * height + 1) && (j != -1)) {
            SecondaryDiagonal++;
            i += 2;
            j -= 2;
        }
        //ГЛАВНАЯ ДИАГОНАЛЬ
        //диагональ вверх влево
        i = ptrI - 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'O') && (playfield[i + 2][j + 2] == 'O') && (i != -1) && (j != -1)) {
            MainDiagonal++;
            i -= 2;
            j -= 2;
        }
        //диагональ вниз вправо
        i = ptrI + 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'O') && (playfield[i - 2][j - 2] == 'O') && (i != 2 * height + 1) && (j != 2 * length + 1)) {
            MainDiagonal++;
            i += 2;
            j += 2;
        }
        WinOrNah = (vertical >=  winZeroes) || (horizontal >= winZeroes) || (MainDiagonal >= winZeroes) || (SecondaryDiagonal >= winZeroes);
    }
    return (WinOrNah);
}
//интерфейс во время игры
void gameUI() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("Сейчас ходят: ");
    if (count % 2 == 0) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("КРЕСТИКИ");
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" (%d для победы)", winExes);
    } else {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("НОЛИКИ");
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" (%d для победы)", winZeroes);
    }
    printf("\n");
    draw_playfield();
}
//игра (логика игры и управления)
void gameplay() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ptrI = 1;
    ptrJ = 1;
    playfield[ptrI][ptrJ] = 254;
    count = 0;
    gameUI();
    int get_key;
    int leave_function = 0;
    while (leave_function != 1) {
        get_key = getch();
        switch (get_key) {
            case UP_ARROW:
                playfield[ptrI][ptrJ] = 32;
                ptrI -= 2;
                if ((ptrI <= -1)) {
                    ptrJ += 2;
                    if (ptrJ == 2 * length + 1) {ptrJ = 1;}
                    for (; ptrJ < length * 2 + 1; ptrJ += 2) {
                        for (ptrI = height * 2 - 1; ptrI > -1; ptrI -= 2) {
                            if (playfield[ptrI][ptrJ] == 32) {
                                goto UA_leave; //Господи прости меня за мои страшные грехи
                            }
                        }
                    }
                } else if (playfield[ptrI][ptrJ] != 32) {
                    while (playfield[ptrI][ptrJ] != 32) {
                        ptrI -= 2;
                        if ((ptrI <= -1)) {
                            ptrJ += 2;
                            if (ptrJ == 2 * length + 1) {ptrJ = 1;}
                            for (; ptrJ < length * 2 + 1; ptrJ += 2) {
                                for (ptrI = height * 2 - 1; ptrI > -1; ptrI -= 2) {
                                    if (playfield[ptrI][ptrJ] == 32) {
                                        goto UA_leave; //Господи прости меня за мои страшные грехи
                                    }
                                }
                            }
                        }
                    }
                }
                UA_leave:
                playfield[ptrI][ptrJ] = 254;
                system("cls");
                gameUI();
                break;
            case DOWN_ARROW:
                playfield[ptrI][ptrJ] = 32;
                ptrI += 2;
                if ((ptrI >= height * 2 + 1)) {
                    ptrJ += 2;
                    if (ptrJ == 2 * length + 1) {ptrJ = 1;}
                    for (; ptrJ < 2 * length + 1; ptrJ += 2) {
                        for (ptrI = 1; ptrI < 2 * height + 1; ptrI += 2) {
                            if (playfield[ptrI][ptrJ] == 32) {
                                goto DA_leave; //Господи прости меня за мои страшные грехи
                            }
                        }
                    }
                } else if (playfield[ptrI][ptrJ] != 32) {
                    while (playfield[ptrI][ptrJ] != 32) {
                        ptrI += 2;
                        if ((ptrI >= height * 2 + 1)) {
                            ptrJ += 2;
                            if (ptrJ == 2 * length + 1) {ptrJ = 1;}
                            for (; ptrJ < 2 * length + 1; ptrJ += 2) {
                                for (ptrI = 1; ptrI < 2 * height + 1; ptrI += 2) {
                                    if (playfield[ptrI][ptrJ] == 32) {
                                        goto DA_leave; //Господи прости меня за мои страшные грехи
                                    }
                                }
                            }
                        }
                    }
                }
                DA_leave:
                playfield[ptrI][ptrJ] = 254;
                system("cls");
                gameUI();
                break;
            case LEFT_ARROW:
                playfield[ptrI][ptrJ] = 32;
                ptrJ -= 2;
                if ((ptrJ <= -1)) {
                    ptrI += 2;
                    if (ptrI == 2 * height + 1) {ptrI = 1;}
                    for (; ptrI < height * 2 + 1; ptrI += 2) {
                        for (ptrJ = length * 2 - 1; ptrJ > -1; ptrJ -= 2) {
                            if (playfield[ptrI][ptrJ] == 32) {
                                goto LA_leave; //Господи прости меня за мои страшные грехи
                            }
                        }
                    }
                } else if (playfield[ptrI][ptrJ] != 32) {
                    while (playfield[ptrI][ptrJ] != 32) {
                        ptrJ -= 2;
                        if ((ptrJ <= -1)) {
                            ptrI += 2;
                            if (ptrI == 2 * height + 1) {ptrI = 1;}
                            for (; ptrI < height * 2 + 1; ptrI += 2) {
                                for (ptrJ = length * 2 - 1; ptrJ > -1; ptrJ -= 2) {
                                    if (playfield[ptrI][ptrJ] == 32) {
                                        goto LA_leave; //Господи прости меня за мои страшные грехи
                                    }
                                }
                            }
                        }
                    }
                }
                LA_leave:
                playfield[ptrI][ptrJ] = 254;
                system("cls");
                gameUI();
                break;
            case RIGHT_ARROW:
                playfield[ptrI][ptrJ] = 32;
                ptrJ += 2;
                if ((ptrJ >= length * 2 + 1)) {
                    ptrI += 2;
                    if (ptrI == 2 * height + 1) {ptrI = 1;}
                    for (; ptrI < 2 * height + 1; ptrI += 2) {
                        for (ptrJ = 1; ptrJ < 2 * length + 1; ptrJ += 2) {
                            if (playfield[ptrI][ptrJ] == 32) {
                                goto RA_leave; //Господи прости меня за мои страшные грехи
                            }
                        }
                    }
                } else if (playfield[ptrI][ptrJ] != 32) {
                    while (playfield[ptrI][ptrJ] != 32) {
                        ptrJ += 2;
                        if ((ptrJ >= length * 2 + 1)) {
                            ptrI += 2;
                            if (ptrI == 2 * height + 1) {ptrI = 1;}
                            for (; ptrI < 2 * height + 1; ptrI += 2) {
                                for (ptrJ = 1; ptrJ < 2 * length + 1; ptrJ += 2) {
                                    if (playfield[ptrI][ptrJ] == 32) {
                                        goto RA_leave; //Господи прости меня за мои страшные грехи
                                    }
                                }
                            }
                        }
                    }
                }
                RA_leave:
                playfield[ptrI][ptrJ] = 254;
                system("cls");
                gameUI();
                break;
            case ENTER:
                if (count % 2 == 0) {playfield[ptrI][ptrJ] = 'X';} else {playfield[ptrI][ptrJ] = 'O';}
                if (IsThereAWin()) {
                    system("cls");
                    gameUI();
                    if (count % 2 == 0) {
                        printf("\nпобедили ");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("КРЕСТИКИ\n\n");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("Для выхода в главное меню нажмите TAB");
                    } else {
                        printf("\nпобедили ");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("НОЛИКИ\n\n");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("Для выхода в главное меню нажмите TAB");
                    }
                    while (get_key != TAB) {
                        get_key = getch();
                    }
                    leave_function = 1;
                    goto EXIT;
                }
                count++;
                if (count < length * height) {
                    ptrI += 2;
                    if (ptrI == height * 2 + 1) {ptrI = 1;}
                    while (playfield[ptrI][ptrJ] != 32 ) {
                        ptrI += 2;
                        if (ptrI == height * 2 + 1) {
                            ptrJ += 2;
                            if (ptrJ == length * 2 + 1) {ptrJ = 1;}
                            ptrI = 1;
                        }
                    }
                    playfield[ptrI][ptrJ] = 254;
                    system("cls");
                    gameUI();
                } else if (count == length * height) {
                    system("cls");
                    gameUI();
                    printf("\nНИЧЬЯ\n\nДля выхода в главное меню нажмите TAB");
                    while (get_key != TAB) {
                        get_key = getch();
                    }
                    leave_function = 1;
                }
                EXIT:
                break;
            case TAB:
                leave_function = 1;
                break;
            default:
                break;
        }
    }
}

int main() {
    //HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    int get_key;
    menu();
    while (num != 10) {
        get_key = getch();
        switch (get_key) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                num = get_key - 48;
                system("cls");
                menu();
                break;
            case UP_ARROW:
                num -= 1;
                if (num == 0) {num = 7;}
                system("cls");
                menu();
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 8) {num = 1;}
                system("cls");
                menu();
                break;
            case ENTER:
                switch (num) {
                    case 1:
                        length = input_number();
                        system("cls");
                        menu();
                        break;
                    case 2:
                        height = input_number();
                        system("cls");
                        menu();
                        break;
                    case 3:
                        winExes = input_number();
                        system("cls");
                        menu();
                        break;
                    case 4:
                        winZeroes = input_number();
                        system("cls");
                        menu();
                        break;
                    case 5:
                        fill_playfield();
                        system("cls");
                        gameplay();
                        system("cls");
                        menu();
                        break;
                    case 6:
                        length = height = winZeroes = winExes = 3;
                        system("cls");
                        menu();
                        break;
                    case 7:
                        num = 10;
                        break;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}