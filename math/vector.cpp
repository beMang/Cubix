#include "vector.hpp"
#include <cstdio>

namespace maths
{
    Vector::Vector(int size) : Matrix(size, 1, 0)
    {
    }

    Vector::Vector(double x, double y, double z) : Matrix(3, 1, 0)
    {
        (*this)(0) = x;
        (*this)(1) = y;
        (*this)(2) = z;
    }

    Vector::Vector(double numbers[], int size) : Matrix(size, 1, 0)
    {
        for (int i = 0; i < size; i++)
        {
            (*this)(i) = numbers[i];
        }
    }

    Vector::~Vector()
    {
    }

    double Vector::dot(Vector &other)
    {
        double result = 0;
        for (int i = 0; i < this->get_n_rows(); i++)
        {
            result += (*this)(i) * other(i);
        }
        return result;
    }

    double &Vector::operator()(int row)
    {
        return this->get(row, 0);
    }

    double const &Vector::operator()(int row) const
    {
        return this->get(row, 0);
    }

    int Vector::size()
    {
        return this->get_n_rows();
    }

    void Vector::print()
    {
        printf("Vector : |");
        for (int i = 0; i < this->get_n_rows(); i++)
        {
            printf(" %f |", (*this)(i));
        }
    }
} // namespace maths
