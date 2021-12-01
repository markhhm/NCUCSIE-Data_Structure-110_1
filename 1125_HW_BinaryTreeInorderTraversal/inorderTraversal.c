#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct nodeM
{
    int data;
    struct nodeM *left;
    struct nodeM *right;
} node;

void inorderT(node *root);
node *createNode(int value);
node *insertLevelOrder(int arr[], node *root, int index, int max);

int main(void)
{
    int arr[MAX_SIZE];
    int i = 0, temp;
    while (1)
    {
        scanf("%d", &temp);
        arr[i] = temp;
        i++;
        if (getchar() == '\n')
            break;
    };
    node *root = insertLevelOrder(arr, root, 0, i);
    inorderT(root);

    return 0;
};

void inorderT(node *root)
{
    if (root == NULL)
        return;
    inorderT(root->left);
    printf("%d ", root->data);
    inorderT(root->right);
};

node *createNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;

    return newNode;
};

node *insertLevelOrder(int arr[], node *root, int index, int max)
{
    if (index < max)
    {
        node *temp = createNode(arr[index]);
        root = temp;

        root->left = insertLevelOrder(arr, root->left, 2 * index + 1, max);
        root->right = insertLevelOrder(arr, root->right, 2 * index + 2, max);
    }
    return root;
}