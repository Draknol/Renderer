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
My eventual goal for this project is to make a simple 3D renderer with textures, file loading (eg .obj), camera controls and hopefully some lighting.
## Version 0.0.1
### description:
I've added a GLFWwindow with a plain blue background, resizing (not visible on blank window) using a callback, which works similar to sfml's event system, and input processing (escape closes window).
I found a good tutorial at ()[learnopengl.com] which covers most of the basics of OpenGL with clear explanations which has been a big help.
I decided to use OpenGL 3.3 as it is a common starting point and later versions mostly only add features beyond the scope of this project.
### goal:
Next I'm planning to get to the stage of rendering a triangle and by extension, other simple 2D geometry. I have a decent understanding of vertex arrays from sfml but it will be interesting getting to use shaders which I haven't used for anything before.
