#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how how many coins the customer is owed
    int cents = get_cents();

    // Calculate the number cents left from number of quarters then update cents
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of cents left from number of dimes then update cents
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of cents left from number of nickles then update cents
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of cents left from number of pennies then update cents
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum all variables to get coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Prompts user for amount owed from amount of cents given
    // Returns cents if above -1
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    return cents;
}

int calculate_quarters(int cents)
{
    // Calculates the number of quarters then returns the result to the quarters variable
    cents = cents / 25;
    return cents;
}

int calculate_dimes(int cents)
{
    // Calculates the number of dimes then returns the result to the dimes variable
    cents = cents / 10;
    return cents;
}

int calculate_nickels(int cents)
{
    // Calculates the number of nickels then returns the result to the nickles variable
    cents = cents / 5;
    return cents;
}

int calculate_pennies(int cents)
{
    // Calculates the number of pennies then returns the result to the pennies variable
    cents = cents / 1;
    return cents;
}
