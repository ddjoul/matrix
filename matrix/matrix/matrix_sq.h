#pragma once
#include "matrix.h"


template<size_t N, typename Field>
class Matrix<N, N, Field> {
protected:
	std::vector< std::vector<Field>> data;
public:
	//Конструктор по умолчанию, создающий единичную матрицу
	Matrix() {
		this->data.resize(N, std::vector<Field>(N, 0));
		for (int i = 0; i < N; i++) {
			data[i][i] = 1;
		}
	}
	
	//Конструктор, создающий матрицу из vector<vector<T>>
	Matrix(std::vector< std::vector<Field>> data) {
		this->data.clear();
		this->data.resize(N, std::vector<Field>(N, 0));
		for (int i = 0; i < std::min(data.size(), this->data.size()); i++) {
			for (int j = 0; j < std::min(data[0].size(), this->data[0].size()); j++) {
				this->data[i][j] = data[i][j];
			}
		}
	}

	//Проверка на равенство: операторы == и !=.
		bool operator==(const Matrix<N, N, Field>&other) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (this->data[i][j] != other.data[i][j]) return 0;
				}
			}
			return 1;
		}
		bool operator !=(const Matrix<N, N, Field>&other) {
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
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				this->data[i][j] *= -1;
			}
		}
		return *this;
	}

	//Сложение, вычитание, операторы +=, −=
		Matrix& operator+=(const Matrix<N, N, Field>&other) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					data[i][j] += other.data[i][j];
				}
			}
			return *this;
		}

		Matrix operator+(const Matrix<N, N, Field>&other) {
			Matrix <N, N, Field>copy = *this;
			return copy += other;
		}

		Matrix& operator-=(const Matrix<N, N, Field>&other) {
			Matrix <N, N, Field>copy = other;
			*this += -copy;
			return *this;
		}

		Matrix operator-(const Matrix<N, N, Field>&other) {
			Matrix <N, N, Field>copy = *this;
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
	Matrix<N, N, Field> transpored() {
		std::vector< std::vector<Field>> d;
		d.resize(N, std::vector<Field>(N, 0));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				d[i][j] = this->data[j][i];
			}
		}
		Matrix<N, N, Field> copy(d);
		return copy;
	}
	
	//След матрицы
	Field trace() {
		Field F(1);
		for (int i = 0; i < N; i++) {
			F *= this->data[i][i];
		}
		return F;
	}

	//ранг
	size_t rank() {
		size_t k; Field F, temp_f;
		Matrix<N, N, Field> temp = *this;
		size_t rank_rows = 0, rank_colomn = 0;
		for (size_t u = 0; u < N - 1; u++) {
			k = u + 1;
			if (temp[u][u] == Field(0)) {
				while (k != N && temp[k][u] == Field(0)) {
					k++;
				}
				if (k == N) break;
				else {
					std::swap(temp[k], temp[u]);
				}
			}
			if (k != N) {
				for (size_t i = u + 1; i < N; i++) {
					F = temp[i][u] / temp[u][u];
					for (size_t j = u; j < N; j++) {
						temp_f = temp[u][j] * F;
						temp[i][j] -= temp_f;
					}
				}
			}
		}
		for (int i = 0; i < N; i++) {
			rank_colomn += nul_str(temp.getColumn(i));
		}
		for (int i = 0; i < N; i++) {
			rank_rows += nul_str(temp.getRow(i));
		}
		return std::min(rank_colomn, rank_rows);
	}

	//Определитель
	Field det() {
		size_t k; Field F, temp_f;
		Matrix<N, N, Field> temp = *this;
		for (size_t u = 0; u < N - 1; u++) {
			k = u + 1;
			if (temp[u][u] == Field(0)) {
				while (k != N && temp[k][u] == Field(0)) {
					k++;
				}
				if (k == N) return Field(0);
				else {
					std::swap(temp[k], temp[u]);
					temp = temp * std::pow(-1, k - u + 1);
				}
			}
			for (size_t i = u + 1; i < N; i++) {
				F = temp[i][u] / temp[u][u];
				for (size_t j = u; j < N; j++) {
					temp_f = temp[u][j] * F;
					temp[i][j] -= temp_f;
				}
			}
		}
		F = Field(1);
		for (size_t i = 0; i < N; i++) {
			F *= temp[i][i];
		}
		return F;
	}

	//Обратная матрица
	Matrix<N, N, Field> invert() {
		assert(this->det() != 0);
		Matrix<N, N, Field> e;
		int k; Field F, temp_f;
		Matrix<N, N, Field> temp = *this;
		for (size_t u = 0; u < N - 1; u++) {
			for (size_t i = u + 1; i < N; i++) {
				F = temp[i][u] / temp[u][u];
				for (size_t j = u; j < N; j++) {
					temp_f = temp[u][j] * F;
					temp[i][j] -= temp_f;
					temp_f = e[u][j] * F;
					e[i][j] -= temp_f;
				}
			}
		}

		for (int u = N - 1; u > 0; u--) {
			for (int i = u - 1; i >= 0; i--) {
				F = temp[i][u] / temp[u][u];
				for (int j = u; j >= 0; j--) {
					temp_f = temp[u][j] * F;
					temp[i][j] -= temp_f;
					temp_f = e[u][j] * F;
					e[i][j] -= temp_f;
				}
			}
		}
		

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				e[i][j] /= temp[i][i];
			}
		}
		*this = e;
		return *this;
	}

	Matrix<N, N, Field> inverted() {
		Matrix<N, N, Field> copy(this->data);
		return copy.invert();
	}

	//Умножение матрицы на число
		friend Matrix<N, N, Field> operator*(const Matrix<N, N, Field>&matr, const Field & sc) {
			Matrix<N, N, Field> copy(matr);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					copy[i][j] *= sc;
				}
			}
			return copy;
		}

		friend Matrix<N, N, Field> operator*(const Field & sc, const Matrix<N, N, Field>&matr) {
			Matrix<N, N, Field> copy(matr);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					copy[i][j] *= sc;
				}
			}
			return copy;
		}

	//Вывод
	template<size_t N, typename Field>
	friend std::ostream& operator<<(std::ostream& os, Matrix<N, N, Field>& a) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				os << a[i][j] << "\t";
			}
			os << "\n";
		}
		return os;
	};

	//Ввод
	template<size_t N, typename Field>
	friend std::istream& operator>>(std::istream& is, Matrix<N, N, Field>& a) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << "[" << i << "][" << j << "]: ";
				is >> a[i][j];
			}
		}
		return is;
	};

	//Умножение матриц
	template<size_t N, typename Field>
	friend Matrix<N, N, Field> operator*(Matrix<N, N, Field>& a, Matrix<N, N, Field>& b);

	//оператор ∗=
	Matrix<N, N, Field>& operator*=(Matrix<N, N, Field> other) {
		*this = *this * other;
		return *this;
	}
};

template<size_t N, typename Field>
Matrix<N, N, Field> operator*(Matrix<N, N, Field>& a, Matrix<N, N, Field>& b) {
	std::vector< std::vector<Field>> temp;
	Matrix<N, N, Field> result(temp);
	Field F;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			F = 0;
			for (int u = 0; u < N; u++) {
				F = a[i][u] * b[u][j];
				result[i][j] += F;
			}
		}
	}
	return result;
}

template<size_t N, typename Field = Rational>
class SquareMatrix : public Matrix<N, N, Field> {
};
