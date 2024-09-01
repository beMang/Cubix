#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/vector.hpp"
#include "object.hpp"
#include <vector>

namespace objects
{
    using namespace maths;

    class Camera : public Object
    {
    private:
        double surface_height;
        double surface_width;
        Vector surface_center;
    public:
        Camera(Vector position, Vector rotation, double surface_height, double surface_width);
        ~Camera();

        //GETTERS
        double get_surface_height();
        double get_surface_width();

        //SETTERS
        void set_surface_height(double height);
        void set_surface_width(double width);

        //AUXILIARY
        void print();

        //OPERATIONS
        void translateForward(double displacement);
        void translateRight(double displacement);
        void translateUp(double displacement);

        Vector getCameraVector();
        std::vector<Vector > getRelativeToCamera(std::vector<Vector>& globalVertices);
    };
    
} // namespace rendering

#endif