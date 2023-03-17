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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Iterate through the images 2d array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Mutate red, green, and blue with image's RGB values
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through the image 2d array
    for (int k = -1, h = height; k < h + 1; k++)
    {
        for (int l = -1, w = width; l < w + 1; l++)
        {
            // Condition for non-edges and non-corners
            if (k > 0 && l > 0 && k < h - 1 && l < w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * copy[k - 1][l - 1].rgbtRed) + (0 * copy[k - 1][l].rgbtRed) + (1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * copy[k + 1][l - 1].rgbtRed) + (0 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * copy[k - 1][l - 1].rgbtRed) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * copy[k + 1][l - 1].rgbtRed) + (2 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * copy[k - 1][l - 1].rgbtGreen) + (0 * copy[k - 1][l].rgbtGreen) + (1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * copy[k + 1][l - 1].rgbtGreen) + (0 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * copy[k - 1][l - 1].rgbtGreen) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * copy[k + 1][l - 1].rgbtGreen) + (2 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * copy[k - 1][l - 1].rgbtBlue) + (0 * copy[k - 1][l].rgbtBlue) + (1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * copy[k + 1][l - 1].rgbtBlue) + (0 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                int row_one_blue_gy = (-1 * copy[k - 1][l - 1].rgbtBlue) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * copy[k + 1][l - 1].rgbtBlue) + (2 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Top Left Corner
            if (k == 0 && l == 0)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_red_gx = (-2 * 0) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_red_gy = (0 * 0) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = sqrt(round((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_green_gx = (-2 * 0) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_green_gy = (0 * 0) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_blue_gx = (-2 * 0) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                int row_one_blue_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_blue_gy = (0 * 0) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Top Right Corner
            if (k == 0 && l == w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * 0);
                int row_three_red_gx = (-1 * copy[k + 1][l - 1].rgbtRed) + (0 * copy[k + 1][l].rgbtRed) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * 0);
                int row_three_red_gy = (1 * copy[k + 1][l - 1].rgbtRed) + (2 * copy[k + 1][l].rgbtRed) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * 0);
                int row_three_green_gx = (-1 * copy[k + 1][l - 1].rgbtGreen) + (0 * copy[k + 1][l].rgbtGreen) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * 0);
                int row_three_green_gy = (1 * copy[k + 1][l - 1].rgbtGreen) + (2 * copy[k + 1][l].rgbtGreen) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * 0);
                int row_three_blue_gx = (-1 * copy[k + 1][l - 1].rgbtBlue) + (0 * copy[k + 1][l].rgbtBlue) + (1 * 0);

                int row_one_blue_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * 0);
                int row_three_blue_gy = (1 * copy[k + 1][l - 1].rgbtBlue) + (2 * copy[k + 1][l].rgbtBlue) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Bottom Left Corner
            if (k == h - 1 && l == 0)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtRed) + (1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gx = (-2 * 0) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gy = (0 * 0) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtGreen) + (1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gx = (-2 * 0) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gy = (0 * 0) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtBlue) + (1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gx = (-2 * 0) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                int row_one_blue_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gy = (0 * 0) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Bottom Right Corner
            if (k == h - 1 && l == w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * copy[k - 1][l - 1].rgbtRed) + (0 * copy[k - 1][l].rgbtRed) + (1 * 0);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * 0);
                int row_three_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * copy[k - 1][l - 1].rgbtRed) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * 0);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * 0);
                int row_three_red_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * copy[k - 1][l - 1].rgbtGreen) + (0 * copy[k - 1][l].rgbtGreen) + (1 * 0);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * 0);
                int row_three_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * copy[k - 1][l - 1].rgbtGreen) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * 0);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * 0);
                int row_three_green_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * copy[k - 1][l - 1].rgbtBlue) + (0 * copy[k - 1][l].rgbtBlue) + (1 * 0);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * 0);
                int row_three_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                int row_one_blue_gy = (-1 * copy[k - 1][l - 1].rgbtBlue) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * 0);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * 0);
                int row_three_blue_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Left Edge
            if (k > 0 && k < h - 1 && l == 0)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtRed) + (1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gx = (-2 * 0) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gy = (0 * 0) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtGreen) + (1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gx = (-2 * 0) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gy = (0 * 0) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * 0) + (0 * copy[k - 1][l].rgbtBlue) + (1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gx = (-2 * 0) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * 0) + (0 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                int row_one_blue_gy = (-1 * 0) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gy = (0 * 0) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * 0) + (2 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Top Edge
            if (k == 0 && l > 0 && l < w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * copy[k + 1][l - 1].rgbtRed) + (0 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * copy[k + 1][l - 1].rgbtRed) + (2 * copy[k + 1][l].rgbtRed) + (1 * copy[k + 1][l + 1].rgbtRed);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * copy[k + 1][l - 1].rgbtGreen) + (0 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * copy[k + 1][l - 1].rgbtGreen) + (2 * copy[k + 1][l].rgbtGreen) + (1 * copy[k + 1][l + 1].rgbtGreen);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * copy[k + 1][l - 1].rgbtBlue) + (0 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                int row_one_blue_gy = (-1 * 0) + (-2 * 0) + (-1 * 0);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * copy[k + 1][l - 1].rgbtBlue) + (2 * copy[k + 1][l].rgbtBlue) + (1 * copy[k + 1][l + 1].rgbtBlue);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Right Edge
            if (k > 0 && k < h - 1 && l == w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * copy[k - 1][l - 1].rgbtRed) + (0 * copy[k - 1][l].rgbtRed) + (1 * 0);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * 0);
                int row_three_red_gx = (-1 * copy[k + 1][l - 1].rgbtRed) + (0 * copy[k + 1][l].rgbtRed) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * copy[k - 1][l - 1].rgbtRed) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * 0);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * 0);
                int row_three_red_gy = (1 * copy[k + 1][l - 1].rgbtRed) + (2 * copy[k + 1][l].rgbtRed) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * copy[k - 1][l - 1].rgbtGreen) + (0 * copy[k - 1][l].rgbtGreen) + (1 * 0);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * 0);
                int row_three_green_gx = (-1 * copy[k + 1][l - 1].rgbtGreen) + (0 * copy[k + 1][l].rgbtGreen) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * copy[k - 1][l - 1].rgbtGreen) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * 0);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * 0);
                int row_three_green_gy = (1 * copy[k + 1][l - 1].rgbtGreen) + (2 * copy[k + 1][l].rgbtGreen) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * copy[k - 1][l - 1].rgbtBlue) + (0 * copy[k - 1][l].rgbtBlue) + (1 * 0);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * 0);
                int row_three_blue_gx = (-1 * copy[k + 1][l - 1].rgbtBlue) + (0 * copy[k + 1][l].rgbtBlue) + (1 * 0);

                int row_one_blue_gy = (-1 * copy[k - 1][l - 1].rgbtBlue) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * 0);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * 0);
                int row_three_blue_gy = (1 * copy[k + 1][l - 1].rgbtBlue) + (2 * copy[k + 1][l].rgbtBlue) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
            // Bottom Edge
            if (k == h - 1 && l > 0 && l < w - 1)
            {
                // Calculate the 3x3 gx matrix for each iteration through red's values
                int row_one_red_gx = (-1 * copy[k - 1][l - 1].rgbtRed) + (0 * copy[k - 1][l].rgbtRed) + (1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gx = (-2 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (2 * copy[k][l + 1].rgbtRed);
                int row_three_red_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through red's values
                int row_one_red_gy = (-1 * copy[k - 1][l - 1].rgbtRed) + (-2 * copy[k - 1][l].rgbtRed) + (-1 * copy[k - 1][l + 1].rgbtRed);
                int row_two_red_gy = (0 * copy[k][l - 1].rgbtRed) + (0 * copy[k][l].rgbtRed) + (0 * copy[k][l + 1].rgbtRed);
                int row_three_red_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_red = row_one_red_gx + row_two_red_gx + row_three_red_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_red = row_one_red_gy + row_two_red_gy + row_three_red_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_red = round(sqrt((grid_gx_red * grid_gx_red) + (grid_gy_red * grid_gy_red)));
                sqrt_red > 255 ? sqrt_red = 255 : sqrt_red;

                // Calculate the 3x3 gx matrix for each iteration through green's values
                int row_one_green_gx = (-1 * copy[k - 1][l - 1].rgbtGreen) + (0 * copy[k - 1][l].rgbtGreen) + (1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gx = (-2 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (2 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                // Calculate the 3x3 gy matrix for each iteration through green's values
                int row_one_green_gy = (-1 * copy[k - 1][l - 1].rgbtGreen) + (-2 * copy[k - 1][l].rgbtGreen) + (-1 * copy[k - 1][l + 1].rgbtGreen);
                int row_two_green_gy = (0 * copy[k][l - 1].rgbtGreen) + (0 * copy[k][l].rgbtGreen) + (0 * copy[k][l + 1].rgbtGreen);
                int row_three_green_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_green = row_one_green_gx + row_two_green_gx + row_three_green_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_green = row_one_green_gy + row_two_green_gy + row_three_green_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_green = round(sqrt((grid_gx_green * grid_gx_green) + (grid_gy_green * grid_gy_green)));
                sqrt_green > 255 ? sqrt_green = 255 :  sqrt_green;

                // Mutate the 3x3 grid for blue's value for each iteraction
                int row_one_blue_gx = (-1 * copy[k - 1][l - 1].rgbtBlue) + (0 * copy[k - 1][l].rgbtBlue) + (1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gx = (-2 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (2 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gx = (-1 * 0) + (0 * 0) + (1 * 0);

                int row_one_blue_gy = (-1 * copy[k - 1][l - 1].rgbtBlue) + (-2 * copy[k - 1][l].rgbtBlue) + (-1 * copy[k - 1][l + 1].rgbtBlue);
                int row_two_blue_gy = (0 * copy[k][l - 1].rgbtBlue) + (0 * copy[k][l].rgbtBlue) + (0 * copy[k][l + 1].rgbtBlue);
                int row_three_blue_gy = (1 * 0) + (2 * 0) + (1 * 0);

                // Equate the sum of the iterations gx 3x3 grid
                int grid_gx_blue = row_one_blue_gx + row_two_blue_gx + row_three_blue_gx;

                // Equate the sum of the iterations gy 3x3 grid
                int grid_gy_blue = row_one_blue_gy + row_two_blue_gy + row_three_blue_gy;

                // Equate the sum of gx added to gy then equate the square root
                int sqrt_blue = round(sqrt((grid_gx_blue * grid_gx_blue) + (grid_gy_blue * grid_gy_blue)));
                sqrt_blue > 255 ? sqrt_blue = 255 : sqrt_blue;

                // Mutate image with the RGB value averages
                image[k][l].rgbtRed = sqrt_red;
                image[k][l].rgbtGreen = sqrt_green;
                image[k][l].rgbtBlue = sqrt_blue;
            }
        }
    }
    return;
}
