#include <iostream>
#include <chrono>
#include <cstdlib>

const int N = 10000; // Tamaño de la matriz (10,000 x 10,000)
int matriz[N][N];

void acceder_por_filas() {
    long long suma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            suma += matriz[i][j]; // 
        }
    }
}

void acceder_por_columnas() {
    long long suma = 0;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            suma += matriz[i][j]; // 
        }
    }
}

int main() {
    // Inicializar matriz (evitar optimizaciones)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;
        }
    }

    // Medir acceso por filas
    auto start = std::chrono::high_resolution_clock::now();
    acceder_por_filas();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Acceso por filas: "
              << std::chrono::duration<double>(end - start).count()
              << " segundos\n";

    // Medir acceso por columnas
    start = std::chrono::high_resolution_clock::now();
    acceder_por_columnas();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Acceso por columnas: "
              << std::chrono::duration<double>(end - start).count()
              << " segundos\n";

    return 0;
}
