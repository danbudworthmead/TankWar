#pragma once
#ifndef __MATRIX_H_
#define __MATRIX_H_

#include "mathLib.h"
#include <vector>

namespace Maths
{
	template<class T> class DLLEXPORT Matrix
	{
	private:
		unsigned int rows, cols;
		T* m_values;
	public:
		inline Matrix(const unsigned int _rows, const unsigned int _cols)
		{
			rows = _rows;
			cols = _cols;
			m_values = new T[_rows * _cols];
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				m_values[i] = 0;
			}
		}

		//\===============================================================================================================================
		//\	Matrix Copy Constructor
		//\===============================================================================================================================
		inline Matrix(DBM::Matrix<T>& a_mat)
		{
			rows = a_mat.GetRows();
			cols = a_mat.GetCols();
			m_values = a_mat.m_values;
		}

		//\===============================================================================================================================
		//\	Return number of rows in the Matrix
		//\===============================================================================================================================
		inline unsigned int Matrix::GetRows() const
		{
			return rows;
		}

		//\===============================================================================================================================
		//\	Return number of columns in the Matrix
		//\===============================================================================================================================
		inline unsigned int Matrix::GetCols() const
		{
			return cols;
		}

		//\===============================================================================================================================
		//\	Overload OStream << 
		//\===============================================================================================================================
		inline friend std::ostream& operator<<(std::ostream& stream, Matrix& matrix)
		{
			for (unsigned int i = 1; i <= matrix.GetRows(); i++)
			{
				for (unsigned int j = 1; j <= matrix.GetCols(); j++)
				{
					stream << matrix(i, j) << "\t";
				}
				stream << "\n";
			}
			return stream;
		}

		//\===============================================================================================================================
		//\	Access Individual Elements in the Matrix
		//\===============================================================================================================================
		inline T& Matrix::operator()(const unsigned int& row, const unsigned int& col)
		{
			if (row > rows || col > cols)
			{
				return m_values[-1];
			}
			return m_values[((row - 1) * cols) + col - 1];
		}

		//\===============================================================================================================================
		//\	Equals Operator Overload
		//\===============================================================================================================================
		inline Matrix<T> Matrix::operator=(const Matrix<T>& other)
		{
			rows = other.GetRows();
			cols = other.GetCols();
			this->m_values = new T[rows * cols];
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				m_values[i] = other.m_values[i];
			}
			return *this;
		}

		//\===============================================================================================================================
		//\	Addition Operator Overloads
		//\===============================================================================================================================
		inline Matrix Matrix::operator+(const Matrix& other) const
		{
			Matrix<T> result(rows, cols);
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				result.m_values[i] = this->m_values[i] + other.m_values[i];
			}
			return result;
		}
		inline Matrix& Matrix::operator+=(const Matrix& other)
		{
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				this->m_values[i] += other.m_values[i];
			}
			return *this;
		}

		////\===============================================================================================================================
		////\	Subtraction Operator Overloads
		////\===============================================================================================================================
		inline Matrix Matrix::operator-(const Matrix& other) const
		{
			Matrix<T> result(rows, cols);
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				result.m_values[i] = this->m_values[i] - other.m_values[i];
			}
			return result;
		}
		inline Matrix& Matrix::operator-=(const Matrix& other)
		{
			for (unsigned int i = 0; i < rows * cols; i++)
			{
				this->m_values[i] -= other.m_values[i];
			}
			return *this;
		}

		////\===============================================================================================================================
		////\	Multiplication Operator Overloads
		////\===============================================================================================================================
		inline Matrix Matrix::operator*(const Matrix& other) const
		{
			Matrix<T> result(rows, other.GetCols());
			if (cols == other.GetRows())
			{

			}
			else
			{
				for (unsigned int i = 0; i < result.GetRows() * result.GetCols(); i++)
					result.m_values[i] = -1;
			}
			return result;
		}
	};
	//template <typename T> class DLLEXPORT Matrix
	//{
	//public:
	//
	//	//\===============================================================================================================================
	//	//\	Matrix Constructor with rows, cols, and type.
	//	//\===============================================================================================================================
	//	Matrix(const unsigned int& a_rows, const unsigned int& a_cols, const T& a_type);
	//
	//	//\===============================================================================================================================
	//	//\	Matrix Copy Constructor.
	//	//\===============================================================================================================================
	//	Matrix(const Matrix& other);
	//
	//	//\===============================================================================================================================
	//	//\	Default Destructor.
	//	//\===============================================================================================================================
	//	virtual ~Matrix();
	//
	//	//\===============================================================================================================================
	//	//\	Equals Operator Overload
	//	//\===============================================================================================================================
	//	Matrix<T>& operator=(const Matrix<T>& other);
	//
	//	//\===============================================================================================================================
	//	//\	Addition Operator Overloads
	//	//\===============================================================================================================================
	//	Matrix<T> operator+(const Matrix<T>& other);
	//	Matrix<T>& operator+=(const Matrix<T>& other);
	//
	//	//\===============================================================================================================================
	//	//\	Subtraction Operator Overloads
	//	//\===============================================================================================================================
	//	Matrix<T> operator-(const Matrix<T>& other);
	//	Matrix<T>& operator-=(const Matrix<T>& other);
	//
	//	//\===============================================================================================================================
	//	//\	Multiplication Operator Overloads
	//	//\===============================================================================================================================
	//	Matrix<T> operator*(const Matrix<T>& other);
	//	Matrix<T>& operator*=(const Matrix<T>& other);
	//
	//	//\===============================================================================================================================
	//	//\	Transpose
	//	//\===============================================================================================================================
	//	Matrix<T> transpose();
	//
	//	//\===============================================================================================================================
	//	//\	Matrix / Scalar Operator Overloads
	//	//\===============================================================================================================================
	//	Matrix<T> operator+(const T& other);
	//	Matrix<T> operator-(const T& other);
	//	Matrix<T> operator*(const T& other);
	//	Matrix<T> operator/(const T& other);
	//
	//	//\===============================================================================================================================
	//	//\	Matrix / Vector Operator Overloads
	//	//\===============================================================================================================================
	//	std::vector<T> operator*(const std::vector<T>& other);
	//	std::vector<T> diag_vec();
	//
	//	//\===============================================================================================================================
	//	//\	Access the row and column sizes
	//	//\===============================================================================================================================
	//	unsigned int GetRows() const;
	//	unsigned int GetCols() const;
	//
	//private:
	//	unsigned int rows, cols;
	//	std::vector<std::vector<T> > matrix;
	//};


//#include "matrix.cpp"
}
#endif //__MATRIX_H_