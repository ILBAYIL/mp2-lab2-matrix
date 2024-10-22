#include <iostream>
#include "utmatrix.h"

int main() {
    TDynamicMatrix<int> a(5, 5), b(5, 5), c(5, 5); // Задаем размеры 5x5 для тестов
    int i, j;

    setlocale(LC_ALL, "Russian");

    try {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                a[i][j] = i * 10 + j; // Заполнение матрицы a
                b[i][j] = (i * 10 + j) * 100; // Заполнение матрицы b
            }
        }

        c = a + b; // Сложение матриц

        // Вывод матриц
        cout << "Matrix a = " << endl << a << endl;
        cout << "Matrix b = " << endl << b << endl;
        cout << "Matrix c = a + b" << endl << c << endl;

    }
    catch (const std::out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl; // Обработка ошибок
    }
}