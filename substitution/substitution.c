#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Calls function below main to the top of the script
string check_key(string args);
char rotate(string correcttext, string args);

int main(int argc, string argv[])
{
    string args = argv[1];

    // Conditional to see if the user input the correct command-line usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        string key = check_key(args);
        // Conditional to check if the key is the correct format
        if (key != false)
        {
            string plaintext = get_string("plaintext: ");
            char ciphertext = rotate(plaintext, args);
        }
        else
        {
            return 1;
        }
    }
}

// Function that checks the keys format
string check_key(string args)
{
    // Counter that checks if every character is unique, uniqueness = 26
    int counter = 0;

    // Conditional to check if the argument vector is 26 characters, if not returns false
    if (strlen(args) != 26)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < strlen(args); i++) // Loop that iterates through 26 times
        {
            // Conditional to check if the argument vectors are A-Z
            if (args[i] >= 65 && args[i] <= 90)
            {
                // Loop and conditional to compare each character index for uniqueness
                for (int j = 0; j < strlen(args); j++)
                {
                    if (args[j] == args[i])
                    {

                        counter++;
                    }
                }
            }
            else if (args[i] >= 97 && args[i] <= 122) // If no conditional evaluates as true, returns false
            {
                for (int j = 0; j < strlen(args); j++)
                {
                    if (args[j] == args[i])
                    {
                        counter++;
                    }
                }
            }
            else // If no conditional evaluates as true, returns false
            {
                return false;
            }
        }

        if (counter != 26) // Final conditional before returning Key, checks if key is 26 unique characters
        {
            return false;
        }
    }
    return args;
}

// Function to rotate the users input to the key's text
char rotate(string correcttext, string args)
{
    int text[50], rotate, index, uppercase[27];
    char ciphertext;

    // Loop that changes key to uppercase
    printf("ciphertext: ");
    for (int i = 0; i < strlen(args); i++)
    {
        int to_upper[27];
        to_upper[i] = toupper(args[i]);
        uppercase[i] = to_upper[i];
    }

    // Loop that iterates through the text
    for (int i = 0; i < strlen(correcttext); i++)
    {
        text[i] = correcttext[i];
        // Conditionals that check for A-Z and a-z then rotates user input to the key's text
        if (text[i] >= 65 && text[i] <= 90)
        {
            text[i] -= 65;
            index = text[i];
            rotate = uppercase[index];
            ciphertext = rotate;
            printf("%c", ciphertext);
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            text[i] -= 97;
            index = text[i];
            rotate = uppercase[index] + 32;
            ciphertext = rotate;
            printf("%c", ciphertext);
        }
        else // If user input isn't A-Z or a-z, does not rotate the text
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return ciphertext;
}