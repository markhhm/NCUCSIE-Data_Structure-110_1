#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int priority;
    // char data[30];
    char *data;
} Node;

typedef struct MaxHeap
{
    int counter;
    int max_amount;
    Node *root;
} MaxHeap;

MaxHeap *generateMaxHeap(int total);
void insert(MaxHeap *max_heap, int priority, char mission[30]);
void extractMaxHeap(MaxHeap *max_heap);
void MaxHeapify(MaxHeap *max_heap, int index);

int main(void)
{
    int total;
    scanf("%d", &total);
    MaxHeap *max_heap = generateMaxHeap(total);

    for (int i = 0; i < total; i++)
    {
        int priority;
        char buffer[30];

        scanf("%30s %d", buffer, &priority);
        char *mission = (char *)calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(mission, buffer);
        insert(max_heap, priority, mission);
    }

    printf("First three things to do:\n");
    for (int i = 0; i < 3; i++)
    {
        extractMaxHeap(max_heap);
    }

    return 0;
}

MaxHeap *generateMaxHeap(int total)
{
    MaxHeap *temp = (MaxHeap *)malloc(sizeof(MaxHeap));
    temp->counter = 0;
    temp->max_amount = total;
    temp->root = (Node *)calloc(total, sizeof(Node));

    return temp;
}

void insert(MaxHeap *max_heap, int priority, char *mission)
{
    if (max_heap->counter >= max_heap->max_amount)
    {
        printf("超出上限");
        return;
    }
    int i = max_heap->counter;
    max_heap->root[i].priority = priority;
    max_heap->root[i].data = mission;
    // strcpy(max_heap->root[i].data, mission);

    while (i && priority > max_heap->root[(i - 1) / 2].priority)
    {
        Node temp = max_heap->root[i];
        max_heap->root[i] = max_heap->root[(i - 1) / 2];
        max_heap->root[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    max_heap->counter++;

    return;
}

void extractMaxHeap(MaxHeap *max_heap)
{
    if (max_heap->counter < 1)
    {
        printf("Queue Empty");
        return;
    }

    int i = max_heap->counter;
    printf("%s\n", max_heap->root[0].data);
    Node temp = max_heap->root[0];
    max_heap->root[0] = max_heap->root[i];
    max_heap->root[i] = temp;

    max_heap->counter--;

    MaxHeapify(max_heap, 0);

    return;
}

void MaxHeapify(MaxHeap *max_heap, int index)
{
    int left = (2 * index) + 1, right = left + 1, max;
    if (right < max_heap->counter && max_heap->root[right].priority > max_heap->root[left].priority)
        max = right;
    else if (left < max_heap->counter && max_heap->root[left].priority > max_heap->root[right].priority)
        max = left;
    else
        max = index;

    if (max != index)
    {
        Node temp = max_heap->root[index];
        max_heap->root[index] = max_heap->root[max];
        max_heap->root[max] = temp;
        MaxHeapify(max_heap, max);
    }
}
