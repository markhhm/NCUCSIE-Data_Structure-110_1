#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    int row;
    int col;
    int value;
};

int COMPARE(int a, int b);
void transMatrix(struct matrix a[], struct matrix b[]);
void multMatrix(struct matrix a[], struct matrix b[], struct matrix new_b[], struct matrix d[]);
void storesum(struct matrix d[], int *totald, int row, int column, int *sum);
void printMatrix(struct matrix matrix[]);
int main(void)
{
    int aRow, aCol, bRow, bCol, termA, termB, countA = 1, countB = 1, tmp;
    struct matrix *a = (struct matrix *)malloc(100000 * sizeof(struct matrix));
    struct matrix *b = (struct matrix *)malloc(100000 * sizeof(struct matrix));
    struct matrix *new_b = (struct matrix *)malloc(100000 * sizeof(struct matrix));
    struct matrix *result = (struct matrix *)malloc(100000 * sizeof(struct matrix)); //NOTE:比起原先少10倍

    scanf("%d %d", &aRow, &aCol);
    for (int i = 1; i <= aRow; i++)
    {
        for (int j = 1; j <= aCol; j++)
        {
            scanf("%d", &tmp);
            if (tmp != 0)
            {
                a[countA].row = i - 1;
                a[countA].col = j - 1;
                a[countA].value = tmp;
                countA++;
            }
        }
    }
    a[countA].col = 0;
    a[0].row = aRow;
    a[0].col = aCol;
    a[0].value = countA - 1;
    a[countA].row = aRow;

    scanf("%d %d", &bRow, &bCol);
    for (int i = 1; i <= bRow; i++)
    {
        for (int j = 1; j <= bCol; j++)
        {
            scanf("%d", &tmp);
            if (tmp != 0)
            {
                b[countB].row = i - 1;
                b[countB].col = j - 1;
                b[countB].value = tmp;
                countB++;
            }
        }
    }
    b[countB].col = 0;
    b[0].row = bRow;
    b[0].col = bCol;
    b[0].value = countB - 1;
    b[countB].row = b[0].row;

    multMatrix(a, b, new_b, result);
    printMatrix(result);

    return 0;
}

int COMPARE(int a, int b)
{
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    if (a < b)
        return -1;
}

void transMatrix(struct matrix a[], struct matrix b[])
{
    int i, j;
    int *rowTerms = (int *)malloc(100000 * sizeof(int));
    int *startingPos = (int *)malloc(100000 * sizeof(int)); //NOTE:比起原先少10倍

    if (a[0].value > 0)
    {
        for (i = 0; i < a[0].col; i++)
        {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= a[0].value; i++)
        {
            rowTerms[a[i].col]++;
        }
        startingPos[0] = 1;
        for (i = 1; i <= a[0].value; i++)
        {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }
        for (i = 1; i <= a[0].value; i++)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void multMatrix(struct matrix a[], struct matrix b[], struct matrix new_b[], struct matrix d[])
{
    int i, j, column, totald = 0;
    int row_begin = 1, row = a[1].row, sum = 0;

    int rows_a = a[0].row;
    int cols_b = b[0].col;
    int totala = a[0].value;
    int totalb = b[0].value;

    transMatrix(b, new_b);

    a[totala + 1].row = a[0].row;
    new_b[totalb + 1].row = b[0].col;
    new_b[totalb + 1].col = 0;

    for (i = 1; i <= totala;)
    {
        column = new_b[1].row;
        for (j = 1; j <= totalb + 1;)
        {
            if (a[i].row != row)
            {
                storesum(d, &totald, row, column, &sum);
                i = row_begin;
                for (; new_b[j].row == column; j++)
                    ;
                column = new_b[j].row;
            }
            else if (new_b[j].row != column)
            {
                storesum(d, &totald, row, column, &sum);
                i = row_begin;
                column = new_b[j].row;
            }
            else
            {
                switch (COMPARE(a[i].col, new_b[j].col))
                {
                case 1:
                    j++;
                    break;
                case -1:
                    i++;
                    break;
                case 0:
                    sum += (a[i++].value * new_b[j++].value);
                }
            }
        }
        for (; a[i].row == row; i++)
            ;
        row_begin = i;
        row = a[i].row;
    }
    d[0].row = rows_a;
    d[0].col = cols_b;
    d[0].value = totald;
}

void storesum(struct matrix d[], int *totald, int row, int column, int *sum)
{
    if (*sum)
    {
        d[++*totald].row = row;
        d[*totald].col = column;
        d[*totald].value = *sum;
        *sum = 0;
    }
}

void printMatrix(struct matrix matrix[])
{
    for (int i = 0; i <= matrix[0].value; i++)
    {
        printf("%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
}