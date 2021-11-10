#include <stdio.h>
#include <stdlib.h>

struct polynomial
{
    int coeff;
    int pow;
    struct polynomial *next;
};

void generatePoly(int term, struct polynomial **temp);
void addPoly(struct polynomial *poly1, struct polynomial *poly2, struct polynomial **result);
int COMPARE(int poly1Pow, int poly2Pow);
void printPoly(struct polynomial *result);

int main(void)
{
    struct polynomial *poly1 = NULL, *poly2 = NULL, *answer = NULL;
    int term1, term2;

    scanf("%d", &term1);
    generatePoly(term1, &poly1);
    scanf("%d", &term2);
    generatePoly(term2, &poly2);

    answer = (struct polynomial *)malloc(sizeof(struct polynomial));
    addPoly(poly1, poly2, &answer);

    printPoly(answer);

    return 0;
}

void generatePoly(int term, struct polynomial **poly)
{
    struct polynomial *temp = (struct polynomial *)malloc(sizeof(struct polynomial));
    int coeff, pow;
    *poly = temp;
    for (int i = 0; i < term; i++)
    {
        scanf("%d %d", &coeff, &pow);
        temp->coeff = coeff;
        temp->pow = pow;

        temp->next = (struct polynomial *)malloc(sizeof(struct polynomial));
        temp = temp->next;
        temp->next = NULL;
    }
}

void addPoly(struct polynomial *poly1, struct polynomial *poly2, struct polynomial **result)
{
    struct polynomial *temp = (struct polynomial *)malloc(sizeof(struct polynomial));
    temp->next = NULL;
    *result = temp;
    while (poly1->next && poly2->next)
    {
        switch (COMPARE(poly1->pow, poly2->pow))
        {
        case 1:
            temp->pow = poly1->pow;
            temp->coeff = poly1->coeff;
            poly1 = poly1->next;

            break;
        case -1:
            temp->pow = poly2->pow;
            temp->coeff = poly2->coeff;
            poly2 = poly2->next;

            break;
        case 0:
            temp->pow = poly1->pow;
            temp->coeff = poly1->coeff + poly2->coeff;
            poly1 = poly1->next;
            poly2 = poly2->next;

            break;
        }
        if (poly1 && poly2)
        {
            temp->next = (struct polynomial *)malloc(sizeof(struct polynomial));
            temp = temp->next;
            temp->next = NULL;
        }
    }

    while (poly1->next || poly2->next)
    {
        temp->next = (struct polynomial *)malloc(sizeof(struct polynomial));
        temp = temp->next;
        temp->next = NULL;

        if (poly1->next)
        {
            temp->pow = poly1->pow;
            temp->coeff = poly1->coeff;
            poly1 = poly1->next;
        }
        if (poly2->next)
        {
            temp->pow = poly2->pow;
            temp->coeff = poly2->coeff;
            poly2 = poly2->next;
        }
    }
}

int COMPARE(int poly1Pow, int poly2Pow)
{
    if (poly1Pow > poly2Pow)
    {
        return 1;
    }
    else if (poly1Pow < poly2Pow)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void printPoly(struct polynomial *result)
{
    while (result != NULL)
    {
        if (result->coeff != 0)
        {
            printf("%d %d ", result->coeff, result->pow);
        }
        result = result->next;
    }
}