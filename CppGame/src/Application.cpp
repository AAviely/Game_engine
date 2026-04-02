#include "Application.hpp"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include <stdexcept>

namespace CppGame {

std::unordered_map<Uint32, std::string> mouse
    = {{SDL_BUTTON_LEFT, "SDL_BUTTON_LEFT"},
       {SDL_BUTTON_MIDDLE, "SDL_BUTTON_MIDDLE"},
       {SDL_BUTTON_RIGHT, "SDL_BUTTON_RIGHT"}};
std::unordered_map<SDL_Scancode, std::string> buttons
    = {{SDL_SCANCODE_A, "left"},
       {SDL_SCANCODE_D, "right"},
       {SDL_SCANCODE_W, "forward"},
       {SDL_SCANCODE_S, "backwards"}};

// The definition matches the header, but without the default (= "CppGame") arguments
Application::Application(
    std::string name,
    unsigned int Window_height,
    unsigned int Window_width,
    std::vector<std::string> script_files,
    std::vector<std::string> mesh_files
) {
    this->m_name          = name;
    this->m_Window_height = Window_height;
    this->m_Window_width  = Window_width;
    this->m_script_files  = script_files;
    this->m_mesh_files    = mesh_files;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        throw std::runtime_error(SDL_GetError());
    }
    m_window = SDL_CreateWindow(name.data(), Window_width, Window_height, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        throw std::runtime_error(SDL_GetError());
    }
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    m_keys     = SDL_GetKeyboardState(nullptr);
}

void Application::Tick() {
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_EVENT_QUIT:
                m_running = false;
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

                spdlog::info("Button: {}\n", mouse[m_event.button.button]);
        }  // keeping it switch for future use:)
    }

    for (const auto& [scan_code, move] : buttons) {
        if (m_keys[scan_code]) {
            spdlog::info("you moved {}\n", move);
        }
    }
}

void Application::MainLoop() {
    m_running = true;
    while (m_running) {
        Tick();
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

}  // namespace CppGame