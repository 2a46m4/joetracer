# A simple Makefile for compiling small SDL projects

# set the compiler
CC := clang++

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2 -lm
# add header files here
HDRS := Scene.h utils/Point.h utils/Ray.h utils/Sphere.h utils/Vec.h utils/VectorOps.h utils/Triangle.h utils/TriangleList.h PinholeCamera.h utils/Surfel.h utils/Light.h utils/Materials.h

# add source files here
SRCS := main.cpp Scene.cpp utils/Point.cpp utils/Ray.cpp utils/Sphere.cpp utils/Vec.cpp utils/VectorOps.cpp utils/Triangle.cpp utils/TriangleList.cpp PinholeCamera.cpp utils/Surfel.cpp utils/Light.cpp utils/Materials.cpp

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := Joetracer

# default recipe
all: $(EXEC)
 
showfont: showfont.c Makefile
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LIBS)

glfont: glfont.c Makefile
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean