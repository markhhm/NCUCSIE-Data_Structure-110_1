#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int num;
    struct node *next;
};

void addBack(int inputNum, struct node **node);
void addFront(int inputNum, struct node **node, struct node **begin);
void addIndex(int inputNum, int targetIndex, struct node **node, struct node **begin);
void deleteIndex(int targetIndex, struct node **begin);

int main(void)
{
    // char Back[7] = "addBack";
    // char Front[8] = "addFront";
    // char addI[8] = "addIndex";
    // char delete[11] = "deleteIndex";
    // char exit[4] = "exit";
    char inputFunc[12];
    int inputNum, inputIndex, counter = 0;
    struct node *n = NULL;
    struct node *start = NULL;
    int B, F, aI, D, e;
    //scanf("%s", inputFunc);
    // int B = strcmp(inputFunc, "addBack");
    // int F = strcmp(inputFunc, "addFront");
    // int aI = strcmp(inputFunc, "addIndex");
    // int D = strcmp(inputFunc, "deleteIndex");
    // int e = strcmp(inputFunc, "exit");

    //printf("addBack%d\naddFront%d\naddIndex%d\ndelete%d\nexit%d\n", B, F, aI, D, e);

    do
    {
        scanf("%s", inputFunc);
        B = strcmp(inputFunc, "addBack");
        F = strcmp(inputFunc, "addFront");
        aI = strcmp(inputFunc, "addIndex");
        D = strcmp(inputFunc, "deleteIndex");
        e = strcmp(inputFunc, "exit");

        if (B == 0)
        {
            scanf("%d", &inputNum);
            addBack(inputNum, &n);
        }
        else if (F == 0)
        {
            scanf("%d", &inputNum);
            addFront(inputNum, &n, &start);
        }
        else if (aI == 0)
        {
            scanf("%d %d", &inputIndex, &inputNum);
            addIndex(inputNum, inputIndex, &n, &start);
        }
        else if (D == 0)
        {
            scanf("%d", &inputIndex);
            deleteIndex(inputIndex, &start);
        }

        if (counter == 0)
        {
            start = n;
        }
        counter++;

        //printf("start %p\nnode %p\n", start, n);

        //printf("addBack%d\naddFront%d\naddIndex%d\ndelete%d\nexit%d\n", B, F, aI, D, e);
    } while (e != 0);

    n = start;
    //printf("start %p\nnode %p\n", start, n);
    // do
    // {
    //     if (n->num != NULL)
    //     {
    //         printf("%d-->", n->num);
    //     }
    //     if (n->next != NULL)
    //     {
    //         n = n->next;
    //     }
    // } while (n->next != NULL);
    // n = n->next;
    // printf("%d-->", n->num);
    for (; n; n = n->next)
    {
        printf("%d-->", n->num);
    }
    printf("null");
}

void addBack(int inputNum, struct node **node)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->num = inputNum;
    temp->next = NULL;

    if (*node == NULL)
    {
        *node = temp;
    }
    else
    {
        while ((*node)->next != NULL)
        {
            *node = (*node)->next;
        }
        (*node)->next = temp;
        *node = (*node)->next;
    }
};
void addFront(int inputNum, struct node **node, struct node **begin)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->num = inputNum;
    if (*begin)
    {
        temp->next = *begin;
        *begin = temp;
    }
    else
    {
        temp->next = NULL;
        *begin = temp->next;
        *node = temp;
    }
};
void addIndex(int inputNum, int targetIndex, struct node **node, struct node **begin)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    struct node *nodeContainer = (struct node *)malloc(sizeof(struct node));
    temp->num = inputNum;
    temp->next = NULL;
    int count = 1;
    //printf("start %p\nnode %p\n", *begin, *node);

    if (targetIndex == 0)
    {
        addFront(inputNum, node, begin);
        return;
    }

    nodeContainer = *begin;
    if (*begin)
    {
        while (nodeContainer->next != NULL && count < targetIndex) //直接在這邊做計數控制
        {
            nodeContainer = nodeContainer->next;
            count++;
        }
    }
    else
    {
        return;
    }
    //printf("count %d\n", count);

    if (nodeContainer != NULL)
    {

        if (targetIndex > 0 && count == targetIndex)
        {
            if (nodeContainer->next == NULL)
            {
                temp->next = NULL;
                nodeContainer->next = temp;
            }
            else
            {
                temp->next = nodeContainer->next;
                nodeContainer->next = temp;
            }
        }
    }
    // node = begin;
    // while ((*node)->next != NULL)
    // {
    //     *node = (*node)->next;
    //     count++;
    // }
    // printf("count %d\n", count);
    // if (targetIndex > count + 1)
    // {
    //     return 0;
    // }

    // node = begin;
    // for (int i = 0; i < targetIndex; i++)
    // {
    //     *node = (*node)->next;
    // }
    // temp->next = (*node)->next;
    // (*node)->next = temp;
};

void deleteIndex(int targetIndex, struct node **begin)
{
    int count = 0;
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = *begin;
    if (temp != NULL && targetIndex >= 0)
    {
        if (targetIndex == 0 && temp->next == NULL)
        {
            temp = NULL;
            *begin = temp;
        }
        else if (targetIndex == 0)
        {
            *begin = temp->next;
        }
        else if (targetIndex > 0)
        {
            while (temp->next != NULL && count < targetIndex - 1)
            {
                temp = temp->next;
                count++;
            }
            if (count == targetIndex - 1 && temp->next != NULL)
            {
                temp->next = temp->next->next;
            }
        }
        // else if (count == 0)
        // {
        //     *begin = temp->next;
        // }
        // while (temp->next != NULL) //算數量
        // {
        //     temp = temp->next;
        //     count++;
        // }
        // count++;
        // if (targetIndex <= count)
        // {
        //     if (targetIndex == 0 && count == 1)
        //     {
        //         temp = NULL;
        //     }
        //     else if (targetIndex == 0 && count > 1)
        //     {
        //         *begin = temp->next;
        //     }
        //     // else if (count == targetIndex)
        //     // {
        //     //     temp->next = NULL;
        //     // }
        //     else
        //     {
        //         temp->next = temp->next->next;
        //     }
        // }
    }
    // if (targetIndex > count) //超過就跳掉
    // {
    //     return 0;
    // }

    // for (int i = 0; i < targetIndex; i++)
    // {
    //     *node = (*node)->next;
    // }
    // (*node)->next = ((*node)->next)->next;
};