#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string userInputLine;
    std::getline(std::cin, userInputLine);
    int matrixHeight = atof(userInputLine.c_str());
    std::string curValueInMatrix;
    double matrix[matrixHeight][matrixHeight];

    for(int row=0; row<matrixHeight; row++){
        std::getline(std::cin, userInputLine);
        std::istringstream stringStream(userInputLine);
        int column = 0;
        while(stringStream >> curValueInMatrix){
            matrix[row][column] = atof(curValueInMatrix.c_str());;
            column++;
        }
    }

    // calculate
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

    // finalSum
    double finalSum = 1.0;
    for(int i=0; i<matrixHeight; i++){
        finalSum *= matrix[i][i];
    }
    finalSum = finalSum*finalSumSign;
    printf("%f\n", finalSum);
}
