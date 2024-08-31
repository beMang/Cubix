#include "math/vector.hpp"
#include "objects/mesh.hpp"
#include <string>

int main()
{
    using namespace objects;
    using namespace maths;

    std::string filename = "model/cube.obj";

    Mesh myMesh = Mesh(filename, Vector(0,0,0), Vector(0,0,0));
    myMesh.print();
    return 0;
}
