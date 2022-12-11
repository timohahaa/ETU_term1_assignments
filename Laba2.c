#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#define ENTER 13
#define TAB 9
#define UP_ARROW 72
#define DOWN_ARROW 80
#define BACKSPACE 8
#define MINUS 45

//глобальные переменные
int num;
long int answer;
long int answer_float; //если нужно выводить вещественные ответы, поменять тип на double
int answer_exists = 10;
long int num_1 = 0;
long int num_2 = 0;

//описание математических действий
//если нужно выводить вещественные ответы поменять тип на double в делении, возведении в степень и извлечении корня, убрать переменную helper
//сложение
long int task_sum(int a, int b){
    int ans_sum;
    ans_sum = a + b;
    return(ans_sum);
}
//вычитание
long int task_diff(int a, int b){
    int ans_diff;
    ans_diff = a - b;
    return(ans_diff);
}
//умножение
long int task_prod(int a, int b){
    int ans_prod;
    ans_prod = a * b;
    return(ans_prod);
}
//деление
long int task_div(int a, int b){
    long int ans_div;
    ans_div = a / b;
    return(ans_div);
}
//возведение в степень
long int task_exp(int a, int b){
    long int ans_exp;
    double ans_helper;
    ans_helper = pow(a, b);
    ans_exp = ans_helper;
    return(ans_helper);
}
//извлечение корня
long int task_NthRoot(int a, int b) {
    long int ans_NthRoot;
    double ans_helper;
    if(a >= 0) {
        ans_helper = pow(a, (1.0/b));
    } else {
        ans_helper = -1 * pow(-1 * a, (1.0/b));
    }
    ans_NthRoot = ans_helper;
    return (ans_NthRoot);
}

//ввод числа
long int get_number() {
    int count = 0;
    int number = 0;
    int full_number = 0;
    int sign = 1;
    int count_numbers;
    int count_numbers_helper;
    while(count != 1) {
        count_numbers = 0;
        count_numbers_helper = full_number;
        while(count_numbers_helper != 0) {
            count_numbers_helper = count_numbers_helper / 10;
            count_numbers ++;
        }
        if(count_numbers < 9) {
            system("cls");
            printf("Введите ваше число:");
            printf("\n");
            printf("================================================================================\n");
            if(sign == -1){
                printf("-");
            }
            printf("%d", full_number);
            printf("\n");
            printf("================================================================================\n");
            printf("Для того, чтобы поменять знак числа на противоположный, нажмите '-'\n");
            printf("Для подтверждения введенного числа нажмите ENTER");
            number = getch();
            switch(number) {
                case '1':
                    number = 1;
                    full_number = full_number * 10 + number;
                    break;
                case '2':
                    number = 2;
                    full_number = full_number * 10 + number;
                    break;
                case '3':
                    number = 3;
                    full_number = full_number * 10 + number;
                    break;
                case '4':
                    number = 4;
                    full_number = full_number * 10 + number;
                    break;
                case '5':
                    number = 5;
                    full_number = full_number * 10 + number;
                    break;
                case '6':
                    number = 6;
                    full_number = full_number * 10 + number;
                    break;
                case '7':
                    number = 7;
                    full_number = full_number * 10 + number;
                    break;
                case '8':
                    number = 8;
                    full_number = full_number * 10 + number;
                    break;
                case '9':
                    number = 9;
                    full_number = full_number * 10 + number;
                    break;
                case '0':
                    number = 0;
                    full_number = full_number * 10 + number;
                    break;
                case ENTER:
                    count = 1;
                    break;
                case MINUS:
                    sign *= -1;
                    break;
                case BACKSPACE:
                    full_number = full_number / 10;
                    break;
                default:
                    number = 0;
                    break;
            }
        } else if(count_numbers == 9) {
            system("cls");
            printf("Введите ваше число:");
            printf("\n");
            printf("================================================================================\n");
            if(sign == -1){
                printf("-");
            }
            printf("%d", full_number);
            printf("\n");
            printf("================================================================================\n");
            printf("Нельзя ввести число, имеющее больше 9 разрядов. Пожалуйста, остановитесь!\n");
            printf("Для того, чтобы поменять знак числа на противоположный, нажмите '-'\n");
            printf("Для подтверждения введенного числа нажмите ENTER");
            number = getch();
            switch(number) {
                case ENTER:
                    count = 1;
                    break;
                case MINUS:
                    sign *= -1;
                    break;
                case BACKSPACE:
                    full_number = full_number / 10;
                    break;
                default:
                    number = 0;
                    break;
            }
        }

    }
    full_number = sign * full_number;
    system("cls");
    return(full_number);
}

