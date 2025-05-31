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
## Version 0.0.2
### description:
Rendering of 2D geometry is now possible. I have tested triangles, squares and messed around with circles. Even at 10 million vertices my PC was still able to render at ~30fps which while I imagine that will decrease as I add more complexity I am definitely getting a feel for the efficiency of OpenGL. I have learnt about VAOs (Vertex Array Objects), which are very effectively the same as vertex arrays in sfml, VBOs (Vertex Buffer Objects), which allow batching vertices together to improve efficiency of sending information to the GPU, and touched on shaders, compiling a very simple vertex and fragment shader as a placeholder. Shaders were something I hadn't made use of in sfml so I am looking forward to gaining a better understanding of how they work. The tutorial also covers EBOs (Element Buffer Objects), which are arrays of indices that allow for reuse of vertices. I haven't implemented an EBO yet although they will likely be very useful once I get to more complex geometry.
### goal:
Next I'll be making some more interesting shaders (the current ones are placeholders) and learning some GLSL.
