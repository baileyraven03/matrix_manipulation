// Written by Bailey Raven in line with the specifications outlined by the ACS130 Matrices Assignment
// Date: 21/03/2024

// Including stdio.h library
#include <stdio.h>

struct matrix // Defining the struture 'matrix'
{
    int rows;           // Defining the number of rows
    int cols;           // Defining the number of columns
    float data[10][10]; // Defining the data points for the matrix
};

void matrixInput(struct matrix *mat, FILE *in);                             // Function prototype for the matrixInput funcion
void matrixDisplay(struct matrix mat);                                      // Function prototype for the matrixDisplay function
float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check);   // Function prototype for the matrixDeterminant function
void matrixInverse(struct matrix m1, float determinant, struct matrix *m3); // Function prototype for the matrixInverse function
void clear(void);                                                           // Function prototype for the clear function

int main()
{
    struct matrix m1, m2, m3; // Declaring matrices m1, m2 and m3 for later use
    int user_choice;          // Declaring the user_choice variable to allow the user to loop through
    FILE *fin;                // Delaring the file pointer for the matrix.txt file

    do // Loops through at least once, before promting the user's choice
    {
        fin = fopen("matrix2.txt", "r"); // Opens the matrix2.txt file in read mode
        if (fin == NULL)                 // checks if the input file cannot be opened and thus the file pointer is null
        {
            printf("Error opening matrix2.txt. Please check file path or permissions.\n"); // prints an error message to the user if theres an issue opening the file.
            return 1;                                                                      // returns 1
        }
        else // runs if the file opens successfully
        {
            matrixInput(&m1, fin);                                    // prompts the user to input the matrix size using the matrixInput function
            matrixDisplay(m1);                                        // displays the matrix created above using the matrixDisplay function
            printf("\nNow calculating your determinant!\n");          // prints to the user to let them know the determinant will be calculated
            float determinant = matrixDeterminant(m1, &m2, &m1.rows); // saves the determinat value to the determinant variable which is calculated using the matrixDeterminant function
            if (m2.rows != 0 && m2.cols != 0)                         // checks to see if the matrix m2 has been created successfully
            {
                printf("The determinant is: %f\n", determinant); // prints the value of the determinant to the user
                printf("For the matrix:\n");                     // tells the user which matrix has been used for the determinant
                matrixDisplay(m2);                               // displays the 2 x 2 matrix used for the determinant (m2)
                matrixInverse(m2, determinant, &m3);             // calculates the inverse of the 2 x 2 matrix (m2) using the matrixInverse function
                if (m3.rows != 0 && m3.cols != 0)                // checks to see if the matrix m2 has been created successfully
                {
                    matrixDisplay(m3); // displays the inverse of the 2 x 2 matrix (m2) using the matrixInverse function (m3)
                }
            }
            fclose(fin);                                                 // closes 'matrix.txt' file using the fin pointer
            printf("\nWould you like to continue? (1 = Yes, 0 = No)\n"); // asks the user  if they would like to continue and re-go through the process
            scanf("%d", &user_choice);                                   // prompts the user to input their answer
        }
    } while (user_choice == 1); // sets the condition to keep the loop going whilst the user_choice is equal to 1

    return 0; // returns 0 to end the program
};

void matrixInput(struct matrix *mat, FILE *fin) // Function definition for the matrixInput function
{
    int i, j; // Declaring the i and j variables for later use
    do        // Loops through at least once, before promting the user's choice
    {
        printf("Please enter the number of rows of the matrix: \n"); // Prompts the user to enter the number of rows for the matrix
        scanf("%d", &mat->rows);                                     // Saves the user's input to the rows variable in the matrix
        clear();                                                     // Calls the clear function to clear the buffer and defend against any incorrect inputs
    } while (mat->rows < 1 || mat->rows > 10);                       // Checks to see if the user's input for rows is greater than or equal to 1 and less than or equal to 10
    do                                                               // Loops through at least once, before promting the user's choice
    {
        printf("Please enter the number of columns of the matrix: \n"); // Prompts the user to enter the number of columns for the matrix
        scanf("%d", &mat->cols);                                        // Saves the user's input to the cols variable in the matrix
        clear();                                                        // Calls the clear function to clear the buffer and defend against any incorrect inputs
    } while (mat->cols < 1 || mat->cols > 10);                          // Checks to see if the user's input for columns is greater than or equal to 1 and less than or equal to 10
    for (i = 0; i <= (mat->rows); i++)                                  // Loops through the rows of the matrix using the int i
    {
        for (j = 0; j <= (mat->cols); j++) // Loops through the columns of the matrix using the int j
        {
            fscanf(fin, "%f", &mat->data[i][j]); // Scans the matrix.txt file for the numbers and saves them to the matrix
        }
    }
};

