#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <string>
#include "object.hpp"

namespace rendering
{
    using namespace std;

    class Scene
    {
    private:
        std::vector<Object> objects;
        string name;
    public:
        Scene(string name);
        ~Scene();

        void add_object(Object object);
        void remove_object(int index);
        void clear_objects();
    };
} // namespace rendering


#endif