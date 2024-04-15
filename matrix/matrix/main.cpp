#include "rational.h"
#include "matrix_sq.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

//Жерносек Даниил, 11 группа
int main() {
    srand(std::time(NULL));
    SquareMatrix<2> a;
    SquareMatrix<2> b;
    SquareMatrix<2> answer;
    std::cin >> a >> b;
    a.invert();
    answer = b * a;
    std::cout << answer;
}
