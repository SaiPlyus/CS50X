#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Calls all function to top of the script
long get_numbers(void);
long get_length(long numbers);
long validator(long numbers);
string americanexpress(long numbers);
string mastercard(long numbers);
string visa(long numbers);

// Main function to generate other functions
int main(void)
{
    //
    long numbers = get_numbers();
    int length = get_length(numbers);
    long valid  = validator(numbers);
    string ami = americanexpress(numbers);
    string mas = mastercard(numbers);
    string vis = visa(numbers);

    // Takes card numbers , if valid returns the matching card number, if not returns invalid
    // Checks if the card is a amex, the correct length, and valid
    if (length == 15 && strcmp(ami, "AMEX") == 0 && valid != -1)
    {
        printf("%s\n", ami);
    } // Checks if the card is a mastercard, the correct length, and valid
    else if (length == 16 &&  strcmp(mas, "MASTERCARD") == 0 && valid != -1)
    {
        printf("%s\n", mas);
    } // Checks if the card is a visa, the correct length, and valid
    else if (length == 13 && strcmp(vis, "VISA") == 0 && valid != -1)
    {
        printf("%s\n", vis);
    } // Checks if the card is a visa, the correct length, and valid
    else if (length == 16 && strcmp(vis, "VISA") == 0 && valid != -1)
    {
        printf("%s\n", vis);
    }
    else // Prints if card is invalid
    {
        printf("INVALID\n");
    }
}

// Prompts user for card number
long get_numbers(void)
{
    long numbers = get_long("Number: ");
    return numbers;
}

// Gets the length of the card number
long get_length(long numbers)
{
    int length = 0;
    while (numbers != 0)
    {
        numbers = numbers / 10;
        length++;
    }
    return length;
}

// Card number validation generator
long validator(long numbers)
{
    // Variables for first set of digits
    long first = numbers;
    first = first / 10;
    int first_num = 0;
    int first_sum = 0;

    // Iterates over first set of digits
    while (first)
    {
        first_num = (first % 10) * 2;
        if (first_num > 9)
        {
            first_num = first_num - 9;
        }
        first_sum = first_sum + first_num;
        first = first / 100;
    }

    // Variables for second set of digits
    long second = numbers;
    int second_num = 0;
    int second_sum = 0;

    // Iterates over second set of digits
    while (second)
    {
        second_num = second % 10;
        second_sum = second_sum + second_num;
        second = second / 100;
    }

    // Adds both sums of digits together
    int sum = first_sum + second_sum;

    // Final check if card is valid , returns card numbers if valid and EOF if invalid
    if (sum % 10)
    {
        return EOF;
    }
    return numbers;
}

// Checks if card is a mastercard
string mastercard(long numbers)
{
    // Card must have 16 digits and the correct starting numbers
    string card = "";
    int digits = numbers / 100000000000000;
    if (digits < 56 && digits >= 51)
    {
        card = "MASTERCARD";
    }
    return card;
}

// Checks if card is an amex
string americanexpress(long numbers)
{
    // Card must have 15 digits and the correct starting numbers
    string card = "";
    int digits = numbers / 10000000000000;
    if (digits < 35 && digits >= 34)
    {
        card = "AMEX";
    }
    else if (digits < 38 && digits >= 37)
    {
        card = "AMEX";
    }
    return card;
}

// Checks if card is a visa
string visa(long numbers)
{
    // Card must have 13 or 16 digits and the correct starting numbers
    string card = "";
    int pri_digits = numbers / 1000000000000;
    int sec_digits = numbers / 1000000000000000;
    if (pri_digits == 4)
    {
        card = "VISA";
    }
    else if (sec_digits == 4)
    {
        card = "VISA";
    }

    return card;
}