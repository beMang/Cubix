#include "camera.hpp"
#include <cmath>
#include <cstdio>

namespace objects
{
    Camera::Camera(Vector position, Vector rotation, double surface_height, double surface_width) : Object(position, rotation)
    {
        this->surface_height = surface_height;
        this->surface_width = surface_width;
        this->surface_center = Vector(0, 0, 1);
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

    void Camera::print()
    {
        printf("Camera : \n");
        printf("\tPosition : ");
        this->position.print();
        printf("\tRotation : ");
        this->rotation.print();
        printf("\tSurface Center : ");
        this->surface_center.print();
        printf("\tSurface Height : %f\n", this->surface_height);
        printf("\tSurface Width : %f\n", this->surface_width);
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

    Vector Camera::getCameraVector()
    {
        Matrix rotationX = Matrix::rotationX_matrix(rotation(0));
        Matrix rotationY = Matrix::rotationY_matrix(rotation(1));
        Matrix rotationZ = Matrix::rotationZ_matrix(rotation(2));

        Matrix result = this->surface_center;
        result = rotationZ * result;
        result = rotationY * result;
        result = rotationX * result;

        return result;
    }

    std::vector<Vector> Camera::getRelativeToCamera(std::vector<Vector>& globalVertices)
    {
        Matrix const rotationX = Matrix::rotationX_matrix(rotation(0));
        Matrix const rotationY = Matrix::rotationY_matrix(rotation(1));
        Matrix const rotationZ = Matrix::rotationZ_matrix(rotation(2));

        std::vector<Vector> relativeToCamera = std::vector<Vector>();
        for (Vector vertex : globalVertices)
        {
            Vector relative = vertex - this->position;
            relative = rotationZ * relative;
            relative = rotationY * relative;
            relative = rotationX * relative;
            relativeToCamera.push_back(relative);
        }
        return relativeToCamera;
    }
} // namespace rendering
