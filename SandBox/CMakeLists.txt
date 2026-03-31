add_executable(SandBox)


target_include_directories(SandBox PRIVATE include)


target_sources(SandBox PRIVATE
    src/main.cpp
)


target_link_libraries(SandBox PRIVATE 
    SDL3::SDL3
    spdlog::spdlog
    fmt::fmt
    decor-0
    CppGame
)