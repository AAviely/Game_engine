#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include <CppGame.hpp>
#include <unordered_map>

int main(int argc, char* argv[]) {
    std::unordered_map<Uint32, std::string> mouse
        = {{SDL_BUTTON_LEFT, "SDL_BUTTON_LEFT"},
           {SDL_BUTTON_MIDDLE, "SDL_BUTTON_MIDDLE"},
           {SDL_BUTTON_RIGHT, "SDL_BUTTON_RIGHT"}};
    std::unordered_map<SDL_Scancode, std::string> buttons
        = {{SDL_SCANCODE_A, "left"},
           {SDL_SCANCODE_D, "right"},
           {SDL_SCANCODE_W, "forward"},
           {SDL_SCANCODE_S, "backwards"}};
    spdlog::info("Starting Game Engine Sandbox...");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        spdlog::error("Failure initializing SDL3: {}", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("My Game Engine - SDL3", 700, 700, SDL_WINDOW_RESIZABLE);
    if (!window) {
        spdlog::error("Failed to create window: {}", SDL_GetError());
        return -1;
    }

    // 1. Create a graphics renderer to talk to your GPU
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    const bool* keys       = SDL_GetKeyboardState(nullptr);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Process Inputs
        int keys_length;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;
                // case SDL_EVENT_MOUSE_MOTION:
                //     spdlog::info(
                //         "mouse    = ({},{})\nrelative motion = ({},{})\n",
                //         event.motion.x,
                //         event.motion.y,
                //         event.motion.xrel,
                //         event.motion.yrel
                //     );
                //     break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:

                    spdlog::info("Button: {}\n", mouse[event.button.button]);
            }  // keeping it switch for future use:)
        }

        for (const auto& [scan_code, move] : buttons) {
            if (keys[scan_code]) {
                spdlog::info("you moved {}\n", move);
            }
        }
        // 2. Clear the screen with a dark gray color (R: 30, G: 30, B: 30)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // 3. Push the drawn pixels to Wayland (This makes the window appear!)
        SDL_RenderPresent(renderer);

        // 4. Sleep for ~16ms so we don't melt your CPU running at 10,000 FPS
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}