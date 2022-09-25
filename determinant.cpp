#include <iostream>
#include <string>
#include <sstream>

int main() {
    // input
    std::string line;
    std::getline(std::cin, line);
    int n = atof(line.c_str());
    std::string num;
    double x[n][n];
    for(int i=0; i<n; i++){
        std::getline(std::cin, line);
        std::istringstream ss(line);
            int j = 0;
        while(ss >> num){
            x[i][j] = atof(num.c_str());;
            j++;
        }
    }
    // calculate
    int flipSign = 1;
    for(int i=0; i<n-1; i++){
        // swap rows
        if(x[i][i] == 0.0){
            for(int j=i+1; j<n; j++){
                if(x[j][i] != 0.0){
                    flipSign *= -1;
                    for(int w=0; w<n; w++){
                        double temp = x[j][w];
                        x[j][w] = x[i][w];
                        x[i][w] = temp;
                    }
                    break;
                }
            }
        }
        // zero points
        for(int j=i+1; j<n; j++){
            if(x[j][i] == 0.0){
                continue;
            }
            double scaler = x[j][i]*-1/x[i][i];
            for(int k=i; k<n; k++){
                x[j][k] += x[i][k]*scaler;
            }
        }
    }
    // sum
    double sum = 1.0;
    for(int i=0; i<n; i++){
        sum *= x[i][i];
    }
    sum = sum*flipSign;
    printf("%f\n", sum);
}
