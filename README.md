# matrix_manipulation
Allows the user to create a matrix and perform set calculations on their matrix.

Firstly the structure matrix is created before the main function, as this is integral to the working of the code.
From here the 3 main functions are defined, along with a helper 'clear' function. These will be re-used throughout for added modularity and simplicity.
Within the main a user choise variable and file pointer is declared outside of the loop, this helps ensure there is no wasted memory and application data is conserved. 

The do-while loop is then initiated, this allows the user to keep performing tasks on a variety of matricies. The file is then opened and the file pointer is checked to have something in it. If the file pointer is not null, then the rest of the code runs, otherwise the program throws an error and the code stops running. 
The user is then prompted to input the number of rows and columns for the matrix, using the function "matrixInput".
This matrix is displayed using the "matrixDisplay" function.
