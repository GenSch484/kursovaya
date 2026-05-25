#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ROWS 9
#define COLS 9 
#define FAILS 8 

const  int sudoku[ROWS][COLS] = { // массив для сравнения
    {3,1,5,8,2,7,9,4,6},
     {4,6,8,9,1,5,7,0,2},
     {7,2,9,3,4,6,5,1,8},
     {9,4,6,5,3,8,1,2,7},
     {5,7,1,6,0,2,4,8,3},
     {8,3,2,1,7,4,6,9,5},
     {6,9,3,2,5,1,8,7,4},
     {2,5,7,4,8,9,3,6,1},
     {1,8,4,7,6,3,2,5,9} };

const int level[ROWS][COLS] = { //"уровень"
    {0,0,0,8,0,0,0,0,0},
    {4,0,0,0,1,5,0,3,0},
    {0,2,9,0,4,0,5,1,8},
    {0,4,0,0,0,0,1,2,0},
    {0,0,0,6,0,2,0,0,0},
    {0,3,2,0,0,0,0,9,0},
    {6,9,3,0,5,0,8,7,0},
    {0,5,0,4,8,0,0,0,1},
    {0,0,0,0,0,3,0,0,0} };
//прототипы используемых в дальнейшем функций:
void vis(int array[ROWS][COLS], int row, int col); // отображение содержимого клетки
void drawlevel(int array[ROWS][COLS], int rows, int colls);//отрисовка уровня
int checkvalue(void); //проверка вводимых чисел
void exitgame(); // выход
int countingzeroes(int array[ROWS][COLS], int rows, int colls); // подсчёт нулей в массиве
void redraw(int array[ROWS][COLS], int rows, int colls); // перезапись массива
void replay(int array[ROWS][COLS], int rows, int colls, int *value, int *value1); // перезапуск уровня

int main() {

    int r, c; //координаты нужной клетки
    int v = 11; // вводимое значение эл-та
    int fail = 0; //счётчик неудачных попыток
    int replaystatus = 0;//переменная, по которой происходит перезапуск уровня

    int matrix[ROWS][COLS]; // массив для записи
    redraw(matrix, ROWS, COLS);

    printf("Welcome to Sudoku!\nYou have 8 attempts to win\nEnter '0' to replay\nEnter '10' to exit\n");

    do {
    drwlvl:
        drawlevel(matrix, ROWS, COLS);
        do {
            do {
                printf("Enter number of row 1-9\n");
                r = checkvalue();
                if (r == 10) { exitgame(); }
                if (r == 0) {
                    (replay(matrix, ROWS, COLS, &fail, &replaystatus));
                    if (replaystatus == 1) { goto drwlvl; }
                }
            } while (r == 10 || r == 0);
            do {
                printf("Enter number of column 1-9\n");
                c = checkvalue();
                if (c == 10) { exitgame(); }
                if (c == 0) {
                    (replay(matrix, ROWS, COLS, &fail, &replaystatus));
                    if (replaystatus == 1) { goto drwlvl; }
                }
            } while (c == 10 || c == 0);
            if (matrix[r - 1][c - 1] != 0) { printf("Cell is full, select another\n"); }
        } while (matrix[r - 1][c - 1] != 0);
        do {
            printf("Enter value of element\n");
            v = checkvalue();
            if (v == 10) { exitgame(); }
            if (v == 0) {
                (replay(matrix, ROWS, COLS, &fail, &replaystatus));
                if (replaystatus == 1) { goto drwlvl; }
            }
        } while (v == 10 || v == 0);

        if (v == (sudoku[r - 1][c - 1])) {
            printf(" right\n");
            matrix[r - 1][c - 1] = v;
        }
        else {
            printf("not right\n");
            fail++;
            printf("%d attempts left\n", FAILS - fail);
            if (fail == FAILS)
            {
                printf("No more attempts, you lose\n");
                exit(0);
            }
        }
    } while (countingzeroes(matrix, ROWS, COLS) > 0);
    printf("You filled all cells correctly.You Win!\n");
    return 0;
}

void vis(int array[ROWS][COLS], int row, int col) {
    if (array[row][col] == 0) printf(" ");
    else printf("%d", array[row][col]);
}

int checkvalue(void) { //проверка вводимых чисел

    int value; //проеверяемое значение 
    char punc; //знак после 1 символа

    while (1) {
        if (scanf("%d%c", &value, &punc) == 2 && punc == '\n') {
            if ((value >= 0) && (value <= 10)) { return value; }
            else {
                printf("Please, enter correct number\n");
            }
        }
        else {
            printf("Please, enter integer number\n");
            while (getchar() != '\n');
        }
    }
}

void drawlevel(int array[ROWS][COLS], int rows, int colls) {

    printf("\n    ");
    for (int i = 1; i <= rows; i++) {
        printf("%d ", i);
        if (i % 3 == 0) { printf("  "); }
    }
    printf("\n  ");
    for (int i = 1; i < 26; i++) { printf("-"); }
    printf("\n");
    for (int t = 1; t <= colls; t++) {
        printf("%d | ", t); for (int i = 1; i <= rows; i++) {
            if (i % 3 != 0) { vis(array, t - 1, i - 1); printf(" "); }
            else { vis(array, t - 1, i - 1); printf(" | "); }
        }
        if (t % 3 == 0) {
            printf("\n  ");
            for (int i = 1; i < 26; i++) { printf("-"); }
            printf("\n");
        }
        else printf("\n");
    }
}

void exitgame() {

    char yn, el; //переменные для проверки ввода

    printf("Do you want to exit? Y/N\n");
    while ((scanf("%c%c", &yn, &el) != 'Y\n') || (scanf("%c%c", &yn, &el) != 'Y\n')) {
        if ((yn == 'Y') && (el == '\n')) {
            printf("As you wish\n");
            exit(0);
        }
        if ((yn == 'N') && (el == '\n'))
        {
            printf("All right, lets continue a game\n");
            break;
        }
        else {
            printf("Please, answer the question Y/N\n");
            while (getchar() != '\n');
        }
    }
}


int countingzeroes(int array[ROWS][COLS], int rows, int colls) {

    int zeroes = 0; //количество нулей

    for (int t = 0; t < colls; t++) {
        for (int i = 0; i < rows; i++) {
            if (array[t][i] == 0)
                zeroes++;
        }
    }
    return zeroes;
}

void redraw(int array[ROWS][COLS], int rows, int colls) {
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < colls; i++)
            array[i][j] = level[i][j];
    }
}

void replay(int array[ROWS][COLS], int rows, int cols, int* variable, int* variable1) {

    char yn, el; //переменные для проверки ввода

    printf("Do you want to replay the level? Y/N\n");
    while ((scanf("%c%c", &yn, &el) != 'Y\n') || (scanf("%c%c", &yn, &el) != 'Y\n')) {
        if ((yn == 'Y') && (el == '\n')) {
            printf("OK, here we go again\n");
            redraw(array, rows, cols);
            *variable = 0;
            *variable1 = 1;
            return;
        }

        if ((yn == 'N') && (el == '\n'))
        {
            printf("All right, lets continue a game\n");
            *variable1 = 0;
            return;
        }
        else {
            printf("Please, answer the question Y/N\n");
            while (getchar() != '\n');

        }
    }
}