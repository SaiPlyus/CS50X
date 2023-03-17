#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Calls functions below main to the top of the script
int only_digits(string args);
char rotate(char text_rotate, int to_int);

int main(int argc, string argv[])
{
    //  Conditional if argument vector 1 equals false , returns 1
    if (argv[1] == 0)
    {
        return 1;
    }

    // Variables for argument vector , and to turn argument vector into a number
    string args = argv[1];
    int to_int = atoi(args), digits = only_digits(args);

    // Conditionals if users enter the incorrect usage format, else runs the problem
    if (argc != 2 || digits == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (digits == 1)
    {
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        // Loop to call rotate function for each character the user entered.
        for (int i = 0; i < strlen(plaintext); i++)
        {
            char text[50];
            char text_rotate;
            text[i] = plaintext[i];
            text_rotate = text[i];
            char ciphertext = rotate(text_rotate, to_int);
        }
        printf("\n");
    }
}

// function to evaluate if digits 0 through 9 are entered , returns true is yes
int only_digits(string args)
{
    bool digits;
    int n = strlen(args);
    // Loop to turn argument vectors in to ASCII so they can be evaluated
    for (int i = 0; i < n; i++)
    {
        if (args[i] >= 48 && args[i] <= 57)
        {
            digits = true;
        }
        else
        {
            digits = false;
        }
    }
    return digits;
}

// Function to rotate characters by the number amount entered
char rotate(char text_rotate, int to_int)
{
    char ciphertext;
    int i, char_to_int = (int)text_rotate;
    // Loop to rotate characters
    for (i = 0; i < to_int; i++)
    {
        // Conditional to check for punctuation marks
        if (char_to_int == 46 || char_to_int == 63 || char_to_int == 33 || char_to_int == 44 || char_to_int == 32)
        {
            ciphertext = char_to_int;
        }
        else
        {
            // Conditional to check for letters Z and z when looping
            if (char_to_int == 90)
            {
                char_to_int = 64;

            }
            else if (char_to_int == 122)
            {
                char_to_int = 96;
            }
            char_to_int++;
            ciphertext = char_to_int;
        }
    }
    printf("%c", ciphertext);
    return ciphertext;
}