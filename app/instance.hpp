#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <SDL2/SDL.h>
#include "../objects/camera.hpp"
#include "../rendering/abstract_render.hpp"

namespace app
{
    //attributes : status, window, event, show_fps, quit, renderer_custom
    class Instance
    {
    private:
        int status;
        SDL_Window* window;
        SDL_Event event;
        bool show_fps;
        bool quit;

        objects::Camera camera;
        rendering::AbstractRender* renderer;
    public:
        Instance();
        ~Instance();

        void init();
        void loop();
        int exit();

        void showFps();
    };
} // namespace app

#endif // INSTANCE_HPP