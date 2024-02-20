#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

// Function to print a matrix
void display(double** matrix, int length) {
    // Iterate over rows
    for (int p = 0; p < length; p++) {
        // Iterate over columns
        for (int m = 0; m < length; m++) {
            // Print matrix element
            cout << matrix[p][m] << " ";
        }
        // Move to the next row
        cout << endl;
    }
}

// Function to multiply two matrices
void multiply(double** matrixA, double** matrixB, double** Result, int length) {
    // Iterate over rows of the first matrix
    for (int p = 0; p < length; p++) {
        // Iterate over columns of the second matrix
        for (int m = 0; m < length; m++) {
            double s = 0; // Initialize sum for the result matrix element
            // Iterate over corresponding elements in the row of the first matrix and column of the second matrix
            for (int d = 0; d < length; d++) {
                s += matrixA[p][d] * matrixB[d][m]; // Perform matrix multiplication
            }
            Result[p][m] = s; // Store the result in the output matrix
        }
    }
}

int main() {
    // Set the size of matrices
    int size = 1200;
    
    // Allocate memory for matrices
    double** matrixA = new double*[size];
    double** matrixB = new double*[size];
    double** result = new double*[size];
    // Allocate memory for each row in the matrices
    for (int p = 0; p < size; p++) {
        matrixA[p] = new double[size];
        matrixB[p] = new double[size];
        result[p] = new double[size];
    }
    
    // Initialize matrices with random values
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-10, 10);
    // Iterate over rows and columns of each matrix to assign random values
    for (int p = 0; p < size; p++) {
        for (int m = 0; m < size; m++) {
            matrixA[p][m] = dis(gen);
            matrixB[p][m] = dis(gen);
        }
    }
    
    // Multiply matrices and measure execution time
    auto start = chrono::high_resolution_clock::now();
    multiply(matrixA, matrixB, result, size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "It takes " << duration.count() << " milliseconds to execute during multiplication" << endl;
    
    // Write output to file
    ofstream output("result.txt");
    // Iterate over rows and columns of the result matrix to write to the file
    for (int p = 0; p < size; p++) {
        for (int m = 0; m < size; m++) {
            output << result[p][m] << " ";
        }
        output << endl;
    }
    output.close();
    
    // Free memory
    for (int p = 0; p < size; p++) {
        delete[] matrixA[p];
        delete[] matrixB[p];
        delete[] result[p];
    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] result;
    
    return 0;
}
