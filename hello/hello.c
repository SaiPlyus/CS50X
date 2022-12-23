// Includes the cs50 library header file
#include <cs50.h>
// Includes the stdio library header file
#include <stdio.h>

// Assigns a main fuction to int that returns no value
int main(void)
{
    // Assigns the get_string function to the question variable with a data type of string
    string question = get_string("What is your name: ");
    // Writes hello with the answer to the question, %s is the format specifier
    printf("Hello, %s\n", question);
}