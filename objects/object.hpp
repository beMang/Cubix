#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../math/vector.hpp"
#include "face.hpp"

namespace objects
{
    using namespace maths;

    class Object
    {
        public :
            Object(Vector position, Vector rotation);
            ~Object();

            //GETTERS
            Vector get_position();
            Vector get_rotation();

            //SETTERS
            void set_position(Vector position);
            void set_rotation(Vector rotation);

            //OPERATIONS
            void rotateX(double angle);
            void rotateY(double angle);
            void rotateZ(double angle);

            void translateX(double displacement);
            void translateY(double displacement);
            void translateZ(double displacement);

            //AUXILIARY
            void print();

        protected:
            Vector position;
            Vector rotation;
    };
} // namespace objects

#endif