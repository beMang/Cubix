#ifndef FACE_HPP
#define FACE_HPP

#include "../math/vector.hpp"
#include <vector>

namespace objects
{
    class Face
    {
    private:
        std::vector<int> vertices_number;
        maths::Vector normal;
    public:
        Face(std::vector<int> vertices_number, std::vector<maths::Vector> vertices);
        Face(std::vector<int> vertices_number);
        ~Face();

        void print();
        void computeNormal(std::vector<maths::Vector> vertices);
        bool isFrontFacingTo(maths::Vector direction);
    };
} // namespace objects

#endif