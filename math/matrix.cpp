#include "matrix.hpp"
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include "vector.hpp"

namespace maths{

    Matrix::Matrix(int rows, int cols, double default_v)
    {
        this->n_rows = rows;
        this->n_cols = cols;
        this->numbers = std::vector<double>(rows * cols, default_v);
    }

    Matrix::~Matrix()
    {
    }

    int Matrix::get_n_rows()
    {
        return this->n_rows;
    }

    int Matrix::get_n_cols()
    {
        return this->n_cols;
    }

    double &Matrix::operator()(int row, int col)
    {
        return this->get(row, col);
    }

    double const &Matrix::operator()(int row, int col) const
    {
        return this->get(row, col);
    }

    double const &Matrix::get(int row, int col) const
    {
        assert(row >= 0 && col >= 0 && row < this->n_rows && col < this->n_cols && "Error, wrong coordinates");
        return this->numbers[this->index(row, col)];
    }

    double &Matrix::get(int row, int col)
    {
        assert(row >= 0 && col >= 0 && row < this->n_rows && col < this->n_cols && "Error, wrong coordinates");
        return this->numbers[this->index(row, col)];
    }

    Matrix Matrix::operator+(Matrix &other)
    {
        *this+=other;
        return *this;
    }

    Matrix &Matrix::operator+=(Matrix &other)
    {
        assert(this->n_rows == other.n_rows && this->n_cols == other.n_cols && "Error, matrix must have the same dimensions");
        for (int i = 0; i < this->n_rows; i++)
        {
            for (int j = 0; j < this->n_cols; j++)
            {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this;
    }

    Matrix Matrix::operator-(Matrix &other)
    {
        *this-=other;
        return *this;
    }

    Matrix &Matrix::operator-=(Matrix &other)
    {
        assert(this->n_rows == other.n_rows && this->n_cols == other.n_cols && "Error, matrix must have the same dimensions");
        for (int i = 0; i < this->n_rows; i++)
        {
            for (int j = 0; j < this->n_cols; j++)
            {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this;
    }

    Matrix Matrix::operator*(double scalar)
    {
        *this*=scalar;
        return *this;
    }

    Matrix &Matrix::operator*=(double scalar)
    {
        for (int i = 0; i < this->n_rows; i++)
        {
            for (int j = 0; j < this->n_cols; j++)
            {
                (*this)(i, j) *= scalar;
            }
        }
        return *this;
    }

    Matrix Matrix::operator*(Matrix &other)
    {
        assert(this->n_cols == other.get_n_rows() && "Error, wrong dimensions");

        Matrix result = Matrix(this->n_rows, other.get_n_cols(), 0.0);
        for (int i = 0; i < result.get_n_rows(); i++)
        {
            for (int j = 0; j < result.get_n_cols(); j++)
            {
                double entry = 0;
                for (int k = 0; k < this->n_cols; k++)
                {
                    entry += (*this)(i, k) * other(k, j);
                }
                result(i, j) = entry;
            }
        }

        //Copy the result in the current matrix
        this->n_cols = result.get_n_cols();
        this->n_rows = result.get_n_rows();
        this->numbers = std::vector<double>(result.numbers);
        return *this;
    }

    Matrix Matrix::operator*(Matrix &other) const {
        assert(this->n_cols == other.get_n_rows() && "Error, wrong dimensions");

        Matrix result = Matrix(this->n_rows, other.get_n_cols(), 0.0);
        for (int i = 0; i < result.get_n_rows(); i++)
        {
            for (int j = 0; j < result.get_n_cols(); j++)
            {
                double entry = 0;
                for (int k = 0; k < this->n_cols; k++)
                {
                    entry += (*this)(i, k) * other(k, j);
                }
                result(i, j) = entry;
            }
        }

        return result;
    }

    Matrix::operator Vector()
    {
        assert(this->n_cols == 1 && "Error, matrix must have only one column");
        Vector v = Vector(this->n_rows);
        for (int i = 0; i < this->n_rows; i++)
        {
            v(i) = (*this)(i, 0);
        }
        return v;
    }

    double Matrix::matrixNorm()
    {
        double result = 0;
        for (int i = 0; i < this->n_rows; i++)
        {
            for (int j = 0; j < this->n_cols; j++)
            {
                result += (*this)(i, j) * (*this)(i, j);
            }
        }
        return sqrt(result);
    }

    void Matrix::normalize()
    {
        double norm = this->matrixNorm();
        for (int i = 0; i < this->n_rows; i++)
        {
            for (int j = 0; j < this->n_cols; j++)
            {
                (*this)(i, j) /= norm;
            }
        }
    }

    Matrix Matrix::identity_matrix(int size)
    {
        Matrix idendity = Matrix(size, size, 0);
        for (int i = 0; i < size; i++)
        {
            idendity(i, i) = 1;
        }
        return idendity;
    }

    Matrix Matrix::rotationX_matrix(double angle)
    {
        Matrix rotation = Matrix(3, 3, 0);

        rotation(0, 0) = 1.0;
        rotation(1, 1) = cos(angle);
        rotation(1, 2) = -sin(angle);
        rotation(2, 1) = sin(angle);
        rotation(2, 2) = cos(angle);

        return rotation;
    }

    Matrix Matrix::rotationY_matrix(double angle)
    {
        Matrix rotation = Matrix(3, 3, 0);

        rotation(0, 0) = cos(angle);
        rotation(0, 2) = sin(angle);
        rotation(1, 1) = 1.0;
        rotation(2, 0) = -sin(angle);
        rotation(2, 2) = cos(angle);

        return rotation;
    }

    Matrix Matrix::rotationZ_matrix(double angle)
    {
        Matrix rotation = Matrix(3, 3, 0);

        rotation(0, 0) = cos(angle);
        rotation(0, 1) = -sin(angle);
        rotation(1, 0) = sin(angle);
        rotation(1, 1) = cos(angle);
        rotation(2, 2) = 1.0;

        return rotation;
    }

    int Matrix::index(int row, int col) const
    {
        assert(row >= 0 && row<this->n_rows && "Row out of bounds");
        assert(col >= 0 && col<this->n_cols && "Col out of bounds");
        return col * this->n_rows + row;
    }

    void Matrix::print()
    {
        if (this->n_rows == 0 || this->n_cols == 0)
        {
            printf("Empty matrice\n");
            return;
        }
        printf("Nbr de ligne : %d - Nbr de colonne : %d \n", this->n_rows, this->n_cols);
        for (int i = 0; i < this->n_rows; i++)
        {
            printf("[ ");
            for (int j = 0; j < this->n_cols; j++)
            {
                printf("%9.2f ", (*this)(i, j));
            }
            printf("]\n");
        }
    }
}