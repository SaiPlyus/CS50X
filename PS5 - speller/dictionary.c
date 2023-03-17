// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Initialize the word count variable
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Assigns the hash function to a variable
    int h = hash(word);

    // Assigns the hash table to a node pointer
    node *n = table[h];

    // Compares case-sensitive words while the node is not null
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        // Points to next node
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Initializes the hash variable
    unsigned int hash = 0;

    // Adds the words number to a hash
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash += toupper(word[i]);
    }
    // Returns the remainder of the hash divided by N
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opens the dictionary argument
    FILE *ptr = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
    }

    // Declares an array
    char arr[LENGTH + 1];

    // Scans dictionary into the array until EOF
    while (fscanf(ptr, "%s", arr) != EOF)
    {
        // Frees memory
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // Copies the dictionary words into the array
        strcpy(n->word, arr);

        // Obtains the hash value
        int hValue = hash(arr);

        // Points the node to the hash table at the index location
        n->next = table[hValue];
        table[hValue] = n;

        // Updates the size
        word_count++;
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Updates number of words
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate over and free nodes of the hash table
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];

        // Loop through linked list
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
