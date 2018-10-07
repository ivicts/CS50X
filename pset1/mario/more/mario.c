#include <stdio.h>
#include <cs50.h>
// Victor Getty
// 15th June 2018
// Prints out a double half-pyramid of a specified height

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 0 || height > 23);

    for (int i = 1; i < height + 1; i++)
    {
        // Prints out the space before the pyramid
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }

        // Prints out the left half of the pyramid
        for (int j = 1; j < i + 1; j++)
        {
            printf("#");
        }

        // Prints out the gap between the left and right half of the pyramid
        printf("  ");

        // Prints out the right half of the pyramid
        for (int j = 1; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}