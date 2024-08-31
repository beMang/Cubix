#include "sdl_render.hpp"
#include <cassert>

namespace rendering {
    void SdlRender::drawMesh(SDL_Renderer *renderer, objects::Mesh mesh, objects::Camera camera)
    {
    }

    SdlRender::SdlRender(SDL_Window* window, app::Scene& scene, objects::Camera& camera) : window(window), scene(scene), camera(camera)
    {
    }

    SdlRender::~SdlRender()
    {
        SDL_DestroyRenderer(this->renderer);
    }

    void SdlRender::init()
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
        assert(renderer!=NULL && "Erreur de SDL_CreateRenderer");
    }

    void SdlRender::render()
    {
        for(auto mesh : scene.getMeshes()){
            drawMesh(renderer, mesh, camera);
        }

        SDL_RenderPresent(renderer);
    }

    void SdlRender::clean()
    {
        assert(SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255)==0 && "Erreur de SDL_SetRenderDrawColor");
        assert(SDL_RenderClear(renderer)==0 && "Erreur de SDL_RenderClear");
    }

    void SdlRender::loadScene(app::Scene scene)
    {
        this->scene = scene;
    }

    void sdlDrawPoint(SDL_Renderer *renderer, int x, int y, int size)
    {
        int up = y-size/2;
        int left = x-size/2;

        SDL_Rect rectangle = {left, up, size, size};
        if (SDL_RenderFillRect(renderer, &rectangle)!=0){
            fprintf(stderr, "Erreur de rendu fat_point : %s", SDL_GetError());
            return;
        }
    }
}
