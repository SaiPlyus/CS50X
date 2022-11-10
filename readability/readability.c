#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// Calls all of the functions below main to the top.
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompts users for the text that will be graded.
    string text = get_string("Text: ");
    printf("%s\n", text);
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);

    // Coleman-Liau Index formula
    float L = ((float)letter_count / (float)word_count) * 100;
    float S = ((float)sentence_count / (float)word_count) * 100;
    double index = round(0.0588 * L - 0.296 * S - 15.8);
    int grade = round(index);

    // Conditional to print the proper grade of the text
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }


}

// Function to count letters of the text
int count_letters(string text)
{
    int i, letter_count = 0;
    long letters = strlen(text);

    // Loop that loops through the text
    for (i = 0; i < letters; i++)
    {

        if (text[i] >= 65 && text[i] <= 90)
        {
            letter_count++;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            letter_count++;
        }
    }
    return letter_count;
}

// Function that counts the words of the text
int count_words(string text)
{
    bool space = false;
    int i, word_count = 0;
    long words = strlen(text);

    // Conditional to check for first word
    if (text[0] >= 65 && text[0] <= 90)
    {
        word_count = 1;
    }
    else if (text[0] >= 97 && text[0] <= 122)
    {
        word_count = 1;
    }

    // Loop to loop through the text
    for (i = 0; i < words; i++)
    {
        // Conditional to count the words
        if (text[i] == 32 && space == false)
        {
            word_count++;
            space = true;
        }

        // Conditional to tell if end of spaces
        if (text[i] >= 65 && text[i] <= 90)
        {
            space = false;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            space = false;
        }

    }
    return word_count;
}

// Function to count the sentences
int count_sentences(string text)
{
    int i, sentence_count = 0;
    long sentences = strlen(text);

    // Loop to loop through the text
    for (i = 0; i < sentences; i++)
    {
        // Conditional to tell when a sentence ends
        if (text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentence_count++;
        }
    }
    return sentence_count;
}