void matrixDisplay(struct matrix mat) // Function definition for the matrixDisplay function
{
    int i, j;                           // declaring ints i & j to be used in upcoming loops
    printf("\n");                       // printing a new line for formatting purposing
    if (mat.rows == 1 && mat.cols == 1) // checks if the matrix is a 1x1 matrix - if so prints it to the terminal in a different manor than if otherwise
    {
        printf("|\t%f\t|\n", mat.data[0][0]); // printing the 1x1 matrix to the terminal
    }
    else // runs if the matrix is not a 1x1 matrix
    {
        for (i = 0; i < mat.rows; i++) // loops through the rows of the matrix
        {
            printf("|\t");                 // printing a vertical line and tab - again for formatting purposes
            for (j = 0; j < mat.cols; j++) // loops through the every column of the matrix for each row
            {
                printf("%f\t", mat.data[i][j]); // prints each corresponding data point and a tab after
            }
            printf("|\n"); // prints a vertical line and a new line to end the row
        }
    }
};

float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check) // Function definition for the matrixDeterminant function
{
    int i = 0, j = 0, method; // setting ints i & j to zero to accomadate 1x1 & 2x2 matrices to minimise user inputs. Also initialises a method int to set a calculation method
    do                        // do while to loop through at least once
    {
        if (m1.rows == 1 && m1.cols == 1) // sets the values for a 1x1 matrix
        {
            method = 2; // sets the method to 2 - used in the following loop
            *check = 0; // check to 0 to ensure it doesnt re-loop through
        }
        else if (m1.rows == 2 && m1.cols == 2) // sets the values for a 2x2 matrix
        {
            method = 1; // sets the method to 1 - used in the following loop
            *check = 0; // check to 0 to ensure it doesnt re-loop through
        }
        else if (m1.rows >= 2 && m1.cols >= 2) // sets the values for a 2x2 matrix or larger
        {
            printf("Please enter the starting row of your 2x2 sub-matrix (at least two less than the total number of rows): \n");       // prompts the user to enter the starting row of the 2x2 sub-matrix
            scanf("%d", &i);                                                                                                            // saves the user's input to the int i
            clear();                                                                                                                    // calls the clear function to clear the buffer and defend against any incorrect inputs
            printf("Please enter the starting column of your 2x2 sub-matrix (at least two less than the total number of columns): \n"); // prompts the user to enter the starting column of the 2x2 sub-matrix
            scanf("%d", &j);                                                                                                            // saves the user's input to the int j
            clear();                                                                                                                    // calls the clear function to clear the buffer and defend against any incorrect inputs
            method = 1;                                                                                                                 // set the method to 1 - used in the following loop
            *check = 0;                                                                                                                 // check set to 0 to ensure it doesnt re-loop through
            if (i > m1.rows - 2 || j > m1.cols - 2)                                                                                     // checks to see if the user's input is valid an will create a 2x2 matrix
            {
                *check = 1;                             // sets check to 1 to re-prompt user entry and re-loop through
                printf("Please enter valid indices\n"); // prints to the user to let them know their input was invalid
            }
        }
        else if (m1.rows < 2 || m1.cols < 2) // sets the value for any matrix with less than 2 rows or columns - 1x1 gets passed this due to the logical ordering
        {
            m2->cols = 0; // sets the columns of m2 to 0 - avoids issues with matrixDisplay function
            m2->cols = 0; // sets the rows of m2 to 0 - avoids issues with matrixDisplay function
            method = 3;   // sets the method to 3 - used in the following loop
            *check = 0;   // check set to 0 to ensure it doesnt re-loop through
        }
    } while (*check != 0); // ensures loop runs whilst check = 1 and the user enters the correct values
    if (method == 1)       // sets the calculation  for method 1
    {
        m2->rows = 2; // sets m2 rows to 2
        m2->cols = 2; // sets m2 cols to 2

        for (int row = 0; row < m2->rows; row++) // loops through the rows of the 2x2 matrix
        {
            for (int col = 0; col < m2->cols; col++) // loops through the columns of the 2x2 matrix
            {
                m2->data[row][col] = m1.data[i + row][j + col]; // sets the data points of the 2x2 matrix to a 2x2 matrix starting form the position stated by the user
            }
        }

        float determinant = m2->data[0][0] * m2->data[1][1] - m2->data[0][1] * m2->data[1][0]; // calculates the determinant of the 2x2 matrix
        return determinant;                                                                    // returns the valie
    }
    else if (method == 2) // sets the calculation method for method 2
    {
        m2->rows = 1;                       // sets m2 rows to 1
        m2->cols = 1;                       // sets m2 cols to 1
        m2->data[0][0] = m1.data[0][0];     // sets the data point of the 1x1 matrix to the data point of the 1x1 matrix - as this is the only data point
        float determinant = m2->data[0][0]; // sets the determinant to the data point of the 1x1 matrix - again, as this is the only data point
        return determinant;                 // returns the value
    }
    else if (method == 3) // sets the calculation method for method 3
    {
        printf("You have entered an invalid matrix size to calculate a determinant, and therefore an inverse cannot be calculated either. \nPlease try again.\n"); // prints to the user to let them know their input was invalid at the start
        float determinant = 0;                                                                                                                                     // sets the determinant to zero
        return determinant;                                                                                                                                        // returns the value
    }
};
void matrixInverse(struct matrix m2, float determinant, struct matrix *m3) // Function definition for the matrixInverse function
{
    if (determinant == 0) // checks to see if the determinant is zero
    {
        printf("\nThe determinant is zero and therefore the inverse does not exist!\n\n"); // prints the error message to the user to let them know the inverse does not exist as the determinant is zero
        m3->rows = 0;                                                                      // sets m3 cols to zero to avoid issues with the matrixDisplay function
        m3->cols = 0;                                                                      // sets m3 rows to zero to avoid issues with the matrixDisplay function
    }
    else if (m2.rows == 2 && m2.cols == 2) // checks to see if the matrix coming in is a 2x2 matrix
    {
        m3->rows = 2;                                    // sets m3 rows to 2
        m3->cols = 2;                                    // sets m3 cols to 2
        float temp = 1.0f / determinant;                 // calculates the temp value for the inverse calculation of 1 / the determinant
        m3->data[0][0] = temp * m2.data[1][1];           // calculates the top left data points for the inverse matrix
        m3->data[0][1] = temp * (-1.0f) * m2.data[0][1]; // calculates the top right data points for the inverse matrix
        m3->data[1][0] = temp * (-1.0f) * m2.data[1][0]; // calculates the bottom left data points for the inverse matrix
        m3->data[1][1] = temp * m2.data[0][0];           // calculates the bottom right data points for the inverse matrix
        printf("\nThe inverse of the matrix is:\n");     // prints to the user to let them know the inverse of their matrix is below
    }
    else // runs if the matrix is a 1x1 matrix
    {
        m3->rows = 1;                                // sets m3 rows to 1
        m3->cols = 1;                                // sets m3 cols to 1
        m3->data[0][0] = -1.0f / m2.data[0][0];      // calculates the inverse as theres only one data point
        printf("\nThe inverse of the matrix is:\n"); // prints to the user to let them know the inverse of their amtrix is below
    }
};

void clear(void) // Function definition for the clear function
{
    while (getchar() != '\n') // loops through until it reaches a new line
    {
        getchar(); // clears the buffer by one character
    };
};