cmake_minimum_required(VERSION 3.10)

# set the project name
project(Joetracer)

file(GLOB SOURCES "[a-z0-9A-Z]*.cpp" "[a-z0-9A-Z]*.h")
# file(GLOB CUDA_SOURCES "[a-z0-9A-Z]*.cu" "[a-z0-9A-Z]*.hu")
# add_library(cuda STATIC
#		 Compute.cu)
# set_target_properties(cuda
#                      PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# c++11 standard
set(CMAKE_CXX_STANDARD 11)
set(IMGUI
    gui/imgui/imconfig.h
    gui/imgui/imgui.cpp
    gui/imgui/imgui.h
    gui/imgui/imgui_demo.cpp
    gui/imgui/imgui_draw.cpp
    gui/imgui/imgui_internal.h
    gui/imgui/imgui_widgets.cpp
    gui/imgui/imgui_tables.cpp
    gui/imgui/imstb_rectpack.h
    gui/imgui/imstb_textedit.h
    gui/imgui/imstb_truetype.h
    gui/imgui/backends/imgui_impl_sdl.cpp
    gui/imgui/backends/imgui_impl_sdl.h
    gui/imgui/backends/imgui_impl_sdlrenderer.cpp
    gui/imgui/backends/imgui_impl_sdlrenderer.h
)

# add the executable
add_executable(joetracer ${SOURCES} ${IMGUI})	

# set_property(TARGET joetracer
#             PROPERTY CUDA_SEPARABLE_COMPILATION ON)

# target_link_libraries(joetracer PRIVATE cuda)

# set(CMAKE_CXX_FLAGS "-O3 -march=native -flto -Wall -lSDL2 -lSDL2_image -fopenmp -Wformat")
set(CMAKE_CXX_FLAGS "-O3 -march=native -flto -Wall -lSDL2 -lSDL2_image -fopenmp -D_GLIBCXX_PARALLEL")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
