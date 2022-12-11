#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#define SIZE 8 //почему не работает с const int size = 8; ???
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER 13
#define BACKSPACE 8
#define TAB 9
#define MINUS 45

//array[maxI][maxJ]
//2-D array index [i][j] =>  1-D array index [i*maxI + j]

int num = 1;
int lambda = 1;
int error_code = 0;
int colorcounter = 0;
//перевод индекса двумерного массива в индекс одномепного массива
int _1Dindex(int i, int j) {
    return i * SIZE + j;
}
int matrix_1[SIZE * SIZE] = {
        4,2,3,0,0,0,0,0,
        8,5,6,0,0,0,0,0,
        2,4,8,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
};
int matrix_2[SIZE * SIZE] = {
        1,-3,0,0,0,0,0,0,
        0,2,0,0,0,0,0,0,
        5,-1,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
};
int result_matrix[SIZE * SIZE] = {0};
int dimI_1 = 3, dimJ_1 = 3, dimI_2 = 3, dimJ_2 = 2, dimI_r = 0, dimJ_r = 0;

//транспонирование
void transpose(int* matrix) {
    int buffer;
    int i = 0, j = 0;
    while (i < SIZE) {
        for (j = i; j < SIZE; j++) {
            buffer = *(matrix + _1Dindex(i,j));
            *(matrix + _1Dindex(i,j)) = *(matrix + _1Dindex(j,i));
            *(matrix + _1Dindex(j,i)) = buffer;
        }
        i++;
    }
}
//сложение и вычитание матриц
void sum(int* matrix_1, int* matrix_2, char is_subtraction, int* where_to_put_the_answer) {
    //к матрице 1 прибавляется матрица 2, результат записывается в where_to_put_the_answer, если is_subtraction = 1, то вычитается, а не прибавляется
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (is_subtraction) {
                *(where_to_put_the_answer + _1Dindex(i,j)) =  *(matrix_1 + _1Dindex(i,j)) - *(matrix_2 + _1Dindex(i,j));
            } else {*(where_to_put_the_answer + _1Dindex(i,j)) =  *(matrix_1 + _1Dindex(i,j)) + *(matrix_2 + _1Dindex(i,j));}
        }
    }
}
//произведение матриц
void product(int* right_matrix, int rows_rigth, int common_dimension, int* left_matrix, int columns_left, int* where_to_put_the_answer) {
    //правая матрица умножается на левую, результат записывается в where_to_put_the_answer, common_dimension - столбцов справа = строк слева
    int buffer[SIZE * SIZE] = {0};
    int i, j;
    for (int row = 0; row < rows_rigth; row++) {
        for (int column = 0; column < columns_left; column++) {
            for (i = 0; i < common_dimension; i++) {
                buffer[_1Dindex(row,column)] += *(right_matrix + _1Dindex(row,i)) * *(left_matrix + _1Dindex(i,column));
            }
        }
    }
    for (i = 0; i < rows_rigth; i++) {
        for (j = 0; j < columns_left; j++) {
            *(where_to_put_the_answer + _1Dindex(i,j)) = buffer[_1Dindex(i,j)]; //обновляем матрицу
        }
    }
}
//умножение/деление матрицы на число
void matrix_prod_number(int* matrix, int lambda, char is_division, int* where_to_put_the_answer) {
    //умножает каждый элемент матрицы на число lambda, если is_division = 1, то делит, а не умножает
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (is_division) {
                *(where_to_put_the_answer + _1Dindex(i,j)) = *(matrix + _1Dindex(i,j)) / lambda;
            } else {*(where_to_put_the_answer + _1Dindex(i,j)) = *(matrix + _1Dindex(i,j)) * lambda;}
        }
    }
}
//определитель
int determinant(int* matrix, int dimensions) {
    int answer = 0, sign = 1;
    if (dimensions == 1) {return *matrix;}
    if (dimensions == 2) {return *(matrix) * *(matrix + 9) - *(matrix + 1) * *(matrix + 8);}
    int did_skip = 0;
    for (int n = 0; n < dimensions; n++) { //раскладываем по строке
        //создаем минор
        int minor[SIZE * SIZE]; //неэффективно в плане памяти!!! :(
        //memset(&minor, 0, SIZE * SIZE * sizeof(int));
        //заполняем нужными элементами
        for (int i = 1; i < dimensions; i++) {
            did_skip = 0;
            for (int j = 0; j < dimensions; j++) {
                if (j != n) {
                    minor[_1Dindex(i - 1, j - did_skip)] = *(matrix + _1Dindex(i,j));
                } else {did_skip = 1;}
            }
        }
        answer += sign * determinant(&minor[0], dimensions - 1) * *(matrix + n);
        sign *= -1;
    }
    return answer;
}
//алгебраическое дополнение
int algebraic_complement(int* matrix, int crossed_out_i, int crossed_out_j, int dimensions) { //индексы как в программировании, начинаются с 0!!!
    int answer;
    int complement_matrix[SIZE * SIZE]; //неэффективно в плане памяти!!! :(
    int skipped_i = 0, skipped_j = 0;
    for (int i = 0; i < SIZE; i++) {
        if (i == crossed_out_i) {skipped_i = 1;}
        skipped_j = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j == crossed_out_j) {skipped_j = 1;}
            complement_matrix[_1Dindex(i,j)] = *(matrix + _1Dindex(i + skipped_i, j + skipped_j));
        }
    }
    answer = (int)pow(-1.0, (double)(crossed_out_i + crossed_out_j)) * determinant(&complement_matrix[0], dimensions - 1);
    return answer;
}
//обратная матрица - записывает в where_to_put_the_answer
//присоедененную матрицу БЕЗ ОПРЕДЕЛИТЕЛЯ, отдельно посчитать 1/определитель
void inverse_matrix(int* matrix, int dimensions, int* where_to_put_the_answer) {
    int attached_matrix[SIZE*SIZE] = {0}; //присоедененная матрица
    int i, j;
    for (i = 0; i < dimensions; i++) {
        for (j = 0; j < dimensions; j++) {
            attached_matrix[_1Dindex(i,j)] = algebraic_complement(&matrix[0], i, j, dimensions);
        }
    }
    transpose(&attached_matrix[0]);
    for (i = 0; i < dimensions; i++) {
        for (j = 0; j < dimensions; j++) {
            *(where_to_put_the_answer + _1Dindex(i,j)) = attached_matrix[_1Dindex(i,j)];
        }
    }
}
//МЕНЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮЮ И ТД И ТП
//все, что ниже - уже не интересно, это просто менюшка, кнопочти, все такое.....
void ConsoleColorGreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void ConsoleColorWhite() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleBackgroundGreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleBackgroundDefault() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void DrawMenuArrow() {
    ConsoleColorGreen();
    printf("     <<<");
    ConsoleColorWhite();
}
//возврат ошибки
void raise_error(int error_code) {
    switch (error_code) {
        case 1:
            printf("Нельзя складывать\\вычитать матрицы разного размера!\n");
            break;
        case 2:
            printf("Неверные размеры умножаемых матриц!\nКоличество столбцов слева =\\= количество строк справа!\n");
            break;
        case 3:
            printf("Нельзя создать матрицу с нулевым количеством строк\\столбцов!\n");
            break;
        case 4:
            printf("Найти определитель можно только для квадратной матрицы!\n");
            break;
        case 5:
            printf("Найти обратную матрицу можно только для квадратной матрицы!\n");
            break;
        case 6:
            printf("Найту обратную можно только для матрицы с ненулевым определителем!\n");
            break;
    }
}
//вывести матрицу на экран
void print_matrix(int* matrix, int dimI, int dimJ) {
    for (int i = 0; i < dimI; i++) {
        for (int j = 0; j < dimJ; j++) {
            printf("%5d", *(matrix + _1Dindex(i, j)));
            if (j == dimJ - 1) {printf("\n");}
        }
    }
}
//заполнить матрицу случайными числами от -10 до 10
void randomly_fill_matrix(int* matrix, int dimI, int dimJ) {
    srand(time(NULL));
    for (int i = 0; i < dimI; i++) {
        for (int j = 0; j < dimJ; j++) {
            *(matrix + _1Dindex(i,j)) = -10 + rand() % 21;
        }
    }
}
//меню
void menu(int lipovoe_chislo, int lipovoe_chislo2, int lipovoe_chuslo3) {
    ConsoleColorWhite();
    printf("Выберите номер команды и нажмите ENTER\n");
    printf("=================================================================\n");
    printf("А) Ввести первую матрицу:");
    if (num == 9) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    //вывод первой матрицы
    print_matrix(&matrix_1[0], dimI_1, dimJ_1);
    printf("B) Ввести вторую матрицу:");
    if (num == 10) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    //вывод второй матрицы
    print_matrix(&matrix_2[0], dimI_2, dimJ_2);
    printf("C) Поменять матрицы местами местами");
    if (num == 11) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("Функции 1-4 выполняются с первой матрицей :)\n");
    printf("=================================================================\n");
    printf("1) Определитель:  ");
    error_code = 0;
    if (dimI_1 == dimJ_1) {
        ConsoleBackgroundGreen();
        printf(" %d ", determinant(&matrix_1[0], dimI_1));
        ConsoleBackgroundDefault();
    } else {
        ConsoleBackgroundGreen();
        printf(" НЕТ ОПРЕДЕЛИТЕЛЯ :)");
        ConsoleBackgroundDefault();
    }
    if (num == 1) {
        DrawMenuArrow();
        if (dimI_1 != dimJ_1) {error_code = 4;}
    }
    printf("\n");
    printf("2) Обратная матрица");
    if (num == 2) {
        DrawMenuArrow();
        error_code = 0;
        if (dimI_1 == dimJ_1) {
            if (determinant(&matrix_1[0], dimI_1) != 0) {
                dimI_r = dimI_1;
                dimJ_r = dimJ_1;
                inverse_matrix(&matrix_1[0], dimI_1, &result_matrix[0]);
            } else {error_code = 6;}
        } else {error_code = 5;}
    }
    printf("\n");
    printf("3) Транспонировать матрицу");
    if (num == 3) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("4) Умножение матрицы на число: ");
    if (colorcounter == 4) {
        ConsoleBackgroundGreen();
        printf(" %d ", lambda);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", lambda);}
    if (num == 4) {
        DrawMenuArrow();
        error_code = 0;
        matrix_prod_number(&matrix_1[0], lambda, 0, &result_matrix[0]);
        dimI_r = dimI_1;
        dimJ_r = dimJ_1;
    }
    printf("\n");
    printf("5) Сложение М1 + М2");
    if (num == 5) {
        DrawMenuArrow();
        error_code = 0;
        if ((dimI_1 == dimI_2) && (dimJ_1 == dimJ_2)) {
            dimI_r = dimI_1;
            dimJ_r = dimJ_1;
            sum(&matrix_1[0], &matrix_2[0], 0, &result_matrix[0]);
        } else {error_code = 1;}
    }
    printf("\n");
    printf("6) Вычитание М1 - М2");
    if (num == 6) {
        DrawMenuArrow();
        error_code = 0;
        if ((dimI_1 == dimI_2) && (dimJ_1 == dimJ_2)) {
            dimI_r = dimI_1;
            dimJ_r = dimJ_1;
            sum(&matrix_1[0], &matrix_2[0], 1, &result_matrix[0]);
        } else {error_code = 1;}
    }
    printf("\n");
    printf("7) Умножение М1 х М2");
    if (num == 7) {
        DrawMenuArrow();
        error_code = 0;
        if (dimJ_1 == dimI_2) {
            dimI_r = dimI_1;
            dimJ_r = dimJ_2;
            product(&matrix_1[0],dimI_1,dimJ_1, &matrix_2[0], dimJ_2, &result_matrix[0]);
        } else {error_code = 2;}
    }
    printf("\n");
    printf("8) Выход");
    if (num == 8) {DrawMenuArrow(); error_code = 0;}
    printf("\n");
    printf("=================================================================\n");
    //результат или ошибка
    if (error_code) {
        raise_error(error_code);
    } else {print_matrix(&result_matrix[0], dimI_r, dimJ_r);}
}
//ввод НЕ ОТРИЦАТЕЛЬНОГО параметра - lambda
void input_param(int* whatIsBeingInput, int upper_bound, int can_be_zero ,void (*what_menu_is_being_used)(int, int, int), int what_matrix) {
    int key, leave_function = 0;
    system("cls");
    what_menu_is_being_used(what_matrix,8,8);
    while (leave_function != 1) {
        if (*whatIsBeingInput < upper_bound) {
            key = getch();
            if ((key >= 48) && (key <= 57)) {
                *whatIsBeingInput = *whatIsBeingInput * 10 + (key - 48);
                if (*whatIsBeingInput > upper_bound) {*whatIsBeingInput /= 10;}
                system("cls");
                what_menu_is_being_used(what_matrix, 8,8);
            } else if (key == BACKSPACE) {
                *whatIsBeingInput /= 10;
                system("cls");
                what_menu_is_being_used(what_matrix,8,8);
            } else if (key == ENTER) {
                if (can_be_zero) {leave_function = 1;
                } else if (*whatIsBeingInput != 0) {leave_function = 1;}
            }
        } else  if (*whatIsBeingInput == upper_bound) {
            key = getch();
            if (key == BACKSPACE) {
                *whatIsBeingInput /= 10;
                system("cls");
                what_menu_is_being_used(what_matrix,8,8);
            } else if (key == ENTER) {leave_function = 1;}
        }
    }
}
//поменять матрицы местами
void matrices_switch(int* matrix_1, int* matrix_2) {
    int buffer[SIZE*SIZE] = {0};
    int i, j;
    for (i  = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            buffer[_1Dindex(i,j)] = *(matrix_1 + _1Dindex(i,j));
        }
    }
    for (i  = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            *(matrix_1 + _1Dindex(i,j)) = *(matrix_2 + _1Dindex(i,j));
        }
    }
    for (i  = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            *(matrix_2 + _1Dindex(i,j)) = buffer[_1Dindex(i,j)];
        }
    }
}

