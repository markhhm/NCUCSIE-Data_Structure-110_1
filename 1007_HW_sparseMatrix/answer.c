#include <stdio.h>
#include <stdlib.h>

struct term
{
    int row;
    int col;
    int value;
};
void enter(int n, int p, struct term re[])
{
    int i, j, m;
    int r = 1;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= p; j++)
        {
            scanf("%d", &m);
            if (m != 0)
            {
                re[r].row = i - 1;
                re[r].col = j - 1;
                re[r].value = m;
                r++;
            }
        }
    }
    re[r].col = 0;
    re[0].row = n;
    re[0].col = p;
    re[0].value = r - 1;
    re[r].row = re[0].row;
}

void transpose(struct term binitial[], struct term bfinal[])
{
    int *starting_pos = (int *)malloc(1000000*sizeof(int));
    int *row_terms = (int *)malloc(1000000*sizeof(int));
    int value = binitial[0].value;
    int col = binitial[0].col;
    int j;
    if (binitial[0].value > 0)
    {
        for (int i = 0; i < col; i++) //清空
        {
            row_terms[i] = 0;
        }
        for (int i = 1; i <= value; i++) //累積column非0項各有幾個
        {
            row_terms[binitial[i].col]++;
        }

        starting_pos[0] = 1;
        for (int i = 1; i <= value; i++) //每一個column的起始位置應該在哪裡
        {
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1]; //第一項的起始位置＋累積幾項
        }
        for (int i = 1; i <= value; i++)
        {

            j = starting_pos[binitial[i].col]++;
            bfinal[j].row = binitial[i].col;
            bfinal[j].col = binitial[i].row;
            bfinal[j].value = binitial[i].value;
        }
    }
}
void storesum(struct term d[], int *totald, int row, int column, int *sum)
{
    if (*sum)
    {
        if (*totald < 1000000)
        {
            d[++*totald].row = row;
            d[*totald].col = column;
            d[*totald].value = *sum;
            *sum = 0;
        }
        else
        {
            fprintf(stderr, "Numbers of terms in product exceeds %d\n", 1000000);
            exit(1);
        }
    }
}
int COMPARE(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    else
        return 0;
}
void mmult(struct term a[], struct term b[], struct term c[], struct term new_b[])
{

    int column;
    int totald = 0;
    int rows_a = a[0].row, totala = a[0].value;
    int cols_b = b[0].col, totalb = b[0].value;
    int row_begin = 1, sum = 0;
    int row = a[1].row;

    transpose(b, new_b);
    a[totala + 1].row = rows_a;
    new_b[totalb + 1].row = cols_b;
    new_b[totalb + 1].col = 0;

    for (int i = 1; i <= totala;)
    {
        column = new_b[1].row;
        for (int j = 1; j <= totalb + 1;)
        {
            if (a[i].row != row) //a讀完但b有剩下
            {
                storesum(c, &totald, row, column, &sum);
                i = row_begin;
                for (; new_b[j].row == column; j++)
                    ;
                column = new_b[j].row;
            }
            else if (new_b[j].row != column)
            {
                storesum(c, &totald, row, column, &sum);
                i = row_begin;
                column = new_b[j].row;
            }
            else
                switch (COMPARE(a[i].col, new_b[j].col))
                {
                case -1:
                    i++;
                    break;
                case 0:
                    sum += (a[i++].value * new_b[j++].value);
                    break;
                case 1:
                    j++;
                }
        }

        for (; a[i].row == row; i++)
            ;
        row_begin = i;
        row = a[i].row;
    }
    c[0].row = rows_a;
    c[0].col = cols_b;
    c[0].value = totald;
}
void show(struct term c[]) //列印
{
    printf("%d %d %d\n", c[0].row, c[0].col, c[0].value);
    for (int i = 1; i <= c[0].value; i++)
    {
        printf("%d %d %d\n", c[i].row, c[i].col, c[i].value);
    }
}
int main(void)
{
    struct term *a = (struct term *)malloc(1000000*sizeof(struct term));
    struct term *b = (struct term *)malloc(1000000*sizeof(struct term));
    struct term *c = (struct term *)malloc(1000000*sizeof(struct term));
    struct term *new_b = (struct term *)malloc(1000000*sizeof(struct term));
    int row1, row2, column1, column2;

    scanf("%d%d", &row1, &column1);
    enter(row1, column1, a);

    scanf("%d%d", &row2, &column2);
    enter(row2, column2, b);

    mmult(a, b, c, new_b);
    show(c);
    return 0;
}