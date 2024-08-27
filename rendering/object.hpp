#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../math/matrix.hpp"
#include "../math/vector.hpp"

namespace rendering
{
    using namespace maths;

    class Object
    {
        public :
            Object(Vector position, Vector rotation, std::vector<Vector> vertices, std::vector<Face> faces);
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

        private:
            Vector position;
            Vector rotation;
            std::vector<Vector> vertices;
            std::vector<Face> faces;
    }
} // namespace rendering

#endif