// game_engine.cpp
#include <SDL2/SDL.h>
#include <iostream>

class GameEngine {
public:
    GameEngine() : window(nullptr), renderer(nullptr), isRunning(false) {}

    bool init(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            SDL_DestroyWindow(window);
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        isRunning = true;
        return true;
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }

    void update() {
        // Game logic goes here
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Rendering logic goes here

        SDL_RenderPresent(renderer);
    }

    void clean() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool running() { return isRunning; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
};

extern "C" {
    GameEngine* GameEngine_new() { return new GameEngine(); }
    bool GameEngine_init(GameEngine* engine, const char* title, int width, int height) { return engine->init(title, width, height); }
    void GameEngine_handleEvents(GameEngine* engine) { engine->handleEvents(); }
    void GameEngine_update(GameEngine* engine) { engine->update(); }
    void GameEngine_render(GameEngine* engine) { engine->render(); }
    void GameEngine_clean(GameEngine* engine) { engine->clean(); }
    bool GameEngine_running(GameEngine* engine) { return engine->running(); }
}
