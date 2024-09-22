#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
template<typename T>
class Matrix {
private:
	std::vector<std::vector<T>  > _matrix;

public:
	Matrix(int rows, int cols) {
		for (int i = 0; i < rows; i++) {
			_matrix.resize(rows);
		}
	};
	Matrix() { _matrix = { 0 } };
	const std::vector<T>& operator[](int row) const { return _matrix[row]; };
	std::vector<T>& operator[](int row) { return _matrix[row]; }
	int getRows() const { return _matrix.size(); }
	int getCols() const { return  getRows() ? _matrix[0].size() : 0 }

	std::vector<T>& operator[](int rows) {
		return _matrix[rows];
	}
};

#endif // !
