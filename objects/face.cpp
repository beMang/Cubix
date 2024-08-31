#include "face.hpp"
#include <iostream>
#include <cassert>

namespace objects {
    Face::Face(std::vector<int> vertices_number, std::vector<maths::Vector> vertices) {
        this->vertices_number = vertices_number;
        computeNormal(vertices);
    }

    Face::Face(std::vector<int> vertices_number)
    {
        this->vertices_number = vertices_number;
    }

    Face::~Face() {
    }

    void Face::print() {
        std::cout << "Nombre de points : " << this->vertices_number.size() << std::endl;
        std::cout << "Points : ";
        for (int i = 0; i < (int) this->vertices_number.size(); i++)
        {
            std::cout << this->vertices_number[i] << " ";
        }
        std::cout << std::endl;
    }

    void Face::computeNormal(std::vector<maths::Vector> vertices) {
        assert(this->vertices_number.size() >= 3);
        maths::Vector v1 = vertices[this->vertices_number[0]];
        maths::Vector v2 = vertices[this->vertices_number[1]];
        maths::Vector v3 = vertices[this->vertices_number[2]];

        //maybe we will have an error here
        maths::Vector u = v2 - v1;
        maths::Vector v = v3 - v1;

        //cross product
        this->normal(0) = u(1)*v(2) - u(2)*v(1);
        this->normal(1) = u(2)*v(0) - u(0)*v(2);
        this->normal(2) = u(0)*v(1) - u(1)*v(0);
    }

    bool Face::isFrontFacingTo(maths::Vector direction)
    {
        assert(direction.size() == this->normal.size());

        double dot = this->normal.dot(direction);
        return dot <= 0;
    }
}
