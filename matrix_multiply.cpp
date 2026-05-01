#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <algorithm>

using Matrix = std::vector<std::vector<double>>;

Matrix allocate_matrix(int n) {
    return Matrix(n, std::vector<double>(n, 0.0));
}

void initialize_matrix(Matrix& M, int n, double value) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = value + i + j;
        }
    }
}


void multiply_naive(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void multiply_blocked(const Matrix& A, const Matrix& B, Matrix& C, int n, int block_size) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = 0.0;

    for (int ii = 0; ii < n; ii += block_size) {
        for (int jj = 0; jj < n; jj += block_size) {
            for (int kk = 0; kk < n; kk += block_size) {

                for (int i = ii; i < std::min(ii + block_size, n); i++) {
                    for (int j = jj; j < std::min(jj + block_size, n); j++) {

                        double sum = C[i][j];

                        for (int k = kk; k < std::min(kk + block_size, n); k++) {
                            sum += A[i][k] * B[k][j];
                        }

                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int n = (argc > 1) ? std::atoi(argv[1]) : 512;
    int block_size = (argc > 2) ? std::atoi(argv[2]) : 64;

    std::cout << "Matrices: " << n << "x" << n << std::endl;

    auto A = allocate_matrix(n);
    auto B = allocate_matrix(n);
    auto C = allocate_matrix(n);

    initialize_matrix(A, n, 1.0);
    initialize_matrix(B, n, 2.0);


    auto start = std::chrono::high_resolution_clock::now();
    multiply_naive(A, B, C, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Tiempo naive: "
              << std::chrono::duration<double>(end - start).count()
              << " s" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    multiply_blocked(A, B, C, n, block_size);
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Tiempo blocked (" << block_size << "): "
              << std::chrono::duration<double>(end - start).count()
              << " s" << std::endl;

    return 0;
}