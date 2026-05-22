#include <stdio.h>
#include <stdlib.h>


const  int sudoku[9][9] = { // массив для сравнения
      {3,1,5,8,2,7,9,4,6},
      {4,6,8,9,1,5,7,3,2},
      {7,2,9,3,4,6,5,1,8},
      {9,4,6,5,3,8,1,2,7},
      {5,7,1,6,9,2,4,8,3},
      {8,3,2,1,7,4,6,9,5},
      {6,9,3,2,5,1,8,7,4},
      {2,5,7,4,8,9,3,6,1},
      {1,8,4,7,6,3,2,5,9}
}; // массив для сравнения

void vis(int array[9][9], int row, int col); // отображение содержимого клетки

int intcheck(void); //проверка вводимых чисел

int main() {
    // Объявление и инициализация статического массива (3 строки, 4 столбца)

    int matrix[9][9] = { // массив для записи
       {0,0,0,8,0,0,0,0,0},
        {4,0,0,0,1,5,0,3,0},
        {0,2,9,0,4,0,5,1,8},
        {0,4,0,0,0,0,1,2,0},
        {0,0,0,6,0,2,0,0,0},
        {0,3,2,0,0,0,0,9,0},
        {6,9,3,0,5,0,8,7,0},
        {0,5,0,4,8,0,0,0,1},
        {0,0,0,0,0,3,0,0,0}
    };

    int r, c; //координаты нужной клетки
    int v; // вводимое значение эл-та
    int fail = 0, win = 0; //счётчики

    printf("Welcome to Sudoku!\nYou have 8 attempts to win\nEnter '0' to exit\n");

drawlevel: // отбражение уровня
    printf("\n    ");
    for (int i = 1; i <= 9; i++) {
        printf("%d ", i);
        if (i % 3 == 0) { printf("  "); }
    }
    printf("\n  ");
    for (int i = 1; i < 26; i++) { printf("-"); }
    printf("\n");
    for (int t = 1; t <= 9; t++) {
        printf("%d | ", t); for (int i = 1; i <= 9; i++) {
            if (i % 3 != 0) { vis(matrix, t - 1, i - 1); printf(" "); }
            else { vis(matrix, t - 1, i - 1); printf(" | "); }
        }
        if (t % 3 == 0) {
            printf("\n  ");
            for (int i = 1; i < 26; i++) { printf("-"); }
            printf("\n");
        }
        else printf("\n");
    }
enterindex: // выбор клетки 
    printf("enter number of row 1-9\n");
    r = intcheck();
    printf("enter number of column 1-9\n");
    c = intcheck();
    if (matrix[r - 1][c - 1] != 0) {
        printf("cell is full, select another\n");
        goto enterindex;
    }
    else
    {
        printf("enter value of element\n");
        v = intcheck(); //ввод значения
        if (v == (sudoku[r - 1][c - 1])) {
            printf(" right\n");
            matrix[r - 1][c - 1] = v;
            win++; if (win == 51) {
                printf("no more empty cells, you win\n");
                exit(0);
            }
            goto drawlevel;
        }
        else {
            printf("not right\n");
            fail++;
            printf("%d attempts left\n", 8 - fail);
            goto drawlevel;
            if (fail == 8) {
                printf("no more attempts, you lose\n");
                exit(0);
                goto drawlevel;
            }
        }
    }
    return 0;
}

void vis(int array[9][9], int row, int col) {
    if (array[row][col] == 0) printf(" ");
    else printf("%d", array[row][col]);
}

int intcheck(void) { //проверка вводимых чисел
    int value;
    int check;
    char puncmark;
    char yn, el;
checknumber:

    while (scanf_s("%d%c", &value, &puncmark) != 2 || puncmark != '\n') {
        printf("ERROR! Please enter integer number\n");
        while (getchar() != '\n');
        goto checknumber;
    }

    if (value < 0 || value>9) {
        printf("Please, enter correct number\n");
        goto checknumber;
    }

    if (value == 0) {
        printf("Do you want to exit? Y/N\n");
    question:
        scanf_s("%c%c", &yn, &el);
        if ((yn == 'Y') && (el == '\n')) {
            printf("As you wish\n");
            exit(0);
        }
        if ((yn == 'N') && (el == '\n'))
        {
            printf("All right, lets continue a game\n");
            goto checknumber;
        }
        else printf("Please, answer the question Y/N\n");
        while (getchar() != '\n');
        goto question;

    }


    else return value;
}