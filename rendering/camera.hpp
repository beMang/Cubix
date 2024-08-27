#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"

namespace rendering
{
    using namespace maths;

    class Camera
    {
    private:
        Vector position;
        Vector rotation;

        double surface_height;
        double surface_width;
        Vector surface_center;
    public:
        Camera(Vector position, Vector rotation, double surface_height, double surface_width);
        ~Camera();

        //GETTERS
        Vector get_position();
        Vector get_rotation();

        //SETTERS
        void set_position(Vector position);
        void set_rotation(Vector rotation);
        void set_surface_height(double height);
        void set_surface_width(double width);

        //OPERATIONS
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);

        void translateX(double displacement);
        void translateY(double displacement);
        void translateZ(double displacement);
    };
    
} // namespace rendering

#endif