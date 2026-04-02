#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <vector>

namespace CppGame {
class Application {
   private:
    SDL_Event m_event;
    bool m_running;
    SDL_Renderer* m_renderer;
    std::vector<std::string> m_script_files;  // entity classes files
    std::vector<std::string> m_mesh_files;    // 3d models for the entities
    SDL_Window* m_window;

   public:
    const bool* m_keys;
    std::string m_name;
    unsigned int m_Window_height;
    unsigned int m_Window_width;

    // Default arguments ONLY go in the header file
    Application(
        std::string name                      = "CppGame",
        unsigned int Window_height            = 500,
        unsigned int Window_width             = 500,
        std::vector<std::string> script_files = {},
        std::vector<std::string> mesh_files   = {}
    );

    void MainLoop();
    void Tick();
};
}  // namespace CppGame