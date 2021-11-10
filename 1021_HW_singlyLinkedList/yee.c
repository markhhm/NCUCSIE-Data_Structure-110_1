#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int getElement();
void checkCommand(char str[]);
void create_singly_linked_list();
int empty();
void addBack(int element);
void addFront(int element);
void addIndex(int index, int element);
void deleteIndex(int index);
void print();
struct node
{

    int data;
    struct node *link;
};

char input[10000];
int input_counter = 0;
struct node *front, *rear;

int main()
{

    create_singly_linked_list();
    int temp_counter = 0;
    for (int i = 0; i < 10000; i++)
    {
        scanf("%c", &input[i]);
        if (input[i] == 'i')
            break;
    }
    for (int i = 0; i < 10000; i++)
    {

        if (input[i] == ' ')
        {
            char temp[20] = "";

            for (int j = 0; j < temp_counter; j++)
                temp[j] = input[j + input_counter];
            input_counter = i + 1;
            checkCommand(temp);
            temp_counter = 0;
        }
        else
            temp_counter++;
    }
    print();
}
int getElement()
{
    int digit_counter = 0;
    int element = 0;
    int number[100000] = {0};
    for (int i = input_counter; i < 100000; i++)
    {
        if (isdigit(input[i]))
        {
            number[digit_counter++] = input[i] - 48;
        }
        else
            break;
    }
    int j = 0;
    while (digit_counter--)
    {
        element += number[j++] * pow(10, digit_counter);
    }
    return element;
}

void checkCommand(char str[])
{

    if (strcmp(str, "addBack") == 0)
    {
        addBack(getElement());
    }
    else if (strcmp(str, "addFront") == 0)
    {
        addFront(getElement());
    }
    else if (strcmp(str, "deleteIndex") == 0)
    {
        deleteIndex(getElement());
    }
    else if (strcmp(str, "addIndex") == 0)
    {
        int index = getElement();
        input_counter += 2;
        int element = getElement();
        input_counter -= 2;
        addIndex(index, element);
    }
}
void create_singly_linked_list()
{

    front = (struct node *)malloc(sizeof(struct node));
    rear = (struct node *)malloc(sizeof(struct node));
    front->link = NULL;
    rear->link = NULL;
}

void free_singly_linked_list()
{

    struct node *this_node, *temp_node;
    if (front->link != NULL)
    {
        this_node = front->link;
        while (this_node->link != NULL)
        {
            temp_node - this_node;
            this_node = this_node->link;
            free(temp_node);
        }
        free(this_node);
    }
    else
        ;

    free(front);
    free(rear);
}

int empty()
{

    if (front->link == NULL)
        return 1;
    else
        return 0;
}

void addBack(int element)
{
    struct node *new_node, *prev_node, *this_node;
    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = element;
    new_node->link = NULL;

    if (empty())
    {
        front->link = new_node;
        rear->link = new_node;
    }
    else
    {

        this_node = rear->link;
        this_node->link = new_node;
        rear->link = new_node;
    }
}

void addFront(int element)
{

    struct node *new_node, *prev_node, *this_node;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = element;
    new_node->link = NULL;

    if (empty())
    {
        front->link = new_node;
        rear->link = new_node;
    }
    else
    {
        this_node = front->link;
        front->link = new_node;
        new_node->link = this_node;
    }
}
void addIndex(int index, int element)
{
    struct node *new_node, *prev_node, *this_node;
    int counter = 0;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = element;
    new_node->link = NULL;

    if (empty())
    {
        if (index == 0)
        {
            front->link = new_node;
            rear->link = new_node;
        }
        else
        {
            return;
        }
    }
    else
    {
        this_node = front->link;
        int counter = 0;
        if (index == 0)
        {
            new_node->link = this_node;
            front->link = new_node;
        }
        while (this_node->link != NULL)
        {
            prev_node = this_node;
            this_node = this_node->link;
            counter++;
            if (counter == index)
            {
                prev_node->link = new_node;
                new_node->link = this_node;
                return;
            }
        }
        if (counter + 1 == index)
        {
            this_node->link = new_node;
            rear->link = new_node;
        }
    }
}
void deleteIndex(int index)
{
    struct node *this_node, *prev_node, *temp_node;
    int counter = 0;

    prev_node = front;
    this_node = front->link;
    if (!empty())
    {
        while (this_node->link != NULL)
        {
            if (counter == index)
            {
                temp_node = this_node;
                prev_node->link = this_node->link;
                free(temp_node);
                return;
            }
            counter++;
            prev_node = this_node;
            this_node = this_node->link;
        }
        if (counter == index)
        {
            temp_node = this_node;
            prev_node->link = NULL;
            rear->link = prev_node;
            free(temp_node);
        }
        else
            return;
    }
    else
        return;
}
void print()
{
    struct node *this_node;
    if (!empty())
    {
        this_node = front->link;
        while (this_node->link != NULL)
        {
            printf("%d-->", this_node->data);
            this_node = this_node->link;
        }
        printf("%d-->null", this_node->data);
    }
    else
        printf("null");
}