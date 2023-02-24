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


/* calculate the determinent of a matrix
   - matrixHeight is the height of a square matrix
   - returns the determinent */
double calculateDeterminant(double** matrix, int matrixHeight){

    int finalSumSign = 1;
    for(int row=0; row<matrixHeight-1; row++){
        // swap rows
        if(matrix[row][row] == 0.0){
            for(int intermediateRow=row+1; intermediateRow<matrixHeight; intermediateRow++){
                if(matrix[intermediateRow][row] != 0.0){
                    finalSumSign *= -1;
                    for(int column=0; column<matrixHeight; column++){
                        double temp = matrix[intermediateRow][column];
                        matrix[intermediateRow][column] = matrix[row][column];
                        matrix[row][column] = temp;
                    }
                    break;
                }
            }
        }
        // zero points
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
    double finalSum = 1.0;
    for(int i=0; i<matrixHeight; i++){
        finalSum *= matrix[i][i];
    }
    return finalSum*finalSumSign;
}


int main() {

    std::string userInputLine;
    std::getline(std::cin, userInputLine);
    int matrixHeight = atof(userInputLine.c_str());

    double** matrix = getUserGeneratedMatrix(matrixHeight);

    double determinent = calculateDeterminant(matrix, matrixHeight);
    printf("%f\n", determinent);
}
