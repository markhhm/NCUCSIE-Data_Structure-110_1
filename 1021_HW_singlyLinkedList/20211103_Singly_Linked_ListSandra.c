#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct list_node
{
    int data;
    struct list_node *link;
};
struct list_node *ptr;

void addBack(int a, struct list_node **node, struct list_node **ptr)
{
    struct list_node *temp = (struct list_node *)malloc(sizeof(struct list_node));
    if (*ptr)
    {
        temp->data = a;
        (*node)->link = temp;
        *node = (*node)->link;
        (*node)->link = NULL;
    }
    else
    {
        temp->data = a;
        temp->link = NULL;
        *ptr = temp;
        *node = temp;
    }
}

void addFront(int a, struct list_node **node, struct list_node **ptr)
{
    struct list_node *temp = (struct list_node *)malloc(sizeof(struct list_node));
    temp->data = a;
    if (*ptr)
    {
        temp->link = *ptr;
        *ptr = temp;
    }
    else
    {
        temp->link = NULL;
        *ptr = temp;
        *node = temp;
    }
}

void addIndex(int f, int s, struct list_node **node, struct list_node **ptr)
{
    int i = 0;
    struct list_node *temp = (struct list_node *)malloc(sizeof(struct list_node));
    struct list_node *time = (struct list_node *)malloc(sizeof(struct list_node));
    temp->data = s;
    time = *ptr;
    if (time == NULL)
    {
        if (f == 0)
        {
            addFront(s, node, ptr);
        }
    }
    else
    {
        if (f == 0)
        {
            addFront(s, node, ptr);
        }
        else if (f > 0)
        {
            while (time->link != NULL && i < f - 1)
            {
                time = time->link;
                i++;
            }

            if (i == f - 1)
            {
                if (time->link == NULL)
                {
                    temp->link = NULL;
                    time->link = temp;
                }
                else
                {
                    temp->link = time->link;
                    time->link = temp;
                }
            }
        }
    }
}
void deleteIndex(int f, struct list_node **ptr)
{
    int i = 0;
    struct list_node *time = (struct list_node *)malloc(sizeof(struct list_node));
    time = *ptr;
    if (f >= 0 && time != NULL)
    {
        if (f == 0 && time->link == NULL)
        {
            time = NULL;
        }
        else if (f > 0)
        {
            while (time->link != NULL && i < f - 1)
            {
                time = time->link;
                i++;
            }
            if (i == f - 1 && time->link != NULL)
            {
                time->link = time->link->link;
            }
            else if (i == 0)
            {
                *ptr = time->link;
            }
        }
    }
}

int main()
{
    int n, a;
    struct list_node *ptr = NULL;
    struct list_node *node = NULL;
    char input[100] = "uu";
    int e = strcmp(input, "exit");
    int ai = strcmp(input, "addIndex");
    int di = strcmp(input, "deleteIndex");
    int ab = strcmp(input, "addBack");
    int af = strcmp(input, "addFront");

    while (e != 0)
    {
        scanf("%s", input);
        e = strcmp(input, "exit");
        ai = strcmp(input, "addIndex");
        di = strcmp(input, "deleteIndex");
        ab = strcmp(input, "addBack");
        af = strcmp(input, "addFront");
        if (ai == 0)
        {
            scanf("%d%d", &n, &a);
        }
        else if (ab == 0 || di == 0 || af == 0)
        {
            scanf("%d", &n);
        }
        if (ab == 0)
        {
            addBack(n, &node, &ptr);
        }
        else if (af == 0)
        {
            addFront(n, &node, &ptr);
        }
        else if (ai == 0)
        {
            addIndex(n, a, &node, &ptr);
        }
        else if (di == 0)
        {
            deleteIndex(n, &ptr);
        }
        else
            break;
    }

    for (; ptr; ptr = ptr->link)
    {
        printf("%d-->", ptr->data);
    }
    printf("null");
}