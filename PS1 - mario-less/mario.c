#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to input desired height
    int bricks = get_int("Height: ");

    // Check to see if user inputs a value between 1 and 8, if not reprompt user
    
    while (bricks < 1 || bricks > 8)
    {
        bricks = get_int("Height: ");
    }

    // Assign input to extra variables for use in algorithm
    int amount = bricks;
    int spaces = bricks - 1;

    // Loop the amount the user inputs
    for (int i = 0; i < bricks; i++)
    {
        // Inserts the right amount of space then decrements
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        // Lets loop continue until it reaches 0
        if (amount > 0)
        {
            // Inserts the right amount of bricks
            for (int k = amount; k <= bricks; k++)
            {
                printf("#");
            }
        }
        // Goes to new line each loop
        
        printf("\n");
        amount--;
        spaces--;
    }
}