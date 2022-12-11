#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER 13
#define BACKSPACE 8

int num = 1;
int L = 1;
int H = 1;
unsigned char a[12][12] = {{0}};

//ввести значение длинны/ширины массива
int get_HL_value() {
    int leave_function = 0;
    int value = 1;
    int count_symbols;
    int value_duplicate;
    int get_number_key;
    int number = 0;
    system("cls");
    while (leave_function != 1) {
        count_symbols = 0;
        value_duplicate = value;
        while (value_duplicate != 0) {
            value_duplicate /= 10;
            count_symbols++;
        }
        if (count_symbols < 2) {
            if (value == 0) {
                printf("Введите значение длинны/ширины от 1 до 12\n");
                printf("========================================\n");
                printf("%d\n", value);
                printf("========================================\n");
                printf("Введенное число не может равняться нулю.");
                get_number_key = getch();
                switch (get_number_key) {
                    case '1':
                        number = 1;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '2':
                        number = 2;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '3':
                        number = 3;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '4':
                        number = 4;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '5':
                        number = 5;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '6':
                        number = 6;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '7':
                        number = 7;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '8':
                        number = 8;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '9':
                        number = 9;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '0':
                        number = 0;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case BACKSPACE:
                        value /= 10;
                        system("cls");
                        break;
                    default:
                        system("cls");
                        break;
                }
            } else if (value != 0) {
                printf("Введите значение длинны/ширины от 1 до 12\n");
                printf("========================================\n");
                printf("%d\n", value);
                printf("========================================\n");
                printf("Для подтверждения введенного числа нажмите ENTER");
                get_number_key = getch();
                switch (get_number_key) {
                    case '1':
                        number = 1;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '2':
                        number = 2;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '3':
                        number = 3;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '4':
                        number = 4;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '5':
                        number = 5;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '6':
                        number = 6;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '7':
                        number = 7;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '8':
                        number = 8;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '9':
                        number = 9;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case '0':
                        number = 0;
                        value = value * 10 + number;
                        system("cls");
                        break;
                    case BACKSPACE:
                        value /= 10;
                        system("cls");
                        break;
                    case ENTER:
                        leave_function = 1;
                        break;
                    default:
                        system("cls");
                        break;
                }
            }

        } else if (count_symbols == 2) {
            if (value > 12) {
                printf("Введите значение длинны/ширины от 1 до 12\n");
                printf("========================================\n");
                printf("%d\n", value);
                printf("========================================\n");
                printf("Нужно ввести значение длинны от 1 до 12!\n");
                printf("Сотрите число с помощью BACKSPACE и попробуйте ввести новое число.");
                get_number_key = getch();
                switch (get_number_key) {
                    case BACKSPACE:
                        value /= 10;
                        system("cls");
                        break;
                    default:
                        system("cls");
                        break;
                }
            } else if (value <= 12){
                printf("Введите значение длинны/ширины от 1 до 12\n");
                printf("========================================\n");
                printf("%d\n", value);
                printf("========================================\n");
                printf("Нужно ввести значение длинны от 1 до 12!\n");
                printf("У вас не получится ввести число больше 12, даже не пытайтесь!\n");
                printf("\n");
                printf("Для подтверждения введенного числа нажмите ENTER");
                get_number_key = getch();
                switch (get_number_key) {
                    case BACKSPACE:
                        value /= 10;
                        system("cls");
                        break;
                    case ENTER:
                        leave_function = 1;
                        break;
                    default:
                        system("cls");
                        break;
                }
            }
        }
    }
    return (value);
}
//спираль по часовой стрелке внутрь
void get_list_clockwise_in() {
    int ring = 0;
    int i;
    int j;
    int count = 1;
    int count_rings;
    for (count_rings = 0; count_rings < ((H > L) ? L : H) / 2; count_rings ++) {
        for (i = ring; i < L - ring; i++) {
            a[ring][i] = count;
            count++;
        }

        for (j = ring + 1; j < H - ring; j++) {
            a[j][L - ring - 1] = count;
            count++;
        }

        for (i = L - ring - 1 - 1; i > ring - 1; i--) {
            a[H - ring - 1][i] = count;
            count++;
        }

        for (j = H - ring - 1 - 1; j > ring; j--) {
            a[j][ring] = count;
            count++;
        }
        ring++;
    }
    if (L > H) {
        if (H % 2 != 0) {
            for (i = ring; i < L - ring; i++) {
                a[ring][i] = count;
                count++;
            }
        }
    } else {
        if (L % 2 != 0){
            for (j = ring; j < H - ring; j++) {
                a[j][L - ring - 1] = count;
                count++;
            }
        }
    }
}
//спираль против часовой стрелки изнутри
void get_list_counterclockwise_out() {
    int ring = 0;
    int i;
    int j;
    int count = L * H;
    int count_rings;
    for (count_rings = 0; count_rings < ((H > L) ? L : H) / 2; count_rings ++) {
        for (i = ring; i < L - ring; i++) {
            a[ring][i] = count;
            count--;
        }

        for (j = ring + 1; j < H - ring; j++) {
            a[j][L - ring - 1] = count;
            count--;
        }

        for (i = L - ring - 1 - 1; i > ring - 1; i--) {
            a[H - ring - 1][i] = count;
            count--;
        }

        for (j = H - ring - 1 - 1; j > ring; j--) {
            a[j][ring] = count;
            count--;
        }
        ring++;
    }
    if (L > H) {
        if (H % 2 != 0) {
            for (i = ring; i < L - ring; i++) {
                a[ring][i] = count;
                count--;
            }
        }
    } else {
        if (L % 2 != 0){
            for (j = ring; j < H - ring; j++) {
                a[j][L - ring - 1] = count;
                count--;
            }
        }
    }
}
//отзеркалить спираль - получить две другие
void mirror_list() {
    unsigned char b[12][12] = {{0}};
    int i;
    int j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < L; j++) {
            b[i][j] = a[i][j];
        }
    }
    for (i = 0; i < H; i++) {
        for (j = 0; j < L; j++) {
            a[i][j] = b[i][L-j-1];
        }
    }
}
//вывод массива на экран
void output_list_in_console() {
    int len;
    int hei;
    for (hei = 0; hei < H; hei++) {
        for (len = 0; len < L; len++) {
            if (a[hei][len] < 10) {
                printf("  %d ",a[hei][len]);
            } else if (a[hei][len] < 100) {
                printf(" %d ", a[hei][len]);
            } else {
                printf("%d ", a[hei][len]);
            }
            if (len == L - 1) {
                printf("\n\n");
            }
        }
    }
}
//пользовательский интерфейс
void UI() {
    printf("Выберите команду.\n");
    printf("=================================================================\n");
    printf("1)Ввести длинну спирали (нажмите Enter): ");
    printf(" %d", L);
    if (num == 1) {
        printf("     <==");
    }
    printf("\n");
    printf("2)Ввести ширину спирали (нажмите Enter): ");
    printf(" %d", H);
    if (num == 2) {
        printf("     <==");
    }
    printf("\n");
    printf("3)Спираль из верхнего левого угла внутрь (по часовой стрелке)");
    if (num == 3) {
        get_list_clockwise_in();
        printf("     <==");
    }
    printf("\n");
    printf("4)Спираль из верхнего правого угла внутрь (против часовой стрелки)");
    if (num == 4) {
        get_list_clockwise_in();
        mirror_list();
        printf("     <==");
    }
    printf("\n");
    printf("5)Спираль изнутри в наружу по часовой стрелке");
    if (num == 5) {
        get_list_counterclockwise_out();
        mirror_list();
        printf("     <==");
    }
    printf("\n");
    printf("6)Спираль изнутри в наружу против часовой стрелки");
    if (num == 6) {
        get_list_counterclockwise_out();
        printf("     <==");
    }
    printf("\n");
    printf("7)Выход (нажмите Enter)");
    if (num == 7) {
        printf("     <==");
    }
    printf("\n");
    printf("=================================================================\n\n");
    if ((num >2) && (num < 7)) {
        output_list_in_console();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int get_key;
    UI();
    while (num != 10) {
        get_key = getch();
        switch (get_key) {
            case '1':
                num = 1;
                system("cls");
                UI();
                break;
            case '2':
                num = 2;
                system("cls");
                UI();
                break;
            case '3':
                num = 3;
                system("cls");
                UI();
                break;
            case '4':
                num = 4;
                system("cls");
                UI();
                break;
            case '5':
                num = 5;
                system("cls");
                UI();
                break;
            case '6':
                num = 6;
                system("cls");
                UI();
                break;
            case '7':
                num = 7;
                system("cls");
                UI();
                break;
            case UP_ARROW:
                num -= 1;
                if (num == 0) {
                num = 7;
                }
                system("cls");
                UI();
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 8) {
                    num = 1;
                }
                system("cls");
                UI();
                break;
            case ENTER:
                if (num == 1) {
                    L = get_HL_value();
                    system("cls");
                    UI();
                } else if (num == 2) {
                    H = get_HL_value();
                    system("cls");
                    UI();
                } else if (num == 7) {
                    num = 10;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}