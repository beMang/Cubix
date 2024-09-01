#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <vector>

namespace maths
{
    class Vector;

    class Matrix
    {
    public:
        Matrix(int row, int cols, double default_v=0);
        ~Matrix();
        Matrix(const Matrix& to_copy) = default;

        //GETTERS
        int get_n_rows();
        int get_n_cols();
        double& operator()(int row, int col);
        double const& operator()(int row, int col) const;
        double const& get(int row, int col) const;
        double& get(int row, int col);

        //AUXILIARY
        void print();
        operator Vector();

        //OPERATIONS
        Matrix operator+(Matrix& other);
        Matrix& operator+=(Matrix& other);
        Matrix operator-(Matrix& other);
        Matrix& operator-=(Matrix& other);
        Matrix operator*(double scalar);
        Matrix& operator*=(double scalar);
        Matrix operator*(Matrix& other);
        Matrix operator*(Matrix& other) const;

        double matrixNorm();
        void normalize();

        //BASIC MATRICES
        static Matrix identity_matrix(int size);
        static Matrix rotationX_matrix(double angle);
        static Matrix rotationY_matrix(double angle);
        static Matrix rotationZ_matrix(double angle);
        private:
            int n_rows;
            int n_cols;
            std::vector<double> numbers;
            int index(int row, int col) const;
    };
} // namespace maths

#endif