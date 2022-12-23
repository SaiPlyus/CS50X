#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Calls all function to top of the script
uint64_t get_numbers(void);
uint64_t get_length(uint64_t numbers);
uint64_t validator(uint64_t numbers);
string americanexpress(uint64_t numbers);
string mastercard(uint64_t numbers);
string visa(uint64_t numbers);

// Main function to generate other functions
uint64_t main(void)
{
    //
    uint64_t numbers = get_numbers();
    uint64_t length = get_length(numbers);
    uint64_t valid  = validator(numbers);
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
uint64_t get_numbers(void)
{
    uint64_t numbers = get_long("Number: ");
    return numbers;
}

// Gets the length of the card number
uint64_t get_length(uint64_t numbers)
{
    uint64_t length = 0;
    while (numbers != 0)
    {
        numbers = numbers / 10;
        length++;
    }
    return length;
}

// Card number validation generator
uint64_t validator(uint64_t numbers)
{
    // Variables for first set of digits
    uint64_t first = numbers;
    first = first / 10;
    uint64_t first_num = 0;
    uint64_t first_sum = 0;

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
    uint64_t second = numbers;
    uint64_t second_num = 0;
    uint64_t second_sum = 0;

    // Iterates over second set of digits
    while (second)
    {
        second_num = second % 10;
        second_sum = second_sum + second_num;
        second = second / 100;
    }

    // Adds both sums of digits together
    uint64_t sum = first_sum + second_sum;

    // Final check if card is valid , returns card numbers if valid and EOF if invalid
    if (sum % 10)
    {
        return EOF;
    }
    return numbers;
}

// Checks if card is a mastercard
string mastercard(uint64_t numbers)
{
    // Card must have 16 digits and the correct starting numbers
    string card = "";
    uint64_t digits = numbers / 100000000000000;
    if (digits < 56 && digits >= 51)
    {
        card = "MASTERCARD";
    }
    return card;
}

// Checks if card is an amex
string americanexpress(uint64_t numbers)
{
    // Card must have 15 digits and the correct starting numbers
    string card = "";
    uint64_t digits = numbers / 10000000000000;
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
string visa(uint64_t numbers)
{
    // Card must have 13 or 16 digits and the correct starting numbers
    string card = "";
    uint64_t pri_digits = numbers / 1000000000000;
    uint64_t sec_digits = numbers / 1000000000000000;
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