#include "camera.hpp"
#include <cmath>

namespace objects
{
    Camera::Camera(Vector position, Vector rotation, double surface_height, double surface_width) : Object(position, rotation)
    {
        this->surface_height = surface_height;
        this->surface_width = surface_width;
        this->surface_center = position;
        //CENTER SHOULD BE A BIT IN FRONT OF THE CAMERA
    }

    Camera::~Camera()
    {
    }

    double Camera::get_surface_height()
    {
        return this->surface_height;
    }

    double Camera::get_surface_width()
    {
        return this->surface_width;
    }

    void Camera::set_surface_height(double height)
    {
        this->surface_height = height;
    }

    void Camera::set_surface_width(double width)
    {
        this->surface_width = width;
    }

    void Camera::translateForward(double displacement)
    {
        using namespace maths;

        this->position(0) += displacement * cos(rotation(1));
        this->position(2) += displacement * sin(rotation(1));
    }

    void Camera::translateRight(double displacement)
    {
        using namespace maths;

        this->position(0) += displacement * cos(rotation(1) + M_PI / 2);
        this->position(2) += displacement * sin(rotation(1) + M_PI / 2);
    }

    void Camera::translateUp(double displacement)
    {
        this->position(1) += displacement;
    }
} // namespace rendering
