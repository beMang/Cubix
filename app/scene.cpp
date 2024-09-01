#include "scene.hpp"

namespace app {
    Scene::Scene(string name) {
        this->name = name;
    }

    Scene::~Scene() {
    }

    void Scene::addMesh(objects::Mesh object) {
        this->meshes.push_back(object);
    }

    void Scene::removeMesh(int index) {
        this->meshes.erase(this->meshes.begin() + index);
    }

    void Scene::clearMesh() {
        this->meshes.clear();
    }

    std::vector<objects::Mesh> Scene::getMeshes()
    {
        return this->meshes;
    }
}
