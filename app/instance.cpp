#include "instance.hpp"
#include <cassert>
#include <iostream>
#include "../rendering/sdl_render.hpp"

namespace app {
    Instance::Instance() : 
        status(EXIT_FAILURE),
        window(NULL), 
        show_fps(false), 
        quit(false), 
        camera(objects::Camera(maths::Vector(0,0,0), maths::Vector(0,0,0), 1, 1)),
        renderer(NULL),
        scene(Scene("default"))
    {
        if(SDL_TRUE){
            SDL_version *version = (SDL_version*)malloc(sizeof(SDL_version));
            SDL_GetVersion(version);
            printf("SDL version : %d.%d.%d\n", version->major, version->minor, version->patch);
            free(version);
        }
    }

    Instance::~Instance() {
        exit();
    }

    void Instance::init() {
        using namespace maths;
        using namespace objects;

        assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "SDL_Init failed");
        window = SDL_CreateWindow("Cubix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_VULKAN);
        assert(window != NULL && "SDL_CreateWindow failed");

        this->renderer = new rendering::SdlRender(window, scene, camera);
        renderer->init();

        //create objects
        this->scene.addMesh(Mesh("model/cube.obj", Vector(0,0,4), Vector(0,0,0), 1));
    }

    void Instance::loop() {
        const int TARGET_FPS = 60;
        while (!this->quit)
        {
            Uint64 t1;
            if(show_fps){
                t1 = SDL_GetTicks64();
            }

            /** Renderer consiretation
            if(SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a)!=0) {
                fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
                goto Quit;
            }
            if(SDL_RenderClear(renderer)!=0) {
                fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
                goto Quit;
            }
             */

            //handle events
            //handleKeyboard(this->camera, &quit, this->event);
            //handleMouse(camera);
            SDL_PumpEvents();
            while(SDL_PollEvent(&(this->event)))
                if(event.type == SDL_QUIT) this->quit = true;

            //update the scene
            //objects::Mesh& o1 = this->scene.getMeshes()[0];
            //o1.translateZ(-0.01);

            //Draw the scene
            //draw_object(renderer, camera, &blue, cube);
            //draw_object(renderer, camera, &red, custom_object);

            //SDL_RenderPresent(renderer);
            if(renderer!=nullptr){
                renderer->clean();
                renderer->render();
            }

            SDL_Delay((int)(1/TARGET_FPS*1000));

            if(show_fps){
                Uint64 t2 = SDL_GetTicks64();
                float time = ((float) (t2-t1))/1000;
                printf("fps : %f.1 \n", 1/time); //SHOW FPS COUNTER IN TERMINAL
            }
        }
    }

    int Instance::exit()
    {
        cout << "Exiting..." << endl;
        if (window!=NULL) SDL_DestroyWindow(window);
        if (renderer!=nullptr) delete renderer;
        SDL_Quit();
        return this->status;
    }

    void Instance::showFps()
    {
        show_fps = !show_fps;
    }
}
