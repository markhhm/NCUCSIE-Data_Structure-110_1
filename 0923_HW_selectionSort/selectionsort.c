#include <stdlib.h>
#include <stdio.h>

//#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void selectionSort(int list1[], int list2[], int n);
int main(void)
{
    int studentNum;

    //printf("輸入多少學生： ");
    scanf("%d", &studentNum);

    int id[studentNum];
    int score[studentNum];

    for (int i = 0; i < studentNum; i++)
    {
        //printf("輸入學號與分數： ");
        scanf("%d %d", &id[i], &score[i]);
    }

    selectionSort(id, score, studentNum);

    for (int i = 0; i < studentNum; i++)
    {
        printf("%d\n", id[i]);
    }
    return 0;
}

void selectionSort(int idList[], int scoreList[], int amount)
{
    int i, j, max, temp;
    for (i = 0; i < amount - 1; i++)
    {
        max = i;
        for (j = i + 1; j < amount; j++)
        {
            if (scoreList[j] > scoreList[max])
            {
                max = j;
            }
        }

        int keyId = idList[max];
        int keyScore = scoreList[max];
        while (max > i)
        {
            idList[max] = idList[max - 1];
            scoreList[max] = scoreList[max - 1];
            max--;
        }

        idList[i] = keyId;
        scoreList[i] = keyScore;
        //SWAP(idList[i], idList[max], temp);
        //SWAP(scoreList[i], scoreList[max], temp);
    }
}