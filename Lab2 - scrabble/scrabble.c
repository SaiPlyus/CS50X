#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    // Calls the function for each score
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Prints who the winner is or if there is a tie
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // Sets variables
    int i, n, index_location, sum_of_score = 0, letters_to_index_location[50];
    // Loops through array of characters
    for (i = 0, n = strlen(word); i < n; i++)
    {
        // Checks if characters or uppercase or lowercase
        if (isupper(word[i]) || islower(word[i]))
        {
            // Converts all letters to uppercase and puts in order from then 0-25
            letters_to_index_location[i] = toupper(word[i]) - 65;
            word[i] = letters_to_index_location[i];
            index_location = word[i];
            // Changes characters to there points value
            word[i] = POINTS[index_location];
            if (word[i] >= 0 && word[i] <= 25)
            {
                // If call conditions are true values get added together
                sum_of_score = sum_of_score + word[i];
            }
        }
    }
    // Sum gets returned
    return sum_of_score;
}
