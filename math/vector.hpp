#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"

namespace maths
{
    class Vector : public Matrix
    {
    public:
        Vector(int size=3);
        Vector(double x, double y, double z);
        Vector(const Vector& to_copy) = default;
        Vector(double numbers[], int size=3);
        ~Vector();

        double dot(Vector& other);
        double & operator()(int row);
        double const& operator()(int row) const;
        int size();

        //AUXILIARY
        void print();
    };
} // namespace maths

#endif