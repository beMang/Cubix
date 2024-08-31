#include "instance.hpp"
#include <cassert>

namespace app {
    Instance::Instance() : 
        status(EXIT_FAILURE),
        window(NULL), 
        show_fps(false), 
        quit(false), 
        renderer(NULL), 
        camera(objects::Camera(maths::Vector(0,0,0), maths::Vector(0,0,0), 1, 1)) 
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

        //init the renderer
        //init the scene and load the objects in memory
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
        exit();
    }

    int Instance::exit()
    {
        if (window!=NULL) SDL_DestroyWindow(window);
        if (renderer!=nullptr) renderer->close();
        SDL_Quit();
        return status;
    }

    void Instance::showFps()
    {
        show_fps = !show_fps;
    }
}
