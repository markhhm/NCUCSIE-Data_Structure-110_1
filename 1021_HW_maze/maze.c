#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

typedef struct
{
    int row;
    int col;
    int dir;
} element;

typedef struct
{
    int vert;
    int horiz;
} offset;

element stack[MAX_STACK_SIZE];
int top = -1;

offset move[4];

void push(element item);
void pop();

int main(void)
{
    int length, width, next_row, next_col, dir, col, row;
    bool found = false;
    element position;

    move[0].vert = -1, move[0].horiz = 0;
    move[1].vert = 0, move[1].horiz = 1;
    move[2].vert = 1, move[2].horiz = 0;
    move[3].vert = 0, move[3].horiz - 1;

    scanf("%d %d", &length, &width);
    int maze[length + 2][width + 2];
    int mark[length + 2][width + 2];

    for (int i = 1; i <= length; i++) //maze input
    {
        for (int j = 1; j <= width; j++)
        {
            scanf("%d", &maze[i][j]);
        }
    }
    for (int i = 0; i <= width + 1; i++) //set width bound
    {
        maze[0][i] = 1;
        maze[length + 1][i] = 1;
    }
    for (int i = 0; i <= length + 1; i++) //set length bound
    {
        maze[i][0] = 1;
        maze[i][width + 1] = 1;
    }
    for (int i = 0; i < length + 2; i++) //init mark
    {
        for (int j = 0; j < width + 2; j++)
        {
            mark[i][j] = 0;
        }
    }
    mark[1][1] = 1, top = 0;                              //set mark start position & top
    stack[0].row = 1, stack[0].col = 1, stack[0].dir = 1; //init Stack, now top = 0

    while (top > -1 && !found)
    {
        position = stack[top];
        row = position.row, col = position.col, dir = position.dir;
        pop(); //NOTE:當前的位置要pop出去
        while (dir < 4 && !found)
        {
            if (dir > 3 && top == -1)
            {
                break;
            }
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz; //預計要往前的位置
            if (next_row == length && next_col == width)
            {
                found = true;
            }
            //else if (!maze[next_row][next_col] && !mark[next_row][next_col])
            else if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0)
            //代表有路可走且尚未走過
            {
                mark[next_row][next_col] = 1; //標記走過位置
                position.dir = ++dir;         //如果路不通，將位置pop出來後可直接使用
                position.row = row, position.col = col;
                push(position);                          //push new position to stack
                row = next_row, col = next_col, dir = 0; //往前的位置
            }
            else
            {
                dir++; //下個方向
            }
        }
    }
    if (found)
    {
        for (int i = 0; i <= top; i++)
        {
            printf("(%d,%d) ", --stack[i].row, --stack[i].col);
        }
        printf("(%d,%d) ", --row, --col);
        printf("(%d,%d)", --next_row, --next_col);
    }
    else if (dir > 3)
    {
        printf("Can't reach the exit!");
    }
}

void push(element item)
{
    ++top;
    stack[top].row = item.row;
    stack[top].col = item.col;
    stack[top].dir = item.dir;
};

void pop()
{
    if (top == -1)
    {
        stack[top];
    }
    else
    {
        stack[top--];
    }
}
