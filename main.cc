#include <iostream>
#include <cstring>
#include <cstdint>

using namespace std;

void printSquare(float * A, int N)
{
    // printing a square matrix of size N x N
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << A[i*N+j] << " ";
        } 
        cout << endl;
    }
}
// assumption of square matrix
// row interchange is not needed
int decompositionLU(float * A, float * L, float * U, int N)
{
    // copy A to U
    memcpy(U, A, sizeof(float)*N*N);
    // construct identity matrix
    memset(L, 0, sizeof(float)*N*N);
    for (int i = 0; i < N; i++) L[i*N+i] = 1.0;

    // row ops
    for (int i = 0; i < N - 1; i++) // iterating through rows 
    {
        float pivot = U[i*N+i]; // finding the pivot
        
        if (pivot == 0) return -1; // check for pivot is not zero
        
        for (int j = i+1; j < N; j++) // iterating through rows
        {
            float factor = U[j*N+i] / pivot; // finding the lead of the row

            for (int k = 0; k < N; k++) // iterating through columns
            {
                U[j*N+k] -= (factor * U[i*N+k]); 
            }
            
            L[j*N+i] = factor; // constructing the elementary matrix
        }
    }

    return 0;
}

void matMul(float * A, float * B, float * C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i*N+j] = 0.0;
            for (int k = 0; k < N; k++)
            {
                C[i*N+j] += A[i*N+k] * B[k*N+j];
            }
        }
    }
    return;
}

int main(int arc, char ** argv)
{
    int N = 3;

    float * A = (float *)malloc(sizeof(float)*N*N);
    float * L = (float *)malloc(sizeof(float)*N*N);
    float * U = (float *)malloc(sizeof(float)*N*N);
    float * B = (float *)malloc(sizeof(float)*N*N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i*N+j] = i * N + j + 1;
        }
    }

    cout << "Matrix A" << endl;
    printSquare(A, N);
    
    decompositionLU(A, L, U, N); // LU Decomposition
    matMul(L, U, B, N); // matrix multiplication to check
    
    cout << "Matrix L" << endl;
    printSquare(L, N);
    cout << "Matrix U" << endl;
    printSquare(U, N);
    cout << "Matrix B" << endl;
    printSquare(B, N);

    return 0;
}