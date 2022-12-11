#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER 13
#define BACKSPACE 8
#define TAB 9
//SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
//const int size=21;
char str1[21] = "Hello, world!";
char str2[21] = "Example123";
char * ptr1 = &str1[0];
char * ptr2 = &str2[0];
int size = 21;
int num = 1, n_forNcpy = 1, start = 1, finish = 1, param = 1;
int colorcounter = 0, NcpyCounter = 0;

//длинна строки, возвращает число int - длинну строки
int strLength( char* string) {
    int i;
    for (i = 0; *(string + i) != '\0'; i++) {}
    return (i);
}
//перевернуть строку, переворачивает строку, ничего не возвращает
void strReverse ( char* string) {
    int i, len = strLength(string);
    char new_str[len];
    char *new_str_ptr = &new_str[0];
    for (i = 0; i < len; i++) {
        new_str[i] = *(string + i);
    }
    int firstElement, lastElement;
    for (i = 0; i < len / 2; i++) {
        firstElement = new_str[i];
        lastElement = new_str[len - i - 1];
        new_str[i] = lastElement;
        new_str[len - i - 1] = firstElement;
    }
    for (i = 0; i < len + 1; i++) {
        *(string + i) = *(new_str_ptr + i);
    }
}
//копирует src в dest, не меняет src, меняет dest, ничего не возвращает
void strCopy(/*Куда копируем*/ char* dest, /*Что копируем*/ char* src) {
    for (int i = 0; i < size; i++) {
        *(dest + i) = *(src + i);
    }
}
//"приклеивает" src к dest с конца и до того момента, пока dest не заполнится полностью, до символа \0 в src
//оставляет последний символ в dest нетронутым, подразумевается, что там находится \0
void strConcat(/*к чему приклеиваем*/ char* dest,/*что приклеиваем*/ char* src) {
    int len = strLength(dest);
    for (int i = strLength(dest); (i < size - 1 ) && (*(src + i - len) != '\0'); i++) {
        *(dest + i) = *(src + i - len);
    }
}
//преобразует все буквы в строке к верхему регистру, меняет саму строку
void strUPcase( char* string) {
    for (int i = 0; i < strLength((string)); i++) {
        if ((*(string + i) <= 122) && (*(string + i)>= 97)) {
            *(string + i) -= 32;
        }
    }
}
//преобразует все буквы в строке к нижнему регистру, меняет саму строку
void strLOWcase( char* string) {
    for (int i = 0; i < strLength((string)); i++) {
        if ((*(string + i) <= 90) && (*(string + i)>= 65)) {
            *(string + i) += 32;
        }
    }
}
// strncpy ровно как в документации
void strNcopy(/*куда копируем*/ char* dest,/*что копируем*/ char* src,/*сколько копируем*/ int n) {
    int lenOfSrc = strLength(src), lenOfDest = strLength(dest);
    int count = 0, i;
    if (n > size) {n = size;}
    for (i = 0; (count < n) && (i < lenOfSrc); i++) {
        *(dest + i) = *(src + i);
        count++;
    }
    for (; count < n; count++) {
        *(dest + i) = '\0';
        i++;
    }
}
//аналогично срезам в питоне, "режет" строку с индекса start до индекса finish
//finish не входит в конечный срез, резултат записывается в исходную строку,
//start < 0 -> 0, finish > strLength -> strLength, start >= finish -> start = finish
void PythonSlice(/*что режем*/ char* string,/*с какого элемента*/ int start,/*по какой элемент*/ int finish) {
    int i, j, lenOfString = strLength(string);
    if (finish > lenOfString) {finish = lenOfString;}
    if (start < 0) {start = 0;}
    if (start >= finish) {start = finish;}
    int lenOfCutString = finish - start;
    char new_str[lenOfCutString];
    char *new_str_ptr = &new_str[0];
    for (i = start, j = 0; i < finish; i++, j++) {
        *(new_str_ptr + j) = *(string + i);
    }
    int count = 0;
    for (i = 0; i < lenOfCutString; i++) {
        *(string + i) = *(new_str_ptr + i);
        count++;
    }
    for (;count < lenOfString; i++) {
        *(string + i) = '\0';
        count++;
    }
}

