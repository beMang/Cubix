#include "scene.hpp"

namespace rendering {
    Scene::Scene(string name) {
        this->name = name;
    }

    Scene::~Scene() {
    }

    void Scene::add_object(Object object) {
        this->objects.push_back(object);
    }

    void Scene::remove_object(int index) {
        this->objects.erase(this->objects.begin() + index);
    }

    void Scene::clear_objects() {
        this->objects.clear();
    }
}
