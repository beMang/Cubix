#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <string>
#include "../objects/mesh.hpp"

namespace app
{
    using namespace std;

    class Scene
    {
    public:
        std::vector<objects::Mesh> meshes;
        string name;
    public:
        Scene(string name);
        ~Scene();

        void addMesh(objects::Mesh object);
        void removeMesh(int index);
        void clearMesh();

        //getters
        std::vector<objects::Mesh> getMeshes();
    };
} // namespace app


#endif