//интерфейс калькулятора
void calc_interface() {
    printf("КАЛЬКУЛЯТОР\n");
    printf("================================================================================\n");
    printf("Введите номер команды или используйте стрелки 'вверх' и 'вниз'\n");
    printf("Нажмите клавишу ENTER чтобы подтвердить выбор команды\n");
    printf("================================================================================\n");
    printf("1)Ввести первое число");
    if (num == 1) {
        printf("     <--");
    }
    printf("\n");
    printf("2)Ввести второе число");
    if (num == 2) {
        printf("     <--");
    }
    printf("\n");
    printf("3)Сложение");
    if (num == 3) {
        printf("     <--");
    }
    printf("\n");
    printf("4)Вычитание второго числа из первого");
    if (num == 4) {
        printf("     <--");
    }
    printf("\n");
    printf("5)Умножение");
    if (num == 5) {
        printf("     <--");
    }
    printf("\n");
    printf("6)Деление первого числа на второе");
    if (num == 6) {
        printf("     <--");
    }
    printf("\n");
    printf("7)Возведение первого числа в степень, равную второму числу");
    if (num == 7) {
        printf("     <--");
    }
    printf("\n");
    printf("8)Корень степени N, равной второму числу, из первого числа");
    if (num == 8) {
        printf("     <--");
    }
    printf("\n");
    printf("9)Поменять первое и второе число местами");
    if (num == 9) {
        printf("     <--");
    }
    printf("\n");
    printf("================================================================================\n");
    printf("Первое число: %d", num_1);
    printf("\n");
    printf("Второе число: %d", num_2);
    printf("\n");
    printf("================================================================================\n");
    if(answer_exists == 1) {
        printf("Ответ: %d", answer);
    } else if(answer_exists == 0) {
        printf("Вы пытались поделить на ноль! Попробуйте ввести числа снова.");
    } else if(answer_exists == -1) {
        printf("Вы пытались извлечь корень четной степени из отрицательного числа!\nПопробуйте ввести числа снова.");
    } else if(answer_exists == -2) {
        printf("Вы пытались извлечь корень степени ноль! Попробуйте ввести числа снова.");
    } else if(answer_exists == 2) {
        printf("Ответ: %d", answer_float); //если нужно выводить вещественные ответы, поменять на %f
    } else if(answer_exists == -3) {
        printf("Не можем перемножить такие большие числа. Попробуйте ввести числа снова.");
    } else if(answer_exists == -4) {
        printf("Не можем выполнить возведение в степень.\nВозможно, вы ввели слишком большое основание и/или показатель.\nПопробуйте ввести числа снова.");
    } else if(answer_exists == -5) {
        printf("Нельзя возвести ноль в отрицательную степень! Попробуйте ввести числа снова.");
    }
    printf("\n");
    printf("================================================================================\n");
    printf("Для того, чтобы закрыть программу, нажмите TAB");
}

//выход из программы
void leave() {
    num = 11;
}

//поменять числа местами
void numbers_switch() {
    long int amogus;
    amogus = num_1;
    num_1 = num_2;
    num_2 = amogus;
}

//выбор действия
void get_task() {
    switch(num) {
        case 3:
            answer = task_sum(num_1, num_2);
            answer_exists = 1;
            break;
        case 4:
            answer = task_diff(num_1, num_2);
            answer_exists = 1;
            break;
        case 5:
            if(num_1 == 0 || num_2 == 0) {
                answer = 0;
                answer_exists = 1;
            } else if(labs(num_1) < 2147483647 / labs(num_2)) {
                answer = task_prod(num_1, num_2);
                answer_exists = 1;
            } else {
                answer_exists = -3;
            }
            break;
        case 6:
            if(num_2 == 0) {
                answer_exists = 0;
            } else {
                answer_float = task_div(num_1, num_2);
                answer_exists = 2;
            }
            break;
        case 7:
            if(num_1 == 0) {
                if(num_2 < 0) {
                    answer_exists = -5;
                } else {
                    answer_float = task_exp(num_1, num_2);
                    answer_exists = 2;
                }
            } else if(num_2 < (21.48/log((double)(labs(num_1))))) {
                answer_float = task_exp(num_1, num_2);
                answer_exists = 2;
            } else {
                answer_exists = -4;
            }
            break;
        case 8:
            if(num_2 % 2 == 0) {
                if(num_1 < 0) {
                    answer_exists = -1;
                } else if(num_2 == 0) {
                    answer_exists = -2;
                } else {
                    answer_float = task_NthRoot(num_1, num_2);
                    answer_exists = 2;
                }
            } else {
                answer_float = task_NthRoot(num_1, num_2);
                answer_exists = 2;
            }
            break;
        case 1:
            num_1 = get_number();
            break;
        case 2:
            num_2 = get_number();
            break;
        case 9:
            numbers_switch();
            break;
    }
}

//мейн)))
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int command_num;
    num = 1;
    while(num != 11) {
        calc_interface();
        command_num = getch();
        switch(command_num) {
            case '1':
                num = 1;
                system("cls");
                break;
            case '2':
                num = 2;
                system("cls");
                break;
            case '3':
                num = 3;
                system("cls");
                break;
            case '4':
                num = 4;
                system("cls");
                break;
            case '5':
                num = 5;
                system("cls");
                break;
            case '6':
                num = 6;
                system("cls");
                break;
            case '7':
                num = 7;
                system("cls");
                break;
            case '8':
                num = 8;
                system("cls");
                break;
            case '9':
                num = 9;
                system("cls");
                break;
            case UP_ARROW:
                num -= 1;
                if(num == 0) {
                    num = 9;
                }
                system("cls");
                break;
            case DOWN_ARROW:
                num += 1;
                if(num == 10) {
                    num = 1;
                }
                system("cls");
                break;
            case ENTER:
                system("cls");
                get_task();
                break;
            case TAB:
                leave();
                break;
            default:
                system("cls");
                break;
        }
    }
    return 0;
}