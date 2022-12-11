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
int ptrI = -1, ptrJ = -1; //�����
int count = 0; //��⠥� ����������� ���� �� ����, ��� ⮫쪮 �� ���� ��������� - ��� �����稢����� ���쥩
// ⠪�� ��⠥�, 祩 ᥩ�� 室

//���������� ���� (������)
void fill_playfield () {
    // ����� ������ �� ��������� (�� 㤠���� 横�...)
    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 29; j++) {
            playfield[i][j] = 32;
        }
    }
    //�� 㤠���� 横� ���, ��쥧��!
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
//�뢮� ��஢��� ���� � ���᮫�
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
//����
void logo() { //����� ��ப, ��� ��ᨢ�!!!
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("====================> ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    printf("�");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("�");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("�");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("�");
    SetConsoleTextAttribute(hStdOut,  FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
    printf("�");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf(" ���⨪�");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("-");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("������");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf(" <====================\n");
}
void menu() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    logo();
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("�롥�� ����� ������� � ������ ENTER\n");
    printf("1) ����� ������ ����:  %d", length);
    if (num == 1) {printf("     <<<");}
    printf("\n");
    printf("2) ����� �ਭ� ����:  %d", height);
    if (num == 2) {printf("     <<<");}
    printf("\n");
    printf("3) ����� �᫮��� ������ ���⨪��:  ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%d", winExes);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (num == 3) {printf("     <<<");}
    printf("\n");
    printf("4) ����� �᫮��� ������ �������:  ");
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("%d", winZeroes);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (num == 4) {printf("     <<<");}
    printf("\n");
    printf("5) ����� ����");
    if (num == 5) {printf("     <<<");}
    printf("\n");
    printf("6) ������ ��ࠬ���� ����");
    if (num == 6) {printf("     <<<");}
    printf("\n");
    printf("7) ��室");
    if (num == 7) {printf("     <<<");}
    printf("\n");
    printf("=================================================================\n");
}
//���� �᫠ � ����������
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
            printf("������ �᫮ �� 2 �� 14\n");
            printf("==================================================\n");
            printf("%d\n", value);
            printf("==================================================\n");
            if (value > 1) {printf("��� ���⢥ত���� ��࠭���� �᫠ ������ ENTER\n");}
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
            printf("������ �᫮ �� 2 �� 14\n");
            printf("==================================================\n");
            printf("%d\n", value);
            printf("==================================================\n");
            if (value < 15) {printf("��� ���⢥ত���� ��࠭���� �᫠ ������ ENTER\n");}
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
//�஢�ઠ ������
_Bool IsThereAWin() {
    _Bool WinOrNah;
    int vertical = 1, horizontal = 1, MainDiagonal = 1, SecondaryDiagonal = 1;
    int i,j;
    if (count % 2 == 0) { //�஢��塞, �먣ࠫ� �� ���⨪�
        //���⨪��� ����
        i = ptrI + 2;
        while ((playfield[i][ptrJ] == 'X') && (playfield[i - 2][ptrJ] == 'X') && (i != 2 * height + 1)) {
            vertical++;
            i += 2;
        }
        //���⨪��� �����
        i = ptrI - 2;
        while ((playfield[i][ptrJ] == 'X') && (playfield[i + 2][ptrJ] == 'X') && (i != -1)) {
            vertical++;
            i -= 2;
        }
        //��ਧ��⠫� ��ࠢ�
        j = ptrJ + 2;
        while ((playfield[ptrI][j] == 'X') && (playfield[ptrI][j - 2] == 'X') && (j != 2 * length + 1)) {
            horizontal++;
            j += 2;
        }
        //��ਧ��⠫� �����
        j = ptrJ - 2;
        while ((playfield[ptrI][j] == 'X') && (playfield[ptrI][j + 2] == 'X') && (j != -1)) {
            horizontal++;
            j -= 2;
        }
        //�������� ���������
        //��������� ����� ��ࠢ�
        i = ptrI - 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'X') && (playfield[i + 2][j - 2] == 'X') && (i != -1) && (j != 2 * length + 1)) {
            SecondaryDiagonal++;
            i -= 2;
            j += 2;
        }
        //��������� ���� �����
        i = ptrI + 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'X') && (playfield[i - 2][j + 2] == 'X') && (i != 2 * height + 1) && (j != -1)) {
            SecondaryDiagonal++;
            i += 2;
            j -= 2;
        }
        //������� ���������
        //��������� ����� �����
        i = ptrI - 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'X') && (playfield[i + 2][j + 2] == 'X') && (i != -1) && (j != -1)) {
            MainDiagonal++;
            i -= 2;
            j -= 2;
        }
        //��������� ���� ��ࠢ�
        i = ptrI + 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'X') && (playfield[i - 2][j - 2] == 'X') && (i != 2 * height + 1) && (j != 2 * length + 1)) {
            MainDiagonal++;
            i += 2;
            j += 2;
        }
        WinOrNah = (vertical >=  winExes) || (horizontal >= winExes) || (MainDiagonal >= winExes) || (SecondaryDiagonal >= winExes);
    } else { //�஢��塞, �먣ࠫ� �� ������
        //���⨪��� ����
        i = ptrI + 2;
        while ((playfield[i][ptrJ] == 'O') && (playfield[i - 2][ptrJ] == 'O') && (i != 2 * height + 1)) {
            vertical++;
            i += 2;
        }
        //���⨪��� �����
        i = ptrI - 2;
        while ((playfield[i][ptrJ] == 'O') && (playfield[i + 2][ptrJ] == 'O') && (i != -1)) {
            vertical++;
            i -= 2;
        }
        //��ਧ��⠫� ��ࠢ�
        j = ptrJ + 2;
        while ((playfield[ptrI][j] == 'O') && (playfield[ptrI][j - 2] == 'O') && (j != 2 * length + 1)) {
            horizontal++;
            j += 2;
        }
        //��ਧ��⠫� �����
        j = ptrJ - 2;
        while ((playfield[ptrI][j] == 'O') && (playfield[ptrI][j + 2] == 'O') && (j != -1)) {
            horizontal++;
            j -= 2;
        }
        //�������� ���������
        //��������� ����� ��ࠢ�
        i = ptrI - 2;
        j = ptrJ + 2;
        while ((playfield[i][j] == 'O') && (playfield[i + 2][j - 2] == 'O') && (i != -1) && (j != 2 * length + 1)) {
            SecondaryDiagonal++;
            i -= 2;
            j += 2;
        }
        //��������� ���� �����
        i = ptrI + 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'O') && (playfield[i - 2][j + 2] == 'O') && (i != 2 * height + 1) && (j != -1)) {
            SecondaryDiagonal++;
            i += 2;
            j -= 2;
        }
        //������� ���������
        //��������� ����� �����
        i = ptrI - 2;
        j = ptrJ - 2;
        while ((playfield[i][j] == 'O') && (playfield[i + 2][j + 2] == 'O') && (i != -1) && (j != -1)) {
            MainDiagonal++;
            i -= 2;
            j -= 2;
        }
        //��������� ���� ��ࠢ�
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
//����䥩� �� �६� ����
void gameUI() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("����� 室��: ");
    if (count % 2 == 0) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("��������");
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" (%d ��� ������)", winExes);
    } else {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("������");
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" (%d ��� ������)", winZeroes);
    }
    printf("\n");
    draw_playfield();
}
//��� (������ ���� � �ࠢ�����)
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
                                goto UA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                        goto UA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                goto DA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                        goto DA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                goto LA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                        goto LA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                goto RA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                                        goto RA_leave; //��ᯮ�� ���� ���� �� ��� ����� ���
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
                        printf("\n�������� ");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("��������\n\n");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("��� ��室� � ������� ���� ������ TAB");
                    } else {
                        printf("\n�������� ");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("������\n\n");
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("��� ��室� � ������� ���� ������ TAB");
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
                    printf("\n�����\n\n��� ��室� � ������� ���� ������ TAB");
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