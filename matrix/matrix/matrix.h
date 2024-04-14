#pragma once
#include "rational.h"
#include <vector>
#include <algorithm>

template<typename Field = Rational>
bool nul_str( std::vector<Field> data) {
	for (size_t i = 0; i < data.size(); i++) {
		if (data[i] != 0) return 1;
	}
	return 0;
}

template<size_t M, size_t N, typename Field = Rational>
class Matrix {
protected:
	std::vector< std::vector<Field>> data;
public:
	//Конструктор, создающий матрицу из vector<vector<T>>
	Matrix(std::vector< std::vector<Field>> data) {
		this->data.clear();
		this->data.resize(M, std::vector<Field>(N, 0));
		for (int i = 0; i < std::min(data.size(), this->data.size()); i++) {
			for (int j = 0; j < std::min(data[0].size(), this->data[0].size()); j++) {
				this->data[i][j] = data[i][j];
			}
		}
	}

	//Проверка на равенство: операторы == и !=.
		template<size_t M, size_t N, typename Field>
		bool operator==(const Matrix<M, N, Field>&other) {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					if (this->data[i][j] != other.data[i][j]) return 0;
				}
			}
			return 1;
		}
		bool operator !=(const Matrix<M, N, Field>&other) {
			return !(this == other);
		}

	//оператор []
		std::vector<Field>& operator[](size_t id) {
			return data[id];
		}
		const std::vector<Field>& operator[](size_t id) const {
			return data[id];
		}

	//Одинарный минус
	Matrix& operator-() {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				this->data[i][j] *= -1;
			}
		}
		return *this;
	}

	//Сложение, вычитание, операторы +=, −=
		template<size_t M, size_t N, typename Field>
		Matrix& operator+=(const Matrix<M, N, Field>&other) {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					data[i][j] += other.data[i][j];
				}
			}
			return *this;
		}

		template<size_t M, size_t N, typename Field>
		Matrix operator+(const Matrix<M, N, Field>&other) {
			Matrix <M, N, Field>copy = *this;
			return copy += other;
		}

		template<size_t M, size_t N, typename Field>
		Matrix& operator-=(const Matrix<M, N, Field>&other) {
			Matrix <M, N, Field>copy = other;
			*this += -copy;
			return *this;
		}

		template<size_t M, size_t N, typename Field>
		Matrix operator-(const Matrix<M, N, Field>&other) {
			Matrix <M, N, Field>copy = *this;
			return copy -= other;
		}

		//Столбец и строка
		std::vector <Field>getColumn(size_t id) {
			return data[id];
		}

		std::vector <Field>getRow(size_t id) {
			std::vector <Field> temp;
			for (int i = 0; i < N; i++) {
				temp.push_back(data[i][id]);
			}
			return temp;
		}

	//Транспонированная матрица
	Matrix<N, M, Field> transpored() {
		std::vector< std::vector<Field>> d;
		d.resize(N, std::vector<Field>(M, 0));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				d[i][j] = this->data[j][i];
			}
		}
		Matrix<N, M, Field> copy(d);
		return copy;
	}

	//ранг

	size_t rank() {
		size_t k; Field F, temp_f;
		Matrix<M, N, Field> temp = *this;
		size_t rank_rows = 0, rank_colomn = 0;
		for (size_t u = 0; u < std :: min(N, M) - 1; u++) {
			k = u + 1;
			if (temp[u][u] == Field(0)) {
				while (k != std::min(N, M) && temp[k][u] == Field(0)) {
					k++;
				}
				if (k == std::min(N, M)) break;
				else {
					std::swap(temp[k], temp[u]);
				}
			}
			if (k != std::min(N, M)) {
				for (size_t i = u + 1; i < M; i++) {
					F = temp[i][u] / temp[u][u];
					for (size_t j = u; j < N; j++) {
						temp_f = temp[u][j] * F;
						temp[i][j] -= temp_f;
					}
				}
			}
		}
		for (int i = 0; i < M; i++) {
			rank_colomn += nul_str(temp.getColumn(i));
		}
		for (int i = 0; i < N; i++) {
			rank_rows += nul_str(temp.getRow(i));
		}
		return std::min(rank_colomn, rank_rows);
	}

	//Умножение матрицы на число
		friend Matrix<M, N, Field> operator*(const Matrix<M, N, Field>&matr, const Field & sc) {
			Matrix<M, N, Field> copy(matr);
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					copy.data[i][j] *= sc;
				}
			}
			return copy;
		}

		friend Matrix<M, N, Field> operator*(const Field & sc, const Matrix<M, N, Field>&matr) {
			Matrix<M, N, Field> copy(matr);
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					copy.data[i][j] *= sc;
				}
			}
			return copy;
		}
	
	//Вывод
	template<size_t M, size_t N, typename Field>
	friend std::ostream& operator<<(std::ostream& os, Matrix<M, N, Field>& a) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				os << a.data[i][j] << "\t";
			}
			os << "\n";
		}
		return os;
	};

	//Ввод
	template<size_t M, size_t N, typename Field>
	friend std::istream& operator>>(std::istream& is, Matrix<M, N, Field>& a) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << "[" << i << "][" << j << "]: ";
				is >> a[i][j];
			}
		}
		return is;
	};
	
	//Умножение матриц
	template<size_t M, size_t K, size_t N, typename Field>
	friend Matrix<M, N, Field> operator*(Matrix<M, K, Field>& a, Matrix<K, N, Field>& b);
};

template<size_t M, size_t K, size_t N, typename Field>
Matrix<M, N, Field> operator*(Matrix<M, K, Field>& a, Matrix<K, N, Field>& b) {
	std::vector< std::vector<Field>> temp;
	Matrix<M, N, Field> result(temp);
	Field F;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			F = 0;
			for (int u = 0; u < K; u++) {
				F = a[i][u] * b[u][j];
				result[i][j] += F;
			}
		}
	}
	return result;
}