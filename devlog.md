# Devlog
A place for me to track my progress towards the project and learning OpenGL
## Version 0.0.0
### description:
I have set up a project with a CMake file for OpenGL includes and a main.cpp with placeholder code.
```c++
#include <iostream>

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello World!";

    return 0;
}
```
### goal:
My eventual goal for this project it to make a simple 3D renderer with textures, file loading (eg .obj), camera controls and hopefully some lighting.