#include "object.hpp"
#include <iostream>

namespace rendering
{
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
        std::cout << "Position: ";
        position.print();
        std::cout << "Rotation: ";
        rotation.print();

        std::cout << "Vertices: ";
    }
} // namespace rendering
