cmake_minimum_required(VERSION 3.10)

# set the project name
project(Joetracer
	VERSION 0.1
	DESCRIPTION "A project path-tracer"
	LANGUAGES CXX)
	
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(IMGUI
    include/imgui/imconfig.h
    include/imgui/imgui.cpp
    include/imgui/imgui.h
    include/imgui/imgui_demo.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_internal.h
    include/imgui/imgui_widgets.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imstb_rectpack.h
    include/imgui/imstb_textedit.h
    include/imgui/imstb_truetype.h
    include/imgui/backends/imgui_impl_sdl.cpp
    include/imgui/backends/imgui_impl_sdl.h
    include/imgui/backends/imgui_impl_sdlrenderer.cpp
    include/imgui/backends/imgui_impl_sdlrenderer.h
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add the executable
# is there really no better way to do this?
add_executable(joetracer
	       src/aabb.cpp
	       src/aaRect.cpp
	       src/BVHNode.cpp
	       src/Functions.cpp
	       src/onb.cpp
	       src/PinholeCamera.cpp
	       src/Point.cpp
	       src/RandomGenerator.cpp
	       src/Ray.cpp
	       src/Scene.cpp
	       src/sdl.cpp
	       src/Sphere.cpp
	       src/Vec3.cpp
	       ${IMGUI})	


target_link_libraries(joetracer Eigen3::Eigen)

set(CMAKE_CXX_FLAGS "-Ofast -march=native -flto -Wall -lSDL2 -lSDL2_image -fopenmp -Wformat")
# set(CMAKE_CXX_FLAGS "-O0 -g -march=native -flto -Wall -lSDL2 -lSDL2_image -fopenmp -Wformat")
# set(CMAKE_CXX_FLAGS "-O3 -march=native -flto -Wall -lSDL2 -lSDL2_image -fopenmp -D_GLIBCXX_PARALLEL")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
