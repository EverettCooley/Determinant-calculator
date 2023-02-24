#include <iostream>
#include <string>
#include <sstream>

/* gets the each value in a matrix from the user
   and returns pointer to the user generated matrix */
double** getUserGeneratedMatrix(int matrixHeight){

    std::string userInputLine;
    double** matrix = new double*[matrixHeight];
    std::string curValueInMatrix;
    for(int row=0; row<matrixHeight; row++){
        matrix[row] = new double[matrixHeight];
        std::getline(std::cin, userInputLine);
        std::istringstream stringStream(userInputLine);
        int column = 0;
        while(stringStream >> curValueInMatrix){
            matrix[row][column] = atof(curValueInMatrix.c_str());;
            column++;
        }
    }
    return matrix;
}


/* swaps the current matrix row with a matrix row that doesnt have a zero
   on the diagonal
   - returns intermediate sign of the determinent (as for every swap the sign 
     should be flipped) */
int swapRows(double** matrix, int row, int matrixHeight){

    int finalDeterminantSign = 1;
    for(int intermediateRow=row+1; intermediateRow<matrixHeight; intermediateRow++){
        if(matrix[intermediateRow][row] == 0.0){continue;}
        finalDeterminantSign *= -1;
        for(int column=0; column<matrixHeight; column++){
            double temp = matrix[intermediateRow][column];
            matrix[intermediateRow][column] = matrix[row][column];
            matrix[row][column] = temp;
        }
        return finalDeterminantSign;
    }
}


/* zeros out the current row of the matrix by multiplying the current row by 
   (another row * some value) to acheive a zero in a paticular matrix cell */
void zeroRow(double** matrix, int row, int matrixHeight){

    for(int intermediateRow=row+1; intermediateRow<matrixHeight; intermediateRow++){
        if(matrix[intermediateRow][row] == 0.0){
            continue;
        }
        double scaler = matrix[intermediateRow][row] * -1/matrix[row][row];
        for(int currentColunn=row; currentColunn<matrixHeight; currentColunn++){
            matrix[intermediateRow][currentColunn] += matrix[row][currentColunn]*scaler;
        }
    }
}


/* calculates the sum of the diagonal values of the matrix 
   (equals the determinent) */
int calculateDiagonalSum(double** matrix, int matrixHeight){
    
    double finalSum = 1.0;
    for(int i=0; i<matrixHeight; i++){
        finalSum *= matrix[i][i];
    }
    return finalSum;
}


/* calculate the determinent of a matrix
   - matrixHeight is the height of a square matrix
   - returns the determinent */
double calculateDeterminant(double** matrix, int matrixHeight){

    int finalDeterminantSign = 1;
    for(int row=0; row<matrixHeight-1; row++){
        if(matrix[row][row] == 0.0){
            finalDeterminantSign *= swapRows(matrix, row, matrixHeight);
        }
        zeroRow(matrix, row, matrixHeight);
    }
    int finalSum = calculateDiagonalSum(matrix, matrixHeight);
    return finalSum*finalDeterminantSign;
}


int main() {

    std::string userInputLine;
    std::getline(std::cin, userInputLine);
    int matrixHeight = atof(userInputLine.c_str());

    double** matrix = getUserGeneratedMatrix(matrixHeight);

    double determinent = calculateDeterminant(matrix, matrixHeight);
    printf("%f\n", determinent);
}
