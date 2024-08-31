#include "object.hpp"
#include "../math/vector.hpp"
#include <iostream>

namespace objects
{
    using namespace maths;

    Object::Object(Vector position, Vector rotation)
    {
        this->position = position;
        this->rotation = rotation;
    }

    Object::~Object()
    {
    }

    Vector Object::get_position()
    {
        return position;
    }

    Vector Object::get_rotation()
    {
        return rotation;
    }

    void Object::set_position(Vector position)
    {
        this->position = position;
    }

    void Object::set_rotation(Vector rotation)
    {
        this->rotation = rotation;
    }

    void Object::rotateX(double angle)
    {
        rotation(0) += angle;
    }

    void Object::rotateY(double angle)
    {
        rotation(1) += angle;
    }

    void Object::rotateZ(double angle)
    {
        rotation(2) += angle;
    }

    void Object::translateX(double displacement)
    {
        position(0) += displacement;
    }

    void Object::translateY(double displacement)
    {
        position(1) += displacement;
    }

    void Object::translateZ(double displacement)
    {
        position(2) += displacement;
    }

    void Object::print()
    {
        std::cout << "Object : \n";
        std::cout << "\tPosition: ";
        position.print();
        std::cout << "\tRotation: ";
        rotation.print();
    }
} // namespace rendering