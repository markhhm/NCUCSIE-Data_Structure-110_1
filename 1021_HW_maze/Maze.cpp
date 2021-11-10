#include <iostream>
#include <stack>
#include <vector>
#define MAX_STACK_SIZE 100
using namespace std;

int length, width;

struct offset
{
    int vert;
    int horiz;
};

struct element
{
    int row;
    int column;
    int dir;
};

int main()
{
    offset move[4];
    move[0].vert = -1, move[0].horiz = 0;
    move[1].vert = 0, move[1].horiz = 1;
    move[2].vert = 1, move[2].horiz = 0;
    move[3].vert = 0, move[3].horiz - 1;

    cin >> length >> width;
    int maze[length + 2][width + 2] = {false};
    int mark[length + 2][width + 2];

    for (int i = 1; i < length + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            cin >> maze[i][j];
        }
    }
    for (int i = 0; i < length + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == length + 1)
            {
                maze[i][j] = 1;
            }
            else if (j == width + 1 || j == 0)
                maze[i][j] = 1;
        }
    }

    for (int i = 0; i < length + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            mark[i][j] = 0;
        }
    }

    int row, col, next_row, next_col, dir, found = false, top = 0;
    stack<element> box;
    element position, ex;
    mark[1][1] = 1;
    ex.row = 1, ex.column = 1, ex.dir = 1;
    box.push(ex);

    while (top > -1 && !found)
    {
        if (dir > 3 && box.empty())
            break;
        position = box.top();

        box.pop();
        row = position.row, col = position.column, dir = position.dir;
        while (dir < 4 && !found)
        {

            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;

            if (next_row == length && next_col == width)
                found = true;
            else if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0)
            {
                mark[next_row][next_col] = 1;
                position.dir = ++dir, position.row = row, position.column = col;
                box.push(position);
                row = next_row, col = next_col, dir = 0;
            }
            else
            {
                dir++;
            }
        }
    }

    if (found)
    {
        vector<element> ans;
        int a = box.size();
        for (int i = a - 1; i >= 0; i--)
        {
            ans.push_back(box.top());
            box.pop();
        }
        for (int i = ans.size() - 1; i >= 0; i--)
        {
            cout << '(' << --ans.at(i).row << ',' << --ans.at(i).column << ')' << " ";
        }
        cout << '(' << --row << ',' << --col << ')' << " ";
        cout << '(' << --next_row << ',' << --next_col << ')';
    }
    else if (dir > 3)
        cout << "Can't reach the exit!";
}