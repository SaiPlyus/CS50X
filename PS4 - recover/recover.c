#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Initialization of variables to be used in main function
typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;
BYTE buffer[BLOCK_SIZE];
int n = 8;

// Main function to recover jpeg files from raw data
int main(int argc, char *argv[])
{
    // Initialize file pointer with Command Line Argument
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }
    // Initialize file pointer with output filename;
    FILE *img = NULL;
    // File read command line argument file and store it in a buffer
    // Loop until all blocks of the file are read
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Dynamically allocate memory to the filenames
        char *filename = malloc(sizeof(char) * n);
        // Check the first 4 bytes to see if the data is the start of a jpeg
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            // Dynamically create jpeg files with ascending numbers
            sprintf(filename, "%03i.jpg", n - 8);
            printf("%s\n", filename);
            img = fopen(filename, "w");
            n++;
        }
        // Write jpeg data to jpeg files
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
        // Free allocated memory
        free(filename);
    }
    // Close all opened files
    fclose(file);
    fclose(img);
}