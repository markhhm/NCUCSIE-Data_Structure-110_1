#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;

node *insert(node *root, int value);
bool DepthFirstSearch(node *root, int sum, int target);

int main(void)
{
    int amount, target;
    scanf("%d", &amount);

    node *BST = NULL;

    for (int i = 0; i < amount; i++)
    {
        int value;
        scanf("%d", &value);
        BST = insert(BST, value);
    }

    scanf("%d", &target);
    if (DepthFirstSearch(BST, 0, target))
        printf("%s", "There exit at least one path in binary search tree.");
    else
        printf("%s", "There have no path in binary search tree.");

    return 0;
}

node *insert(node *root, int value)
{
    if (root == NULL)
    {
        root = (node *)malloc(sizeof(node));
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value < root->value)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insert(root->right, value);
    }
    return root;
}

bool DepthFirstSearch(node *root, int sum, int target)
{
    if (root == NULL)
        return false;

    if ((root->value + sum) == target && root->left == NULL && root->right == NULL)
        return true;

    if (DepthFirstSearch(root->left, sum + root->value, target) | DepthFirstSearch(root->right, sum + root->value, target))
        return true;
    else
        return false;
}