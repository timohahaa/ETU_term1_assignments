#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h> //библиотека для линукс????????

#define SIZE 22

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define BACKSPACE 8
#define TAB 9
#define MINUS 45

//array[maxI][maxJ]
//2-D array index [i][j] =>  1-D array index [i*maxI + j]
int num = 1, color_counter = 0, wall_counter = 0, food_counter = 0;
int length = 10, height = 10, score_1 = 1, score_2 = 1, lose_condition = 0;
int head_i_1, head_j_1, tail_i_1, tail_j_1;
int head_i_2, head_j_2, tail_i_2, tail_j_2;
int tail_direction_1, head_direction_1, tail_direction_2, head_direction_2; //1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
int playfield[SIZE * SIZE] = {0};
//ВНИМАНИЕ! СЕЙЧАС БУДУТ КОСТЫЛИ *****! ГОТОВЫ? ПОЕХАЛИ *****!
//первая змейка
//символы для тела: \ / - | @ это повороты, прямые части тела и голова соответственно
//переменные: head_i_1, head_j_1, head_direction_1 - координаты головы и ее направление
//tail_i_1, tail_j_1, tail_direction_1 - координаты хвоста и его направление
//вторая змейка
//символы для тела: < > _ : % это повороты, прямые части тела и голова соответственно
//переменные: head_i_2, head_j_2, head_direction_2 - координаты головы и ее направление
//tail_i_2, tail_j_2, tail_direction_2 - координаты хвоста и его направление
//КОСТЫЛИ ЗАКОНЧИЛИСЬ! СПАСИБО ЗА ВНИМАНИЕ!


