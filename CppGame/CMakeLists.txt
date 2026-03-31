add_library(CppGame SHARED)

target_include_directories(CppGame PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(CppGame PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_sources(CppGame PRIVATE
    src/CppGame.cpp
)

target_link_libraries(CppGame PRIVATE
    SDL3::SDL3
    spdlog::spdlog
    fmt::fmt
    decor-0
)
