#include "rational.h"
//#include "matrix.h"
#include "matrix_sq.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

template<typename Field>
void print(std::vector< std::vector<Field>>& data) {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) std::cout << data[i][j] << "\t";
        std::cout << "\n";
    }
}

int main() {
    srand(std::time(NULL));
    Rational za;
    std::vector< std::vector<Rational>> data;
    data.resize(2, std::vector<Rational>(2, 0));
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            data[i][j] = rand() % 10 + 1;
        }
    }
    print(data);
    std::cout << "\n";
    Matrix<2, 2> m(data);
    SquareMatrix<2> m1;
    std::cout <<  (m1.rank());
}
