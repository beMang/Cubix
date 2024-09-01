#ifndef MESH_HPP
#define MESH_HPP

#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "object.hpp"
#include "face.hpp"
#include <vector>
#include <string>

namespace objects
{
    using namespace maths;
    using namespace std;

    class Mesh : public Object
    {
        public :
            Mesh(const Mesh& to_copy) = default;
            Mesh(string filename, Vector position, Vector rotation, double scale=1);
            Mesh(Vector position, Vector rotation);
            ~Mesh();

            void print();

            vector<Vector> getGlobalVertices();

        private:
            std::vector<Vector> vertices;
            std::vector<Face> faces;
            double scale;

            void countVerticesAndFaces(string filename, int& n_vertices, int& n_faces);
            void loadVerticesAndFaces(string filename, vector<Vector>& vertices, vector<Face>& faces);
    };
} // namespace objects

#endif