//перевод индекса двумерного массива в индекс одномепного массива
int _1Dindex(int i, int j) {
    return i * SIZE + j;
}
void ConsoleColorGreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void ConsoleColorDarkGreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}
void ConsoleColorRed() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void ConsoleColorPink() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColorLightBlue() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColorWhite() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColorPaleWhite() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void ConsoleBackgroundGreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleBackgroundDefault() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void draw_whole_playfield(int length, int height, int i_cursor, int j_cursor) {
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < length + 2; j++) {
            if ((i == i_cursor) && (j == j_cursor)){
                ConsoleBackgroundGreen();
                printf("%2c", playfield[_1Dindex(i,j)]);
                ConsoleBackgroundDefault();
            } else if (playfield[_1Dindex(i,j)] == '*') {
                ConsoleColorRed();
                printf("%2c", playfield[_1Dindex(i,j)]);
                ConsoleColorWhite();
            } else if ((playfield[_1Dindex(i,j)] == '/') || (playfield[_1Dindex(i,j)] == '\\') || (playfield[_1Dindex(i,j)] == '-') || (playfield[_1Dindex(i,j)] == '|')) {
                ConsoleColorLightBlue();
                printf("%2c", 'o');
                ConsoleColorWhite();
            } else if (playfield[_1Dindex(i,j)] == '@') {
                ConsoleColorLightBlue();
                printf("%2c", 254);
                ConsoleColorWhite();
            } else if ((playfield[_1Dindex(i,j)] == '>') || (playfield[_1Dindex(i,j)] == '<') || (playfield[_1Dindex(i,j)] == '_') || (playfield[_1Dindex(i,j)] == ':')) {
                ConsoleColorPink();
                printf("%2c", 'o');
                ConsoleColorWhite();
            } else if (playfield[_1Dindex(i,j)] == '%') {
                ConsoleColorPink();
                printf("%2c", 254);
                ConsoleColorWhite();
            } else {printf("%2c", playfield[_1Dindex(i,j)]);}
            if (j == length + 1) {printf("\n");}
        }
    }
}
void clear_playfield() {
    for (int i = 0; i < SIZE * SIZE; i++) {
        if (playfield[i] != '#') {playfield[i] = ' ';}
    }
}
void draw_outer_wals(int length, int height) {
    int i, j;
    for (i = 0; i < SIZE * SIZE; i++) {playfield[i] = ' ';}
    for (i = 0; i < height + 2; i++) {
        playfield[_1Dindex(i,0)] = '#';
        playfield[_1Dindex(i,length + 1)] = '#';
    }
    for (j = 0; j < length + 2; j++) {
        playfield[_1Dindex(0,j)] = '#';
        playfield[_1Dindex(height + 1, j)] = '#';
    }
}
void DrawLeftArrow() {
    ConsoleColorGreen();
    printf("         >>> |");
    ConsoleColorWhite();
}
void DrawRightArrow() {
    ConsoleColorGreen();
    printf("| <<<");
    ConsoleColorWhite();
}
//пауза в милисекундах
void pause_for_N_seconds(int miliseconds) {
    usleep(miliseconds * 1000);
}
void first_screen() {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    int pause = 100;
    ConsoleColorGreen();
    system("cls");
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "         '_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "        -'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "       --'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "       >-'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "       `-'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "       ,-'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "       --'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "        -'_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(pause);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n"
           "\n"
           "\n"
           "\n"
           "          .-.\n"
           "         '_,))\n"
           "           // ,·-·.\n"
           "          ((./ /``\\\\\n"
           "           `·-'    ))\n"
           "                   ((\n"
           "                    ``-\n"
           "          Нажмите ENTER");
    pause_for_N_seconds(2000);
    ConsoleColorWhite();
}
void fraza_v_nachale() {
    ConsoleColorWhite();
    printf("       ~~~|<>| ");
    ConsoleColorGreen();
    printf("З");
    ConsoleColorPaleWhite();
    printf("м");
    ConsoleColorDarkGreen();
    printf("Е");
    ConsoleColorGreen();
    printf("й");
    ConsoleColorPaleWhite();
    printf("К");
    ConsoleColorDarkGreen();
    printf("а");
    ConsoleColorWhite();
    printf(" - мультиплеер |<>|~~~\n");
}
void menu() {
    fraza_v_nachale();
    printf("         Выберите команду и нажмите ENTER\n");
    printf("==================================================\n");
    if (num == 1) {
        DrawLeftArrow();
        printf("(1) Длинна поля: ");
        if (color_counter == 1) {
            ConsoleBackgroundGreen();
            printf("%3d ", length);
            ConsoleBackgroundDefault();
        } else {printf("%3d ", length);}
        DrawRightArrow();
    } else {printf("            (1) Длинна поля: ");printf(" %d ", length);}
    printf("\n");
    if (num == 2) {
        DrawLeftArrow();
        printf("(2) Ширина поля: ");
        if (color_counter == 1) {
            ConsoleBackgroundGreen();
            printf("%3d ", height);
            ConsoleBackgroundDefault();
        } else {printf("%3d ", height);}
        DrawRightArrow();
    } else {printf("            (2) Ширина поля: ");printf(" %d ", height);}
    printf("\n");
    if (num == 3) {
        DrawLeftArrow();
        printf("(3) Поставить стенки ");
        DrawRightArrow();
    } else {printf("            (3) Поставить стенки");}
    printf("\n");
    if (num == 4) {
        DrawLeftArrow();
        printf("(4) Начать игру      ");
        DrawRightArrow();
    } else {printf("            (4) Начать игру");}
    printf("\n");
    if (num == 5) {
        DrawLeftArrow();
        printf("(5) Выход            ");
        DrawRightArrow();
    } else {printf("            (5) Выход");}
    printf("\n");
    printf("==================================================\n");
    if (color_counter == 1) {printf("Длинна\\ширина поля - число от 5 до 20 :)\n");}
}
void end_screen(){
    switch (lose_condition) {
        case 1:
            printf("    ...                                           ...:^^^:.\n"
                   "  :G#&########P.       .~?5PPPY7^   :YPPPPPPPG! :B&#&&&@@@&Y   .5GBBBBBGBB: ^GB~      ~P#7   JGGBBBBBGG5.\n"
                   "  ?@@J!77777#@#.     :Y&@#P55P#@@Y  5@@5YYYYYY^ 7@@Y~^::^~!:   ~@@P????&@&. J@@~    !G@@@!  .&@#??JJY@@#\n"
                   "  P@&.     ^@@J     ?&@P^      G@@: B@&!!~^.    P@&.  ..:.     Y@@:   .&@5  G@#. .7B@G&@B   ^@@J    ^@@Y\n"
                   " .#@G      J@@^    Y@@7        B@# ^@@&##&@&P: ^@@@B##&&&B:   ^&@Y    7@@! :&@J 7#@P^~@@J   Y@@^    ?@@~\n"
                   " !@@?      G@#.   ~@@Y       .P@&~ J@@!   J@@? 5@&J?7!!~^:   .B@G     G@#. J@&J#@5^  5@&:  .#@G     G@#.\n"
                   " P@&.     :&@5    ~@@G^    :7#@B~ :#@B:.:~G@#:.&@P          :B@B^....~@@Y .#@@@5:   :&@P   ?@@7    ^@@5\n"
                   ":@@5      !@@?     7B@@#BGB&@B7   !@@@&&&&BY: :@@#YYYY55? :G&@@&#&&&&&@@B.7@&5^     7@@~:B#@&J     J@@~\n"
                   ".??:      :J?.       ^7JYJ?!:     .^^~~~^:     !YPGGGGPP7 Y@@?!!!!!!!7&@B .~:       :!^ .!!~.      :!^\n"
                   "                                                          7P?        .5P~\n"
                   "\n"
                   "\n"
                   "  .??.      .7?: :7JJJJJJ7!..YPGBG5!.      .^~!!~:.    :?7    .^!^              ..       ..   .::.            :7J5Y?^\n"
                   "  Y@@^    .?#@@~.#@&BBBB#&#^5@&JJ5&@B:  .7P&&&&&@@#Y.  G@&. .J&@BY             !&&P     !&Y 7P5YP&5         ?B@#GPB@@Y\n"
                   "  B@B   :Y&@@@B ~@@?     . :&@Y   ?@@~ 7#@B?^:..:Y@@Y :&@P.!B@&!              :&&#@!   :&&:P&!  ^@B         ?J~   7@@Y\n"
                   " :&@J :Y@&J7@@? J@@~       J@@?~7P@&? Y@@7       ^@@Y 7@@&&@@J.               P@!!@B   G@~7@5  ~BB:            ^JB@&J\n"
                   " J@&~Y@#?. 5@&: P@#.      .#@&##BP7: ?@@!       .G@&^ 5@&JY#@G~              ?@Y  G@7 J@Y :5GYYY7.          ~Y#@#P7.\n"
                   ".#@&@#?.  :&@P .&@P       7@@!..     G@&^      ~B@#~ .#@P  :G@@?            ~@B.  !@B!@G.7??JJJ?.         .5@&Y^\n"
                   "?@@#?.    ?@@! !@@?       P@#        !&@&5?77YB@&Y.  ?@@7    G@@~          :#@^    G@@&: ^~^^^^^          J@@BY5PP5J.\n"
                   "!5?.      7PJ  J@B:       ?5~         :?PB###B57.    ~5?     :YJ:          !P!     ^55!                   !PP55555PY.\n");
            break;
        case 2:
            printf("    ...                                           ...:^^^:.\n"
                   "  :G#&########P.       .~?5PPPY7^   :YPPPPPPPG! :B&#&&&@@@&Y   .5GBBBBBGBB: ^GB~      ~P#7   JGGBBBBBGG5.\n"
                   "  ?@@J!77777#@#.     :Y&@#P55P#@@Y  5@@5YYYYYY^ 7@@Y~^::^~!:   ~@@P????&@&. J@@~    !G@@@!  .&@#??JJY@@#\n"
                   "  P@&.     ^@@J     ?&@P^      G@@: B@&!!~^.    P@&.  ..:.     Y@@:   .&@5  G@#. .7B@G&@B   ^@@J    ^@@Y\n"
                   " .#@G      J@@^    Y@@7        B@# ^@@&##&@&P: ^@@@B##&&&B:   ^&@Y    7@@! :&@J 7#@P^~@@J   Y@@^    ?@@~\n"
                   " !@@?      G@#.   ~@@Y       .P@&~ J@@!   J@@? 5@&J?7!!~^:   .B@G     G@#. J@&J#@5^  5@&:  .#@G     G@#.\n"
                   " P@&.     :&@5    ~@@G^    :7#@B~ :#@B:.:~G@#:.&@P          :B@B^....~@@Y .#@@@5:   :&@P   ?@@7    ^@@5\n"
                   ":@@5      !@@?     7B@@#BGB&@B7   !@@@&&&&BY: :@@#YYYY55? :G&@@&#&&&&&@@B.7@&5^     7@@~:B#@&J     J@@~\n"
                   ".??:      :J?.       ^7JYJ?!:     .^^~~~^:     !YPGGGGPP7 Y@@?!!!!!!!7&@B .~:       :!^ .!!~.      :!^\n"
                   "                                                          7P?        .5P~\n"
                   "\n"
                   "\n"
                   "  :??.      .?J: :?JYYYYJ?!.:5GBBB57.      .^!!!~^.    :J?.   .~7~              ...      ..   :^^.            :?5~\n"
                   "  Y@@^    :J#@@~.&@&GGGGB&#^5@&??Y#@#:  .7G&&&&&@@#Y.  G@&. .Y&@BJ             !&&G     7@Y 7G5J5&P         JB&@@!\n"
                   "  B@B   :Y&@@@B ~@@7     . :&@J   ?@@~ ?&@B7^...:J@@Y :&@P.7#@#!              :&&#@7   :&#:P&!  ^@B        .JJ#@B\n"
                   " ^@@? ^5@&?7@@? J@@~       J@@?!?G@&7 5@@7       ~@@Y 7@@&&@@J.               G@~~@B   G@~7@5 .~#B:          :@@?\n"
                   " J@&!5@#7. 5@&: P@#.      .#@&##B57. J@@!       .G@&: 5@&?J#@B!              J@Y  G@7 Y@J :5PYYY!            J@&:\n"
                   ".#@&@#7   :&@P :&@P       7@@~       G@&^      ~B@#^ .&@P  .P@@J            ~@G   ~@B7@G 7J?JJJ?.            B@P\n"
                   "J@@#7     J@@! 7@@7       G@B        ~#@@PJ??YB@&J.  ?@@!    G@@!          :&@^    P@@&: ^^^^^^^          !5P@@#Y: \n"
                   "~Y7.      7P?  J@B.       7Y~         .75G##BGY!.    ~Y7     :YJ:          !5!     ^YY~                   755YYYJ.\n");
            break;
        case 3:
            printf("     :!!:             .~^    .^^             .^^.   .^^          :~.                                .:::^^^\n"
                   "    !&@@5            7#@@7  7&@@?           !#@@P  7&@@Y       .P@@B:   JGB5.                  .~?PB#&&@@@@Y.\n"
                   "    5@@@J           7@@@#:  P@@@J         !G@@@@P .#@@@5       7@@@#.  ?@@@@:               .~Y#@@@@@@&@@@@G.\n"
                   "   ^&@@@~          .#@@@Y  .#@@@7       7B@@@@@@! ^@@@#:       Y@@@J   B@@@#               !B@@@@GJ7~^:B@@@?\n"
                   "   ?@@@G.          !@@@&~  ~@@@&^     !G@@@&@@@&. 5@@@5       .B@@@~  .#@@@P              ?@@@&Y^     ~&@@@~\n"
                   "   5@@@7       ..::5@@@P   J@@@P    !G@@@G!G@@@5 :@@@@?       ~@@@&:  :&@@@#PPP55Y7:     ^@@@@7       Y@@@&:\n"
                   "  .B@@#7!?J5PPB#&&&@@@@?   G@@@~  ~G@@@G! :&@@@^ :&@@@G^.....:P@@@Y   ~@@@@@@@@@@@@@P:   ^@@@@#J~:... G@@@B.\n"
                   "  ?@@@@@@@@@@@@@&&&@@@#:  ~@@@B :5@@@G!   ?@@@#.  7@@@@@&####&@@@@^   J@@@B~~~!?5@@@@G    ~B@@@@@&####@@@@J\n"
                   "  P@@@#GPPY?7!^::.5@@@Y   5@@@55&@@G~     B@@@J    ^YG#&@@@@@@@@@#.  :&@@@?      5@@@#.     ^J&@@@@@@@@@@@^\n"
                   " ^&@@B.          .B@@@!  :&@@@&@@#7      ^@@@&:       .:^^^^^B@@@G   7@@@#:      G@@@P    :7P#@@@@&B5B@@@&.\n"
                   " P@@@J           ~@@@&^  ?@@@@@#?.       Y@@@B              .&@@@!  .B@@@5:^^^~?B@@@B: :?G&@@@#G?^:  G@@@G\n"
                   "^&@@#:           J@@@#. :&@@@&Y.        :&@@@J              ~@@@#   ?@@@@@@@@@@@@@#Y. J&@@@#5!.     .&@@@7\n"
                   "?@@@P            Y@@@J  :G&#5^          :#@@P.              ~#&B7   ~B####&&##BPY!.   5&#P7.        .G&#Y.\n"
                   "!BB5^            .!7~     ..             :~^                 ..       ........         ..             ..\n");
            break;
    }
    printf("\n                                      Нажмите ENTER для выхода");
    while (getch() != ENTER) {getch();}
}
//ввод НЕ ОТРИЦАТЕЛЬНОГО параметра
void input_param(int* whatIsBeingInput, int upper_bound, int lower_bound, int can_be_zero) {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    int key, leave_function = 0;
    color_counter = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    menu();
    while (leave_function != 1) {
        if (*whatIsBeingInput < upper_bound) {
            key = getch();
            if ((key >= 48) && (key <= 57)) {
                *whatIsBeingInput = *whatIsBeingInput * 10 + (key - 48);
                if (*whatIsBeingInput > upper_bound) {*whatIsBeingInput /= 10;}
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                menu();
            } else if (key == BACKSPACE) {
                *whatIsBeingInput /= 10;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                menu();
            } else if (key == ENTER) {
                if (can_be_zero) {
                    if (*whatIsBeingInput >= lower_bound) {leave_function = 1;color_counter = 0;}
                } else if ((*whatIsBeingInput != 0) && (*whatIsBeingInput >= lower_bound)) {leave_function = 1; color_counter = 0;}
            }
        } else  if (*whatIsBeingInput == upper_bound) {
            key = getch();
            if (key == BACKSPACE) {
                *whatIsBeingInput /= 10;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                menu();
            } else if (key == ENTER) {leave_function = 1; color_counter = 0;}
        }
    }
}
//редактор стенок
void wall_editor_menu(int i_cursor, int j_cursor) {
    ConsoleColorWhite();
    printf("Всего можно поставить 5 стенок.\nВыберете, куда поставить стенку с помощью стрелок вверх/вниз/вправо/влево.\nЧтобы поставить стенку, нажмите ENTER.\nСтавьте стенки с умом! Мы не несем ответственность за глупо поставленные стенки!\n\n");
    draw_whole_playfield(length, height, i_cursor, j_cursor);
    printf("\nЧтобы вернуться в главное меню, нажмите TAB.\nЧтобы убрать стенку нажмите BACKSPACE.");
}
void wall_editor() {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    int i = 1, j = 1;
    wall_editor_menu(i, j);
    int leave_function = 0, key;
    while (leave_function != 1) {
        key = getch();
        if (key == UP_ARROW) {
            i--;
            if (i == 0) {i = 1;}
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            wall_editor_menu(i, j);
        }
        if (key == DOWN_ARROW) {
            i++;
            if (i == height + 1) {i = height;}
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            wall_editor_menu(i, j);
        }
        if (key == LEFT_ARROW) {
            j--;
            if (j == 0) {j = 1;}
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            wall_editor_menu(i, j);
        }
        if (key == RIGHT_ARROW) {
            j++;
            if (j == length + 1) {j = length;}
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            wall_editor_menu(i, j);
        }
        if (key == TAB) {leave_function = 1;}
        if (key == ENTER) {
            if ((wall_counter != 5) && playfield[_1Dindex(i,j)] != '#') {
                playfield[_1Dindex(i,j)] = '#';
                wall_counter++;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                wall_editor_menu(i, j);
            }
        }
        if (key == BACKSPACE) {
            if (playfield[_1Dindex(i,j)] == '#') {
                playfield[_1Dindex(i,j)] = ' ';
                wall_counter--;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                wall_editor_menu(i, j);
            }
        }
    }
}
//генерация еды
void get_food() {
    srand(time(NULL));
    int food_i, food_j, maxfood = 4;
    if (score_1 + score_2 == length * height - 1 - 4) { maxfood = 4;}
    if (score_1 + score_2  == length * height - 1 - 3) { maxfood = 3;}
    if (score_1 + score_2  == length * height - 1 - 2) { maxfood = 2;}
    if (score_1 + score_2  == length * height - 1 - 1) { maxfood = 1;}
    if (score_1 + score_2  == length * height - 1 - 0) { maxfood = 0; lose_condition = 3;}
    food_i = 1 + rand() % (height);
    food_j = 1 + rand() % (length);
    while (food_counter != maxfood) {
        while (playfield[_1Dindex(food_i, food_j)] != ' ') {
            food_i = 1 + rand() % (height);
            food_j = 1 + rand() % (length);
        }
        playfield[_1Dindex(food_i, food_j)] = '*';
        food_counter++;
    }
}
//проверка, была ли сьедена еда :)
int check_if_food_was_eaten(int i, int j, int* score) {
    if (playfield[_1Dindex(i,j)] == '*') {
        food_counter--;
        *score += 1;
        return 1;
    } else {return 0;}
}
//обновление хвоста и головы
void get_tail(int* tail_direction, int* tail_i, int* tail_j) {
    switch (*tail_direction) {//1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
        case 1:
            playfield[_1Dindex(*tail_i, *tail_j)] = ' ';
            if (playfield[_1Dindex(*tail_i - 1, *tail_j)] == '/') {
                *tail_direction = 4;
                *tail_i -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '-';
            } else if (playfield[_1Dindex(*tail_i - 1, *tail_j)] == '\\') {
                *tail_direction = 3;
                *tail_i -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '-';
            } else if (playfield[_1Dindex(*tail_i - 1, *tail_j)] == '>') {
                *tail_direction = 4;
                *tail_i -=1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '_';
            } else if (playfield[_1Dindex(*tail_i - 1, *tail_j)] == '<') {
                *tail_direction = 3;
                *tail_i -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '_';
            } else {*tail_i -= 1;}
            break;
        case 2:
            playfield[_1Dindex(*tail_i, *tail_j)] = ' ';
            if (playfield[_1Dindex(*tail_i + 1, *tail_j)] == '/') {
                *tail_direction = 3;
                *tail_i += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '-';
            } else if (playfield[_1Dindex(*tail_i + 1, *tail_j)] == '\\') {
                *tail_direction = 4;
                *tail_i += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '-';
            } else if (playfield[_1Dindex(*tail_i + 1, *tail_j)] == '>') {
                *tail_direction = 3;
                *tail_i +=1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '_';
            } else if (playfield[_1Dindex(*tail_i + 1, *tail_j)] == '<') {
                *tail_direction = 4;
                *tail_i += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '_';
            } else {*tail_i += 1;}
            break;
        case 3:
            playfield[_1Dindex(*tail_i, *tail_j)] = ' ';
            if (playfield[_1Dindex(*tail_i, *tail_j - 1)] == '/') {
                *tail_direction = 2;
                *tail_j -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '|';
            } else if (playfield[_1Dindex(*tail_i, *tail_j - 1)] == '\\') {
                *tail_direction = 1;
                *tail_j -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '|';
            } else if (playfield[_1Dindex(*tail_i, *tail_j - 1)] == '>') {
                *tail_direction = 2;
                *tail_j -=1;
                playfield[_1Dindex(*tail_i, *tail_j)] = ':';
            } else if (playfield[_1Dindex(*tail_i, *tail_j - 1)] == '<') {
                *tail_direction = 1;
                *tail_j -= 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = ':';
            } else {*tail_j -= 1;}
            break;
        case 4:
            playfield[_1Dindex(*tail_i, *tail_j)] = ' ';
            if (playfield[_1Dindex(*tail_i, *tail_j + 1)] == '/') {
                *tail_direction = 1;
                *tail_j += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '|';
            } else if (playfield[_1Dindex(*tail_i, *tail_j + 1)] == '\\') {
                *tail_direction = 2;
                *tail_j += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = '|';
            } else if (playfield[_1Dindex(*tail_i, *tail_j + 1)] == '>') {
                *tail_direction = 1;
                *tail_j +=1;
                playfield[_1Dindex(*tail_i, *tail_j)] = ':';
            } else if (playfield[_1Dindex(*tail_i, *tail_j + 1)] == '<') {
                *tail_direction = 2;
                *tail_j += 1;
                playfield[_1Dindex(*tail_i, *tail_j)] = ':';
            } else {*tail_j += 1;}
            break;
    }
}
void get_head(int new_direction_1, int new_direction_2) {
    if (new_direction_1) {
        switch (new_direction_1) {
            case 1://1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
                if (head_direction_1 == 3) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '\\';
                    head_direction_1 = new_direction_1;
                } else if (head_direction_1 == 4) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '/';
                    head_direction_1 = new_direction_1;
                } else {playfield[_1Dindex(head_i_1, head_j_1)] = '|';}
                break;
            case 2:
                if (head_direction_1 == 3) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '/';
                    head_direction_1 = new_direction_1;
                } else if (head_direction_1 == 4) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '\\';
                    head_direction_1 = new_direction_1;
                } else {playfield[_1Dindex(head_i_1, head_j_1)] = '|';}
                break;
            case 3:
                if (head_direction_1 == 1) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '\\';
                    head_direction_1 = new_direction_1;
                } else if (head_direction_1 == 2) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '/';
                    head_direction_1 = new_direction_1;
                } else {playfield[_1Dindex(head_i_1, head_j_1)] = '-';}
                break;
            case 4:
                if (head_direction_1 == 1) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '/';
                    head_direction_1 = new_direction_1;
                } else if (head_direction_1 == 2) {
                    playfield[_1Dindex(head_i_1, head_j_1)] = '\\';
                    head_direction_1 = new_direction_1;
                } else {playfield[_1Dindex(head_i_1, head_j_1)] = '-';}
                break;
        }
    } else {
        switch (new_direction_2) {
            case 1://1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
                if (head_direction_2 == 3) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '<';
                    head_direction_2 = new_direction_2;
                } else if (head_direction_2 == 4) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '>';
                    head_direction_2 = new_direction_2;
                } else {playfield[_1Dindex(head_i_2, head_j_2)] = ':';}
                break;
            case 2:
                if (head_direction_2 == 3) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '>';
                    head_direction_2 = new_direction_2;
                } else if (head_direction_2 == 4) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '<';
                    head_direction_2 = new_direction_2;
                } else {playfield[_1Dindex(head_i_2, head_j_2)] = ':';}
                break;
            case 3:
                if (head_direction_2 == 1) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '<';
                    head_direction_2 = new_direction_2;
                } else if (head_direction_2 == 2) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '>';
                    head_direction_2 = new_direction_2;
                } else {playfield[_1Dindex(head_i_2, head_j_2)] = '_';}
                break;
            case 4:
                if (head_direction_2 == 1) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '>';
                    head_direction_2 = new_direction_2;
                } else if (head_direction_2 == 2) {
                    playfield[_1Dindex(head_i_2, head_j_2)] = '<';
                    head_direction_2= new_direction_2;
                } else {playfield[_1Dindex(head_i_2, head_j_2)] = '_';}
                break;
        }
    }
}
void calc_lose_condition(int i, int j, int witch_snake) {
    if ((playfield[_1Dindex(i, j)] == '@') || (playfield[_1Dindex(i, j)] == '%')) {
        lose_condition = 3;
    } else {if (witch_snake == 1) {lose_condition = 1;} else {lose_condition = 2;}}
}
void print_scores() {
    printf("Первый игрок: ");
    ConsoleColorLightBlue();
    printf("%d", score_1);
    ConsoleColorWhite();
    printf(" очков\n");
    printf("Второй игрок: ");
    ConsoleColorPink();
    printf("%d", score_2);
    ConsoleColorWhite();
    printf(" очков\n");
}
//движение змейки по кадрам
void move_snake(int new_direction_1, int new_direction_2) {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    switch (new_direction_1) { //1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
        case 1: //1 - вверх
            if (new_direction_1 != head_direction_1) {get_head(new_direction_1, 0);} else { playfield[_1Dindex(head_i_1, head_j_1)] = '|';}
            head_i_1--;
            if (playfield[_1Dindex(head_i_1, head_j_1)] != ' ') {
                if (check_if_food_was_eaten(head_i_1, head_j_1, &score_1)) {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_food();} else {calc_lose_condition(head_i_1, head_j_1, 1);}
            } else {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_tail(&tail_direction_1, &tail_i_1, &tail_j_1);}
            break;
        case 2: //2 - вниз
            if (new_direction_1 != head_direction_1) {get_head(new_direction_1, 0);} else { playfield[_1Dindex(head_i_1, head_j_1)] = '|';}
            head_i_1++;
            if (playfield[_1Dindex(head_i_1, head_j_1)] != ' ') {
                if (check_if_food_was_eaten(head_i_1, head_j_1, &score_1)) {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_food();} else {calc_lose_condition(head_i_1, head_j_1, 1);}
            } else {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_tail(&tail_direction_1, &tail_i_1, &tail_j_1);}
            break;
        case 3: //3 - влево
            if (new_direction_1 != head_direction_1) {get_head(new_direction_1, 0);} else {playfield[_1Dindex(head_i_1, head_j_1)] = '-';}
            head_j_1--;
            if (playfield[_1Dindex(head_i_1, head_j_1)] != ' ') {
                if (check_if_food_was_eaten(head_i_1, head_j_1, &score_1)) {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_food();} else {calc_lose_condition(head_i_1, head_j_1, 1);}
            } else {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_tail(&tail_direction_1, &tail_i_1, &tail_j_1);}
            break;
        case 4: //4 - вправо
            if (new_direction_1 != head_direction_1) {get_head(new_direction_1, 0);} else {playfield[_1Dindex(head_i_1, head_j_1)] = '-';}
            head_j_1++;
            if (playfield[_1Dindex(head_i_1, head_j_1)] != ' ') {
                if (check_if_food_was_eaten(head_i_1, head_j_1, &score_1)) {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_food();} else {calc_lose_condition(head_i_1, head_j_1, 1);}
            } else {playfield[_1Dindex(head_i_1, head_j_1)] = '@'; get_tail(&tail_direction_1, &tail_i_1, &tail_j_1);}
            break;
    }
    switch (new_direction_2) { //1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
        case 1: //1 - вверх
            if (new_direction_2 != head_direction_2) {get_head(0, new_direction_2);} else { playfield[_1Dindex(head_i_2, head_j_2)] = ':';}
            head_i_2--;
            if (playfield[_1Dindex(head_i_2, head_j_2)] != ' ') {
                if (check_if_food_was_eaten(head_i_2, head_j_2, &score_2)) { playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_food();} else {calc_lose_condition(head_i_2, head_j_2, 2);}
            } else {playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_tail(&tail_direction_2, &tail_i_2, &tail_j_2);}
            break;
        case 2: //2 - вниз
            if (new_direction_2 != head_direction_2) {get_head(0, new_direction_2);} else { playfield[_1Dindex(head_i_2, head_j_2)] = ':';}
            head_i_2++;
            if (playfield[_1Dindex(head_i_2, head_j_2)] != ' ') {
                if (check_if_food_was_eaten(head_i_2, head_j_2, &score_2)) { playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_food();} else {calc_lose_condition(head_i_2, head_j_2, 2);}
            } else {playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_tail(&tail_direction_2, &tail_i_2, &tail_j_2);}
            break;
        case 3: //3 - влево
            if (new_direction_2 != head_direction_2) {get_head(0, new_direction_2);} else { playfield[_1Dindex(head_i_2, head_j_2)] = '_';}
            head_j_2--;
            if (playfield[_1Dindex(head_i_2, head_j_2)] != ' ') {
                if (check_if_food_was_eaten(head_i_2, head_j_2, &score_2)) { playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_food();} else {calc_lose_condition(head_i_2, head_j_2, 2);}
            } else {playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_tail(&tail_direction_2, &tail_i_2, &tail_j_2);}
            break;
        case 4: //4 - вправо
            if (new_direction_2 != head_direction_2) {get_head(0, new_direction_2);} else { playfield[_1Dindex(head_i_2, head_j_2)] = '_';}
            head_j_2++;
            if (playfield[_1Dindex(head_i_2, head_j_2)] != ' ') {
                if (check_if_food_was_eaten(head_i_2, head_j_2, &score_2)) { playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_food();} else {calc_lose_condition(head_i_2, head_j_2, 2);}
            } else {playfield[_1Dindex(head_i_2, head_j_2)] = '%'; get_tail(&tail_direction_2, &tail_i_2, &tail_j_2);}
            break;
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    draw_whole_playfield(length, height, -1, -1);
    print_scores();
}
void get_new_direction(int* new_direction_1, int* new_direction_2, int key) {
    switch (key) { //1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
        case UP_ARROW:
            *new_direction_1 = 1;
            break;
        case DOWN_ARROW:
            *new_direction_1 = 2;
            break;
        case LEFT_ARROW:
            *new_direction_1 = 3;
            break;
        case RIGHT_ARROW:
            *new_direction_1 = 4;
            break;
        case 'w':
        case 'W':
            *new_direction_2 = 1;
            break;
        case 's':
        case 'S':
            *new_direction_2 = 2;
            break;
        case 'a':
        case 'A':
            *new_direction_2 = 3;
            break;
        case 'd':
        case 'D':
            *new_direction_2 = 4;
            break;
        default:
            break;
    }
}
//начальное положение змеек
void set_head_tail_props() {
    tail_i_1 = head_i_1;
    tail_j_1 = head_j_1 - 1;
    head_i_2 = tail_i_1 + 1;
    head_j_2 = tail_j_1;
    tail_i_2 = head_i_2;
    tail_j_2 = head_j_1;
}
void get_start_pos() {
    srand(time(NULL));
    head_i_1 = height / 2 + 1;
    head_j_1 = length / 2 + 1;
    set_head_tail_props();
    head_direction_1  = tail_direction_1 = 4;
    head_direction_2 = tail_direction_2 = 3;
    while ((playfield[_1Dindex(head_i_1, head_j_1)] != ' ') || (playfield[_1Dindex(tail_i_1, tail_j_1)] != ' ') || (playfield[_1Dindex(head_i_2, head_j_2)] != ' ') || (playfield[_1Dindex(tail_i_2, tail_j_2)] != ' ')) {
        head_i_1 = 1 + rand() % (height);
        head_j_1 = 1 + rand() % (length);
        set_head_tail_props();
    }
    playfield[_1Dindex(head_i_1, head_j_1)] = '@';
    playfield[_1Dindex(tail_i_1, tail_j_1)] = '-';
    playfield[_1Dindex(head_i_2, head_j_2)] = '%';
    playfield[_1Dindex(tail_i_2, tail_j_2)] = '_';
    head_direction_1  = tail_direction_1 = 4;
    head_direction_2 = tail_direction_2 = 3;
}
//логика игры
void gameplay(int head_dir_1, int head_dir_2) {
    int new_direction_1 = head_dir_1;
    int new_direction_2 = head_dir_2;
    int leave_function = 0;
    draw_whole_playfield(length, height, -1, -1);
    print_scores();
    pause_for_N_seconds(1000);
    while (leave_function != 1) {
        //pause_for_N_seconds(250);
        if (kbhit()) { get_new_direction(&new_direction_1, &new_direction_2, getch());}
        move_snake(new_direction_1, new_direction_2);
        pause_for_N_seconds(250);
        if (lose_condition) {leave_function = 1;}
        if (kbhit()) { get_new_direction(&new_direction_1, &new_direction_2, getch());}
        pause_for_N_seconds(250);
        if (kbhit()) { get_new_direction(&new_direction_1, &new_direction_2, getch());}
        pause_for_N_seconds(250);
    }
    system("cls");
    end_screen();
}

int main() {
    int get_key = 8;
    first_screen();
    while (get_key != ENTER) {
        first_screen();
        if(kbhit()) {get_key = getch();}
    }
    draw_outer_wals(length, height);
    system("cls");
    menu();
    while (num != 1000) {
        get_key = getch();
        switch (get_key) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                num = get_key - 48;
                system("cls");
                menu();
                break;
            case UP_ARROW:
                num -= 1;
                if (num == 0) { num = 5; }
                system("cls");
                menu();
                break;
            case DOWN_ARROW:
                num += 1;
                if (num == 6) { num = 1; }
                system("cls");
                menu();
                break;
            case ENTER:
                switch (num) {
                    case 1:
                        input_param(&length, 20, 5, 0);
                        wall_counter = 0;
                        draw_outer_wals(length, height);
                        system("cls");
                        menu();
                        break;
                    case 2:
                        input_param(&height, 20, 5, 0);
                        wall_counter = 0;
                        draw_outer_wals(length, height);
                        system("cls");
                        menu();
                        break;
                    case 3:
                        system("cls");
                        wall_editor();
                        system("cls");
                        menu();
                        break;
                    case 4:
                        system("cls");
                        get_start_pos();
                        get_food();
                        gameplay(head_direction_1, head_direction_2);
                        clear_playfield();
                        score_1 = score_2 = 1;
                        food_counter = 0;
                        lose_condition = 0;
                        system("cls");
                        menu();
                        break;
                    case 5:
                        num = 1000;
                        break;
                }
                break;
        }
    }
    return 0;
}