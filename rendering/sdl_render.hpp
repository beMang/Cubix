#ifndef SDL_RENDER_HPP
#define SDL_RENDER_HPP

#include <SDL2/SDL.h>

#include "abstract_render.hpp"
#include "../objects/camera.hpp"
#include "../app/scene.hpp"

namespace rendering
{
    class SdlRender : public AbstractRender
    {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        app::Scene& scene;
        objects::Camera& camera;

        void drawMesh(SDL_Renderer* renderer, objects::Mesh object, objects::Camera camera);
    public:
        SdlRender(SDL_Window* window, app::Scene& scene, objects::Camera& camera);
        ~SdlRender();

        void init() override;
        void render() override;
        void clean() override;

        void loadScene(app::Scene scene);
    };

    void sdlDrawPoint(SDL_Renderer* renderer, int x, int y, int size);
} // namespace rendering

#endif // SDL_RENDER_HPP