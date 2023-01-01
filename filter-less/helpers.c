#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the images 2d array
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // Add the color values of the current iteration and average them
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int mean = round((float)sum / 3);

            // Mutate the image with the averages
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the images 2d array
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // Equate the sepia formula for each RGB value of sepia
            int sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769
                                 * (float)image[i][j].rgbtGreen + .189
                                 * (float)image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686
                                   * (float)image[i][j].rgbtGreen + .168
                                   * (float)image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534
                                  * (float)image[i][j].rgbtGreen + .131
                                  * (float)image[i][j].rgbtBlue);
            // Ternary operators for limiting the sepia RGB values from exceeding 255
            sepiaRed > 255 ? sepiaRed = 255 : sepiaRed;
            sepiaGreen > 255 ? sepiaGreen = 255 : sepiaGreen;
            sepiaBlue > 255 ? sepiaBlue = 255 :  sepiaBlue;

            // Mutate the image RGB values with the sepia RGB values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    // Iterate through the image 2d array, second nested loop iterates half way
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w / 2; j++)
        {
            // Make a temporary variable so that image and mutated image can be swapped
            tmp = image[i][j];
            // Mutated image uses width minus index location to iterate right to left
            image[i][j] = image[i][w - j - 1];
            image[i][w - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width], red[height][width], green[height][width], blue[height][width];
    // Iterate through the images 2d array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Mutate red, green, and blue with image's RGB values
            red[i][j].rgbtRed = image[i][j].rgbtRed;
            green[i][j].rgbtGreen = image[i][j].rgbtGreen;
            blue[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // Iterate through the image 2d array
    for (int k = 0, h = height; k < h; k++)
    {
        for (int l = 0, w = width; l < w; l++)
        {
            // Condition for non-edges and non-corners
            if (k > 0 && l > 0 && k < h - 1 && l < w - 1)
            {
                // Mutate the 3x3 grid for red's for each iteration
                int row_one_red = red[k - 1][l - 1].rgbtRed + red[k - 1][l].rgbtRed + red[k - 1][l + 1].rgbtRed;
                int row_two_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed + red[k][l + 1].rgbtRed;
                int row_three_red = red[k + 1][l - 1].rgbtRed + red[k + 1][l].rgbtRed + red[k + 1][l + 1].rgbtRed;

                // Average the red values from the 3x3 grid
                int mean_red = round((float)(row_one_red + row_two_red + row_three_red) / 9);

                // Mutate the 3x3 grid for green's for each iteration
                int row_one_green = green[k - 1][l - 1].rgbtGreen + green[k - 1][l].rgbtGreen + green[k - 1][l + 1].rgbtGreen;
                int row_two_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;
                int row_three_green = green[k + 1][l - 1].rgbtGreen + green[k + 1][l].rgbtGreen + green[k + 1][l + 1].rgbtGreen;

                // Average the green values from the 3x3 grid
                int mean_green = round((float)(row_one_green + row_two_green + row_three_green) / 9);

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue = blue[k - 1][l - 1].rgbtBlue + blue[k - 1][l].rgbtBlue + blue[k - 1][l + 1].rgbtBlue;
                int row_two_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;
                int row_three_blue = blue[k + 1][l - 1].rgbtBlue + blue[k + 1][l].rgbtBlue + blue[k + 1][l + 1].rgbtBlue;

                // Average the blue values from the 3x3 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue + row_three_blue) / 9);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Top Left Corner
            if (k == 0 && l == 0)
            {
                // Mutate the 2x2 grid for the red's values for each iteration
                int row_one_red = red[k][l].rgbtRed + red[k][l + 1].rgbtRed;
                int row_two_red = red[k + 1][l].rgbtRed + red[k + 1][l + 1].rgbtRed;

                // Average the red values for the 2x2 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 4);

                // Mutate the 2x2 grid for the green's values for each iteration
                int row_one_green = green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;
                int row_two_green = green[k + 1][l].rgbtGreen + green[k + 1][l + 1].rgbtGreen;

                // Average the green values for the 2x2 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 4);

                // Mutate the 2x2 grid for the red's values for each iteration
                int row_one_blue = blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;
                int row_two_blue = blue[k + 1][l].rgbtBlue + blue[k + 1][l + 1].rgbtBlue;

                // Average the blue values for the 2x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 4);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Top Right Corner
            if (k == 0 && l == w - 1)
            {
                // Mutate the 2x2 grid for the red's values for each iteration
                int row_one_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed;
                int row_two_red = red[k + 1][l - 1].rgbtRed + red[k + 1][l].rgbtRed;

                // Average the red values for the 2x2 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 4);

                // Mutate the 2x2 grid for the green's values for each iteration
                int row_one_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen;
                int row_two_green = green[k + 1][l - 1].rgbtGreen + green[k + 1][l].rgbtGreen;

                // Average the green values for the 2x2 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 4);

                // Mutate the 2x2 grid for the blue's values for each iteration
                int row_one_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue;
                int row_two_blue = blue[k + 1][l - 1].rgbtBlue + blue[k + 1][l].rgbtBlue;

                // Average the blue values for the 2x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 4);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Bottom Left Corner
            if (k == h - 1 && l == 0)
            {
                // Mutate the 2x2 grid for the red's values for each iteration
                int row_one_red = red[k - 1][l].rgbtRed + red[k - 1][l + 1].rgbtRed;
                int row_two_red = red[k][l].rgbtRed + red[k][l + 1].rgbtRed;

                // Average the red values for the 2x2 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 4);

                // Mutate the 2x2 grid for the green's values for each iteration
                int row_one_green = green[k - 1][l].rgbtGreen + green[k - 1][l + 1].rgbtGreen;
                int row_two_green = green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;

                // Average the green values for the 2x2 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 4);

                // Mutate the 2x2 grid for the blue's values for each iteration
                int row_one_blue = blue[k - 1][l].rgbtBlue + blue[k - 1][l + 1].rgbtBlue;
                int row_two_blue = blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;

                // Average the blue values for the 2x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 4);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Bottom Right Corner
            if (k == h - 1 && l == w - 1)
            {
                // Mutate the 2x2 grid for the red's values for each iteration
                int row_one_red = red[k - 1][l - 1].rgbtRed + red[k - 1][l].rgbtRed;
                int row_two_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed;

                // Average the red values for the 2x2 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 4);

                // Mutate the 2x2 grid for the green's values for each iteration
                int row_one_green = green[k - 1][l - 1].rgbtGreen + green[k - 1][l].rgbtGreen;
                int row_two_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen;

                // Average the green values for the 2x2 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 4);

                // Mutate the 2x2 grid for the blue's values for each iteration
                int row_one_blue = blue[k - 1][l - 1].rgbtBlue + blue[k - 1][l].rgbtBlue;
                int row_two_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue;

                // Average the blue values for the 2x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 4);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Left Edge
            if (k > 0 && k < h - 1 && l == 0)
            {
                // Mutate the 3x2 grid for the red's values for each iteration
                int row_one_red = red[k - 1][l].rgbtRed + red[k - 1][l + 1].rgbtRed;
                int row_two_red = red[k][l].rgbtRed + red[k][l + 1].rgbtRed;
                int row_three_red = red[k + 1][l].rgbtRed + red[k + 1][l + 1].rgbtRed;

                // Average the red values for the 3x2 grid
                int mean_red = round((float)(row_one_red + row_two_red + row_three_red) / 6);

                // Mutate the 3x2 grid for the green's values for each iteration
                int row_one_green = green[k - 1][l].rgbtGreen + green[k - 1][l + 1].rgbtGreen;
                int row_two_green = green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;
                int row_three_green = green[k + 1][l].rgbtGreen + green[k + 1][l + 1].rgbtGreen;

                // Average the green values for the 3x2 grid
                int mean_green = round((float)(row_one_green + row_two_green + row_three_green) / 6);

                // Mutate the 3x2 grid for the blue's values for each iteration
                int row_one_blue = blue[k - 1][l].rgbtBlue + blue[k - 1][l + 1].rgbtBlue;
                int row_two_blue = blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;
                int row_three_blue = blue[k + 1][l].rgbtBlue + blue[k + 1][l + 1].rgbtBlue;

                // Average the blue values for the 3x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue + row_three_blue) / 6);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Top Edge
            if (k == 0 && l > 0 && l < w - 1)
            {
                // Mutate the 2x3 grid for the red's values for each iteration
                int row_one_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed + red[k][l + 1].rgbtRed;
                int row_two_red = red[k + 1][l - 1].rgbtRed + red[k + 1][l].rgbtRed + red[k + 1][l + 1].rgbtRed;

                // Average the red values for the 2x3 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 6);

                // Mutate the 2x3 grid for the green's values for each iteration
                int row_one_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;
                int row_two_green = green[k + 1][l - 1].rgbtGreen + green[k + 1][l].rgbtGreen + green[k + 1][l + 1].rgbtGreen;

                // Average the green values for the 2x3 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 6);

                // Mutate the 2x3 grid for the blue's values for each iteration
                int row_one_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;
                int row_two_blue = blue[k + 1][l - 1].rgbtBlue + blue[k + 1][l].rgbtBlue + blue[k + 1][l + 1].rgbtBlue;

                // Average the blue values for the 2x3 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 6);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Right Edge
            if (k > 0 && k < h - 1 && l == w - 1)
            {
                // Mutate the 3x2 grid for the red's values for each iteration
                int row_one_red = red[k - 1][l - 1].rgbtRed + red[k - 1][l].rgbtRed;
                int row_two_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed;
                int row_three_red = red[k + 1][l - 1].rgbtRed + red[k + 1][l].rgbtRed;

                // Average the red values for the 3x2 grid
                int mean_red = round((float)(row_one_red + row_two_red + row_three_red) / 6);

                // Mutate the 3x2 grid for the green's values for each iteration
                int row_one_green = green[k - 1][l - 1].rgbtGreen + green[k - 1][l].rgbtGreen;
                int row_two_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen;
                int row_three_green = green[k + 1][l - 1].rgbtGreen + green[k + 1][l].rgbtGreen;

                // Average the green values for the 2x3 grid
                int mean_green = round((float)(row_one_green + row_two_green + row_three_green) / 6);

                // Mutate the 3x2 grid for the blue's values for each iteration
                int row_one_blue = blue[k - 1][l - 1].rgbtBlue + blue[k - 1][l].rgbtBlue;
                int row_two_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue;
                int row_three_blue = blue[k + 1][l - 1].rgbtBlue + blue[k + 1][l].rgbtBlue;

                // Average the blue values for the 3x2 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue + row_three_blue) / 6);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
            // Bottom Edge
            if (k == h - 1 && l > 0 && l < w - 1)
            {
                // Mutate the 2x3 grid for the red's values for each iteration
                int row_one_red = red[k - 1][l - 1].rgbtRed + red[k - 1][l].rgbtRed + red[k - 1][l + 1].rgbtRed;
                int row_two_red = red[k][l - 1].rgbtRed + red[k][l].rgbtRed + red[k][l + 1].rgbtRed;

                // Average the red values for the 2x3 grid
                int mean_red = round((float)(row_one_red + row_two_red) / 6);

                // Mutate the 2x3 grid for the green's values for each iteration
                int row_one_green = green[k - 1][l - 1].rgbtGreen + green[k - 1][l].rgbtGreen + green[k - 1][l + 1].rgbtGreen;
                int row_two_green = green[k][l - 1].rgbtGreen + green[k][l].rgbtGreen + green[k][l + 1].rgbtGreen;

                // Average the green values for the 2x3 grid
                int mean_green = round((float)(row_one_green + row_two_green) / 6);

                // Mutate the 2x3 grid for the blue's values for each iteration
                int row_one_blue = blue[k - 1][l - 1].rgbtBlue + blue[k - 1][l].rgbtBlue + blue[k - 1][l + 1].rgbtBlue;
                int row_two_blue = blue[k][l - 1].rgbtBlue + blue[k][l].rgbtBlue + blue[k][l + 1].rgbtBlue;

                // Average the blue values for the 2x3 grid
                int mean_blue = round((float)(row_one_blue + row_two_blue) / 6);

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = mean_red;
                image[k][l].rgbtGreen = mean_green;
                image[k][l].rgbtBlue = mean_blue;
            }
        }
    }
    return;
}