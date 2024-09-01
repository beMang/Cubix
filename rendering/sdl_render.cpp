#include "sdl_render.hpp"
#include <cassert>
#include <vector>
#include "../math/vector.hpp"
#include <iostream>

namespace rendering {
    void SdlRender::drawMesh(objects::Mesh mesh, objects::Camera camera)
    {
        // TODO : Implementer le rendu de l'objet

        std::vector<maths::Vector> globalVertices = mesh.getGlobalVertices();
        std::vector<maths::Vector> relativeToCamera = camera.getRelativeToCamera(globalVertices);

        //PROJECT MESH WITH HOMOGENEOUS COORDINATES
        std::vector<maths::Vector> projectedVertices = std::vector<maths::Vector>();
        for (maths::Vector& vertex : relativeToCamera)
        {
            maths::Vector projectedVertex = maths::Vector(2);
            projectedVertex(0) = vertex(0) / vertex(2);
            projectedVertex(1) = vertex(1) / vertex(2);
            projectedVertices.push_back(projectedVertex);
        }

        //CLIPPING
        //TODO

        //MAP ON SDL WINDOW
        for(maths::Vector& vertex : projectedVertices){
            maths::Vector translationVector = maths::Vector(2);
            translationVector(0) = 1;
            translationVector(1) = -1;
            vertex = vertex + translationVector;
            vertex(1) = -vertex(1);
            vertex*=250;
        }

        //DRAW POINTS AND LINES OF MESH
        for(maths::Vector& vertex : projectedVertices){
            sdlDrawPoint(this->renderer, vertex(0), vertex(1), 5);
        }
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
        assert(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)==0 && "Erreur de SDL_SetRenderDrawColor");
        for(auto mesh : scene.getMeshes()){
            drawMesh(mesh, camera);
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
