#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int col;
    int row;
    int val;
} term;

//function prototype
void transpose(term *, term *);
void mmult(term *, term *, term *);
void storesum(int, int, int *, int *, term *);
int COMPARE(int, int);
void show(term *m);

int main(void)
{
    int i, j, aRow, aCol, bRow, bCol;
    int iSave = 0, iRnum = 0;
    scanf("%d", &aRow);
    scanf("%d", &aCol);
    term *a = (term *)malloc(sizeof(term) * (aRow * aCol + 1));
    a[0].val = aRow * aCol;
    a[0].row = aRow;
    a[0].col = aCol;

    for (i = 0; i < aRow; i++)
    {
        for (j = 0; j < aCol; j++)
        {
            iSave++;
            scanf("%d", &a[iSave].val);
            if (a[iSave].val != 0)
            {
                iRnum++;
            }
            a[iSave].row = i;
            a[iSave].col = j;
        }
    }
    scanf("%d", &bRow);
    scanf("%d", &bCol);
    term *b = (term *)malloc(sizeof(term) * (bRow * bCol + 1));
    b[0].val = bRow * bCol;
    b[0].row = bRow;
    b[0].col = bCol;
    iSave = 0;
    for (i = 0; i < bRow; i++)
    {
        for (j = 0; j < bCol; j++)
        {
            iSave++;
            scanf("%d", &b[iSave].val);
            if (b[iSave].val != 0)
            {
                iRnum++;
            }
            b[iSave].row = i;
            b[iSave].col = j;
        }
    }

    //term *r = (term *)malloc(sizeof(term) * (iRnum + 1));
    
    term *r = (term *)malloc(sizeof(term) * 250000);
    
    mmult(a, b, r);
    for (i = 0; i <= r[0].val; i++)
    {
        printf("%d %d %d\n", r[i].row, r[i].col, r[i].val);
    }
    
    printf("----show a----\n");
    show(a);
    printf("\n----show b----\n");
    show(b);
    printf("\n--------\n");
    
    free(a);
    free(b);
    free(r);
    return 0;
} //end main

//function to transpose
/*
	to transpose b
	1.scan how many numbers in a column
	2.store numbers in order
*/

void transpose(term *o, term *t) //o denotes original b matrix; t denotes transposed b
{
    int i, j;
    if (o[0].val > 0) //make sure nonzero matrix
    {
        int count[o[0].col]; //initialize count to 0 o[0].col
        int start[o[0].col];
        //count how many numbers in a column
        for (i = 0; i < o[0].col; i++)
        {
            count[i] = 0;
            start[i] = 0;
        }
        for (i = 1; i < (o[0].col * o[0].row + 1); i++)
        {
            count[o[i].col]++;
        }
        //find where to start
        start[0] = 1;
        for (i = 1; i <= o[0].col; i++)
        {
            //when you put all the col before you into right place then u can start
            start[i] = start[i - 1] + count[i - 1];
        }
        //how many space in t[] were occupied
        for (i = 1; i < (o[0].row * o[0].col + 1); i++)
        {
            j = start[o[i].col]++; //0*2 1*3 2*1 1->3
            t[j].row = o[i].col;
            t[j].col = o[i].row;
            t[j].val = o[i].val;
            //printf("%d :%d*",j,t[j].val);//test
        }
    }

} //end transpose function

//function to multiply
/*
	to multiply a&b
	1.multiply a[0][?] with bt[i][?] put it to new line r[0][i]
	2.store numbers in order r[0][i]->r[1][i]......r[a[0].rows](iMAX = bt[0].rows)
	HOW TO STORE THEM Hmmmmm
	maybe use malloc if didn't use then free it
*/
void mmult(term *a, term *b, term *r)
{
    int i, j, column;
    int total = 0, sum = 0, r_now = 1;
    int a_row = a[1].row;
    int row_begin = 1;
    term *t = (term *)malloc(sizeof(term) * (b[0].val + 1));
    t[0].row = b[0].col;
    t[0].col = b[0].row;
    t[0].val = b[0].val;
    transpose(b, t);
    //printf("%d",a[0].val);//test
    /*
	a[a[0].val+1].row = a[0].row;
	t[t[0].val+1].row = t[0].row;
	t[t[0].val+1].col = 0;
	*/
    for (i = 1; i < (a[0].val + 1);)
    {
        column = t[1].row;
        for (j = 1; j <= (t[0].val + 1);)
        {
            //printf("\n%d & %d\n",a[i].val,t[j].val);//test
            //calculate in each row
            /*
			1. deal with matrix a over : a move to next row/ b still didn't have corresponding num
				->skip b and note that a need to run again till r[i][?]?all finish 
				//note that column record 
			2. deal with matrix b over t[0].row : b move to next column(row t)
				->skip a and go to next row of a (out of for j you need to take note of this)
			3. case
				i.		element in a == 0 or not corresponding items
				ii.		element in b == 0 or not corresponding items
				iii.	multiply
			*/
            //multiply a[0][?] with bt[i][?] put it to new line r[0][i]

            if (a[i].row != a_row)
            {
                //add sum of a[i][?]*b[i][?] to r[]
                //printf("this is answer: %d %d", a_row, column);//test
                if (sum > 0)
                {
                    storesum(a_row, column, &sum, &r_now, r);
                }
                i = row_begin;                  //calculate next b column(t row)
                for (; t[j].row == column; j++) //skip bcolumns same as now (move to next bcolumn)
                    ;
                column = t[j].row; //record new column number
            }
            else if (t[j].row != column)
            {
                //add sum of a[i][?]*b[i][?] to r[]
                //printf("%d",j);//test
                if (sum > 0)
                {
                    storesum(a_row, column, &sum, &r_now, r);
                }
                i = row_begin;
                column = t[j].row;
            }
            else
                switch (COMPARE(a[i].col, t[j].col))
                {
                case -1:
                    //i>j means no corresponding value
                    i++;
                    break;
                case 0:
                    //printf("\n%d %d & %d %d\n",a[i].row, a[i].col, t[j].row, t[i].col);
                    //printf("\n%d %d\n",a[i].val, t[j].val);
                    sum += (a[i++].val * t[j++].val);
                    //printf("%s %d %d %d\n","this is", a_row, column, sum);//test
                    break;
                case 1:
                    //i<j means no corresponding value
                    j++;
                }
        } //end j<totalb loop
        for (; a[i].row == a_row; i++)
            ;             //skip a_row which does not have corresponding value
        row_begin = i;    //record which num in matrix a still not be calculate
        a_row = a[i].row; //record which row will be calculate
    }
    r[0].row = a[0].row;
    r[0].col = t[0].row;
    r[0].val = r_now - 1;
    free(t);
} //end mmult function

void storesum(int row, int col, int *sum, int *r_now, term *r)
{
    r[*r_now].row = row;
    r[*r_now].col = col;
    r[*r_now].val = *sum;
    *sum = 0;
    *r_now += 1;
    //printf("%d",*r_now);//test
    //printf("%d",*r_now);//test
}

//multiply a[0][?] with bt[i][?] put it to new line r[0][i]
int COMPARE(int i, int j)
{
    if (i == j)
    {
        return 0;
    }
    else if (i > j)
    {
        return 1;
    }
    else if (i < j)
    {
        return -1;
    }
}

void show(term *m)
{
    int i;
    printf("%d %d %d\n", m[0].row, m[0].col, m[0].val);
    for (i = 1; i <= m[0].val; i++)
    {
        printf("%d %d %d\n", m[i].row, m[i].col, m[i].val);
    }
}