//все, что ниже - уже не интересно, это просто менюшка, кнопочти, все такое.....
void ConsoleColorBlue() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColorWhite() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleBackgroundBlue() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleBackgroundDefault() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void DrawMenuArrow() {
    ConsoleColorBlue();
    printf("     <<<");
    ConsoleColorWhite();
}
void help() { //me...
    ConsoleColorWhite();
    switch (num) {
        case 1:
            printf("strlen - длинна строки, возвращает число int - длинну строки до символа \\0\n\n");
            break;
        case 2:
            printf("strrev - переворачивает строку, меняет при этом исходную строку, ничего не возвращает\n"
                   "ПРИМЕР: abcde --> edcba\n\n");
            break;
        case 3:
            printf("strUcase - преобразует все буквы в строке к верхнему регистру (игнорирует не буквы), меняет при этом исходную строку\n"
                   "ПРИМЕР: abC3deF67 --> ABC3DEF67\n\n");
            break;
        case 4:
            printf("strLcase - преобразует все буквы в строке к нижнему регистру (игнорирует не буквы), меняет при этом исходную строку\n"
                   "ПРИМЕР: abC3deF67 --> abc3def67\n\n");
            break;
        case 5:
            printf("strcat - приклеивает source к destination с конца и до того момента, пока destination не заполнится полностью\n"
                   "Двигается в source до символа \\0 и не трогает в destination последний байт подразумевая, что там находится \\0\n"
                   "ПРИМЕР: source[10] - abcde, destination[15] - 123456, получим destination[15] - 123456abcde\n\n");
            break;
        case 6:
            printf("strcpy - копирует source в destination, меняет destination\n"
                   "ВАЖНО: sourse и destination должны занимать в памяти одинаковое количество байт, иначе ждите undefined behaviour\n"
                   "ПРИМЕР: source[10] - abcde, destination[10] - 1234567890, получим destination[10] - abcde\n\n");
            break;
        case 7:
        case 8:
            printf("strncat - почитайте документацию :) ИЛИ если вы - Валерий Евгеньевич Синев - спросите сидящего справа от вас автора программы\n\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("Срез строки - аналогично срезам строк в Python - режет строку с индекса start до индекса finish (включая start, не включая finish)\n"
                   "Результат записывается в исходную строку\n"
                   "ВАЖНО: разница с питоном в том, что start < 0 приводится к start = 0, start > finish приводится к start = finish\n"
                   "и если finish больше чем количество байт, занимаемое строкой, то finish приводится к finish = кол-во байт\n\n");
            break;
        default:
            break;
    }
}
//вывести строку посимвольно
void output_symbol_by_symbol(char* string) {
    printf(">>>");
    for (int i = 0; i < size; i++) {
        if (*(string + i) == '\0') {
            printf("\\0");
        } else {printf("%c", *(string + i));}
    }
    printf("<<<");
}
//уже в 1488133722869 раз написанное меню)))
void menu() {
    ConsoleColorWhite();
    printf("Выберите номер команды и нажмите ENTER\n");
    printf("=================================================================\n");
    printf("А) Ввести первую строку (destination):  ");
    if (colorcounter == 1) {
        ConsoleBackgroundBlue();
        printf(" %s ", str1);
        ConsoleBackgroundDefault();
    } else {printf(" %s ", str1);}
    if (num == 13) {DrawMenuArrow();}
    printf("\n");
    printf("B) Ввести вторую строку (source):  ");
    if (colorcounter == 2) {
        ConsoleBackgroundBlue();
        printf(" %s ", str2);
        ConsoleBackgroundDefault();
    } else {printf(" %s ", str2);}
    if (num == 14) {DrawMenuArrow();}
    printf("\n");
    printf("C) Поменять строки местами");
    if (num == 15) {DrawMenuArrow();}
    printf("\n");
    printf("Команды 1-4, 8 выполняются с destination\n");
    printf("=================================================================\n");
    printf("1) strlen (длинна строки):  ");
    ConsoleBackgroundBlue();
    printf(" %d ", strLength(ptr1));
    ConsoleBackgroundDefault();
    if (num == 1) {DrawMenuArrow();}
    printf("\n");
    printf("2) strrev (перевернуть строку)");
    if (num == 2) {DrawMenuArrow();}
    printf("\n");
    printf("3) strUcase (в верхний регистр)");
    if (num == 3) {DrawMenuArrow();}
    printf("\n");
    printf("4) strLcase (в нижний регистр)");
    if (num == 4) {DrawMenuArrow();}
    printf("\n");
    printf("5) strcat (конкатенация)");
    if (num == 5) {DrawMenuArrow();}
    printf("\n");
    printf("6) strcpy (копирование)");
    if (num == 6) {DrawMenuArrow();}
    printf("\n");
    printf("7) strncat (ровно как в документации!)");
    if (num == 7) {DrawMenuArrow();}
    printf("\n");
    printf("   Значение num:  ");
    if (colorcounter == 3) {
        ConsoleBackgroundBlue();
        printf(" %d ", param);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", n_forNcpy);}
    if (num == 8) {DrawMenuArrow();}
    printf("\n");
    printf("8) Срез строки (как в Python)");
    if (num == 9) {DrawMenuArrow();}
    printf("\n");
    printf("   Значение start:  ", start);
    if (colorcounter == 4) {
        ConsoleBackgroundBlue();
        printf(" %d ", param);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", start);}
    if (num == 10) {DrawMenuArrow();}
    printf("\n");
    printf("   Значение finish:  ", finish);
    if (colorcounter == 5) {
        ConsoleBackgroundBlue();
        printf(" %d ", param);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", finish);}
    if (num == 11) {DrawMenuArrow();}
    printf("\n");
    printf("9) Выход");
    if (num == 12) {DrawMenuArrow();}
    printf("\n");
    printf("=================================================================\n");
    printf("Строка destination посимвольно:  ");
    output_symbol_by_symbol(ptr1);
    printf("\n");
    printf("Строка source посимвольно:  ");
    output_symbol_by_symbol(ptr2);
    printf("\n\n");
    help();
}
//ввод параметров start, finish и num, предполагается, что у них есть значение по умолчанию
int input_param(int whatIsBeingInput) {
    param = whatIsBeingInput;
    int key, leave_function = 0;
    system("cls");
    menu();
    while (leave_function != 1) {
        if (param < 100) {
            key = getch();
            if ((key >= 48) && (key <= 57)) {
                param = param * 10 + (key - 48);
                system("cls");
                menu();
            } else if (key == BACKSPACE) {
                param /= 10;
                system("cls");
                menu();
            } else if (key == ENTER) {
                NcpyCounter = 1;
                colorcounter = 0;
                leave_function = 1;
            }
        } else {
            key = getch();
            if (key == BACKSPACE) {
                param /= 10;
                system("cls");
                menu();
            } else if (key == ENTER) {
                NcpyCounter = 1;
                colorcounter = 0;
                leave_function = 1;
            }
        }
    }
    return (param);
}
//ввод строки с клавиатуры
void input_string(char* string) {
    int key, leave_function = 0;
    system("cls");
    menu();
    while (leave_function != 1) {
        if (strLength(string) < 20) {
            key = getch();
            if (key == 224) {
                key = getch();
                //игнорируем все arrow keys
            } else if ((key >= 32) && (key <= 126)) {
                *(string + strLength(string)) = key;
                system("cls");
                menu();
            } else if (key == BACKSPACE) {
                *(string + strLength(string) - 1) = '\0';
                system("cls");
                menu();
            } else if (key == ENTER) {
                colorcounter = 0;
                leave_function = 1;
            }
        } else {
            key = getch();
            if (key == BACKSPACE) {
                *(string + strLength(string) - 1) = '\0';
                system("cls");
                menu();
            } else if (key == ENTER) {
                colorcounter = 0;
                leave_function = 1;
            }
        }
    }
}
//поменять строки местами
void swap_strings() {
    char helper[21] = {0};
    int i;
    for (i = 0; i < size; i++) {helper[i] = str1[i];}
    for (i = 0; i < size; i++) {str1[i] = str2[i];}
    for (i = 0; i < size; i++) {str2[i] = helper[i];}
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int get_key;
    menu();
    while (num != 20) {
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
            case '8':
                num = 9;
                system("cls");
                menu();
                break;
            case '9':
                num = 12;
                system("cls");
                menu();
                break;
            case 'a':
            case 'A':
                num = 13;
                system("cls");
                menu();
                break;
            case 'b':
            case 'B':
                num = 14;
                system("cls");
                menu();
                break;
            case 'c':
            case 'C':
                num = 15;
                system("cls");
                menu();
                break;

            case UP_ARROW:
                num -= 1;
                if (num == 0) {num = 15;}
                system("cls");
                menu();
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 16) {num = 1;}
                system("cls");
                menu();
                break;
            case ENTER:
                switch (num){
                    case 1:
                        break;
                    case 2:
                        strReverse(ptr1);
                        system("cls");
                        menu();
                        break;
                    case 3:
                        strUPcase(ptr1);
                        system("cls");
                        menu();
                        break;
                    case 4:
                        strLOWcase(ptr1);
                        system("cls");
                        menu();
                        break;
                    case 5:
                        strConcat(ptr1,ptr2);
                        system("cls");
                        menu();
                        break;
                    case 6:
                        strCopy(ptr1,ptr2);
                        system("cls");
                        menu();
                        break;
                    case 7:
                        strNcopy(ptr1,ptr2,n_forNcpy);
                        system("cls");
                        menu();
                        break;
                    case 8:
                        colorcounter = 3;
                        n_forNcpy = input_param(n_forNcpy);
                        system("cls");
                        menu();
                        break;
                    case 9:
                        PythonSlice(ptr1,start,finish);
                        system("cls");
                        menu();
                        break;
                    case 10:
                        colorcounter = 4;
                        start = input_param(start);
                        system("cls");
                        menu();
                        break;
                    case 11:
                        colorcounter = 5;
                        finish = input_param(finish);
                        system("cls");
                        menu();
                        break;
                    case 12:
                        num = 20;
                        break;
                    case 13:
                        colorcounter = 1;
                        input_string(ptr1);
                        system("cls");
                        menu();
                        break;
                    case 14:
                        colorcounter = 2;
                        input_string(ptr2);
                        system("cls");
                        menu();
                        break;
                    case 15:
                        swap_strings();
                        system("cls");
                        menu();
                        break;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