void print_inputed_matrix(int* matrix, int dimI, int dimJ, int I, int J) {
    for (int i = 0; i < dimI; i++) {
        for (int j = 0; j < dimJ; j++) {
            if ((i == I) && (j == J)) {
                ConsoleBackgroundGreen();
                printf("%5d", *(matrix + _1Dindex(i, j)));
                ConsoleBackgroundDefault();
            } else {printf("%5d", *(matrix + _1Dindex(i, j)));}
            if (j == dimJ - 1) {printf("\n");}
        }
    }
}
//меню ввода матрицы
void input_matrix_MENU(int what_matrix, int I, int J) {
    int *matrix;
    int *dimI;
    int *dimJ;
    if (what_matrix == 1) {
        matrix = &matrix_1[0];
        dimI = &dimI_1;
        dimJ = &dimJ_1;
    } else {
        matrix = &matrix_2[0];
        dimI = &dimI_2;
        dimJ = &dimJ_2;
    }
    ConsoleColorWhite();
    printf("Выберите номер команды и нажмите ENTER\n");
    printf("=================================================================\n");
    printf("1) Ввести количество строк (от 1 до 8):");
    if (colorcounter == 101) {
        ConsoleBackgroundGreen();
        printf(" %d ", *dimI);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", *dimI);}
    if (num == 101) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("2) Ввести количество  (от 1 до 8):");
    if (colorcounter == 102) {
        ConsoleBackgroundGreen();
        printf(" %d ", *dimJ);
        ConsoleBackgroundDefault();
    } else {printf(" %d ", *dimJ);}
    if (num == 102) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("3) Заполнить элементы матрицы случайными числами от -10 до 10");
    if (num == 103) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("4) Заполнить элементы матрицы вручную");
    if (num == 104) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("5) Вернуться в основное меню");
    if (num == 105) {DrawMenuArrow();error_code = 0;}
    printf("\n");
    printf("=================================================================\n");
    print_inputed_matrix(matrix, *dimI, *dimJ, I, J);
}
void input_matrix_element(int* what_is_being_input, int what_matrix, int* i, int* j) {
    int key, leave_function = 0, sign = 1;
    system("cls");
    input_matrix_MENU(what_matrix, *i, *j);
    while (leave_function != 1) {
        key = getch();
        if (abs(*what_is_being_input) < 10) {
            if ((key >= 48) && (key <= 57)) {
                *what_is_being_input = sign * (abs(*what_is_being_input) * 10 + (key - 48));
                if (abs(*what_is_being_input) > 10) {*what_is_being_input = sign * (abs(*what_is_being_input) / 10);}
                system("cls");
                input_matrix_MENU(what_matrix, *i, *j);
            } else if (key == BACKSPACE) {
                *what_is_being_input = sign * (abs(*what_is_being_input) / 10);
                system("cls");
                input_matrix_MENU(what_matrix, *i, *j);
            } else if (key == ENTER) {
                *j += 1;
                leave_function = 1;
            } else if (key == MINUS) {
                sign *= -1;
                *what_is_being_input *= -1;
                system("cls");
                input_matrix_MENU(what_matrix, *i, *j);
            }
        } else if (abs(*what_is_being_input) == 10) {
            if (key == BACKSPACE) {
                *what_is_being_input = sign * (abs(*what_is_being_input) / 10);
                system("cls");
                input_matrix_MENU(what_matrix, *i, *j);
            } else if (key == ENTER) {
                *j += 1;
                leave_function = 1;
            } else if (key == MINUS) {
                sign *= -1;
                *what_is_being_input *= -1;
                system("cls");
                input_matrix_MENU(what_matrix, *i, *j);
            }
        }
    }
}
//заполнение матрицы
void fill_matrix(int* matrix, int dimI, int dimJ, int what_matrix) {
    int i = 0, j = 0;
    int count = 0;
    while (count != dimI * dimJ) {
        //аналог инпут парам но переписаный четко для случая -10.....10
        //по нажатию ЕНТЕР каунт++ и курсор смещается по строчке вправо
        //дошли до конца строки - строка++, курсор в начало строки
        //заполнили все элементы - ИДИТЕ НАХУЙ
        input_matrix_element(matrix + _1Dindex(i,j), what_matrix,&i, &j);
        if (j == dimJ) {
            j = 0;
            i++;
        }
        count++;
    }
}
//сброс матрицы в 0
void reset_matrix(int* matrix) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        *(matrix + i) = 0;
    }
}
void input_matrix_MENU_logic(int what_matrix) {
    int *matrix;
    int *dimI;
    int *dimJ;
    if (what_matrix == 1) {
        matrix = &matrix_1[0];
        dimI = &dimI_1;
        dimJ = &dimJ_1;
    } else {
        matrix = &matrix_2[0];
        dimI = &dimI_2;
        dimJ = &dimJ_2;
    }
    int get_key;
    num = 101;
    input_matrix_MENU(what_matrix,8,8);
    while (num != 1) {
        get_key = getch();
        switch (get_key) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                num = get_key - 48 + 100;
                system("cls");
                input_matrix_MENU(what_matrix, 8,8);
                break;
            case UP_ARROW:
                num -= 1;
                if (num == 100) {num = 105;}
                system("cls");
                input_matrix_MENU(what_matrix,8,8);
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 106) {num = 101;}
                system("cls");
                input_matrix_MENU(what_matrix,8,8);
                break;
            case ENTER:
                switch (num) {
                    case 101:
                        colorcounter = 101;
                        reset_matrix(matrix);
                        input_param(dimI, 8, 0, input_matrix_MENU, what_matrix);
                        colorcounter = 0;
                        system("cls");
                        input_matrix_MENU(what_matrix,8,8);
                        break;
                    case 102:
                        colorcounter = 102;
                        reset_matrix(matrix);
                        input_param(dimJ, 8, 0,input_matrix_MENU, what_matrix);
                        colorcounter = 0;
                        system("cls");
                        input_matrix_MENU(what_matrix,8,8);
                        break;
                    case 103:
                        randomly_fill_matrix(matrix, *dimI, *dimJ);
                        system("cls");
                        input_matrix_MENU(what_matrix,8,8);
                        break;
                    case 104:
                        fill_matrix(matrix,*dimI, *dimJ, what_matrix);
                        system("cls");
                        input_matrix_MENU(what_matrix,8,8);
                        break;
                    case 105:
                        num = 1;
                        break;
                }
                break;
            default:
                break;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int get_key;
    menu(8,8,8);
    while (num != 1000) {
        get_key = getch();
        switch (get_key) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                num = get_key - 48;
                system("cls");
                menu(8,8,8);
                break;
            case 'a':
            case 'A':
                num = 9;
                system("cls");
                menu(8,8,8);
                break;
            case 'b':
            case 'B':
                num = 10;
                system("cls");
                menu(8,8,8);
                break;
            case 'c':
            case 'C':
                num = 11;
                system("cls");
                menu(8,8,8);
                break;
            case UP_ARROW:
                num -= 1;
                if (num == 0) {num = 11;}
                system("cls");
                menu(8,8,8);
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 12) {num = 1;}
                system("cls");
                menu(8,8,8);
                break;
            case ENTER:
                switch (num) {
                    case 3:
                        transpose(&matrix_1[0]);
                        int buffer = dimI_1;
                        dimI_1 = dimJ_1;
                        dimJ_1 = buffer;
                        system("cls");
                        menu(8,8,8);
                        break;
                    case 4:
                        colorcounter = 4;
                        input_param(&lambda, 10, 1, menu, 8);
                        colorcounter = 0;
                        system("cls");
                        menu(8,8,8);
                        break;
                    case 8:
                        num = 1000;
                        break;
                    case 9:
                        system("cls");
                        input_matrix_MENU_logic(1);
                        system("cls");
                        menu(8,8,8);
                        break;
                    case 10:
                        system("cls");
                        input_matrix_MENU_logic(2);
                        system("cls");
                        menu(8,8,8);
                        break;
                    case 11:
                        matrices_switch(&matrix_1[0], &matrix_2[0]);
                        int bufferI = dimI_1, bufferJ = dimJ_1;
                        dimI_1 = dimI_2;
                        dimJ_1 = dimJ_2;
                        dimI_2 = bufferI;
                        dimJ_2 = bufferJ;
                        system("cls");
                        menu(8,8,8);
                        break;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}