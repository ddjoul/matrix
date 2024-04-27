#include "rational.h"
#include "matrix_sq.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

int main() {
    srand(std::time(NULL));

    {
        Matrix<100, 100> m3;
    }

    std::vector<std::vector<int>> arr{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<Rational>> arr0{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Matrix<3, 4, int> m1(arr);
    Matrix<3, 4, int> m2(arr);
    Matrix<3, 4> m3(arr0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            m2[i][j] = rand() % 6;
        }
    }
    std::cout << "m1<3, 4>:\n" << m1 << "rank m1:" << m1.rank();
    std :: cout << "\nm2<3, 4>\n" << m2 << "rank m2:" << m2.rank() << "\nm1 + m2:\n" << m1 + m2 << "m2.transpored:\n" << m2.transpored();

    Matrix<3, 3> sq_m1;
    std::vector<std::vector<Rational>> sq_arr{ {1, 2, 3}, {4, 5, 6}, {7, 8, -9} };
    SquareMatrix<3> sq_m2(sq_arr);
    std::cout << "Enter elements of square matrix #1:\n";
    std::cin >> sq_m1;
    std::cout << "sq_m1<3, 3>:\n" << sq_m1 << "trace sq_m1:" << sq_m1.trace() << "\ndet sq_m1:" << sq_m1.det();
    std::cout << "\nsq_m2<3>:\n" << sq_m2 << "trace sq_m2:" << sq_m2.trace() << "\ndet sq_m2:" << sq_m2.det();
    std::cout << "\ninverted:\n" << sq_m2.inverted();
    std::cout << "\n sq_m2 * m3\n" << sq_m2 * m3;
    sq_m1 *= sq_m1;
    std::cout << "\n(sq_m1)^2\n" << sq_m1;
}
