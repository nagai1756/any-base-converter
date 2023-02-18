#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "conio.h"
typedef struct data Data;
typedef struct data *DataP;
struct data
{
    int value;
    int count;
    DataP previous;
};
DataP add_data(long number, int count, DataP last);
void hexadecimal_output(long base, DataP last2);
void print_data(long base, DataP last);

int main()
{
    long number = 0;
    long base = 0;
    int count = 0;
    Data begin;
    DataP first, last;
    printf("任意の数字を任意の進数表示に変換するプログラムです\n");
    while (1)
    {
        printf("数字と進数の底を入力(例:27を3進数 → 27,3) >>");
        scanf("%ld,%ld", &number, &base);
        if (number > 0 && base >= 2)
            break;
    }
    printf("%ldの%ld進法表示は\n", number, base);
    printf("%ld = ", number);
    last = &begin;
    last->value = number % base;
    last->count = 0;
    last->previous = NULL;
    while (number - base >= 0)
    {
        number /= base;
        last = add_data(number % base, ++count, last);
    }
    DataP last2 = last;
    print_data(base, last2);
    printf("\n");
    hexadecimal_output(base, last);
    printf("(%ld)", base);
    return 0;
}

DataP add_data(long i, int count, DataP last)
{
    DataP new;
    if ((new = (DataP)malloc(sizeof(Data))) == NULL)
    {
        fprintf(stderr, "data allocation error!\n");
        exit(1);
    }
    new->value = i;
    new->count = count;
    new->previous = last;
    return new;
}

void hexadecimal_output(long base, DataP last)
{
    while (last != NULL)
    {
        if (base == 16)
        {
            if (last->value < 10)
                printf("%d ", last->value);
            else
            {
                switch (last->value)
                {
                case 10:
                    printf("A ");
                    break;
                case 11:
                    printf("B ");
                    break;
                case 12:
                    printf("C ");
                    break;
                case 13:
                    printf("D ");
                    break;
                case 14:
                    printf("E ");
                    break;
                case 15:
                    printf("F ");
                }
            }
        }
        else
            printf("%d ", last->value);
        last = last->previous;
    }
}
void print_data(long base, DataP last)
{
    while (last != NULL)
    {
        printf("%d*%.0f", last->value, pow(base, last->count));
        last = last->previous;
        if (last != NULL)
            printf(" + ");
    }
}