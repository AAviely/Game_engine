
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include <CppGame.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace CppGame {
class Application {
   private:
    SDL_Renderer* m_renderer;
    std::vector<std::string> m_script_files;  // entity classes files
    std::vector<std::string> m_mesh_files;    // 3d models for the entities
    SDL_Window* m_window;

   public:
    std::string m_name;
    unsigned int m_Window_height;
    unsigned int m_Window_width;
    Application(
        std::string name                      = "CppGame",
        unsigned int Window_height            = 500,
        unsigned int Window_width             = 500,
        std::vector<std::string> script_files = {},
        std::vector<std::string> mesh_files   = {}
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
    }

    void Tick() {}

    void MainLoop() {
        bool running(true);
        while (running) {
            Tick();
        }
    }
};
}  // namespace CppGame

bool Receptor() { return true; }

// Fixed: Added 'return' keyword
auto a = []() -> bool { return Receptor(); }();