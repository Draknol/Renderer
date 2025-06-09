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
## Version 0.0.3
### description:
New shaders have been added and the vertices array now contains color data with rgb values.
```c++
float vertices[] = {
//    x       y      z      r     g     b    
    -0.5f,  -0.5f,  0.0f,  0.2f, 0.7f, 0.1f,
    -0.25f, -0.25f, 0.0f,  0.9f, 0.3f, 0.4f,
     0.5f,  -0.5f,  0.0f,  0.1f, 0.5f, 0.9f,
     0.25f, -0.25f, 0.0f,  0.6f, 0.4f, 0.9f,
     0.5f,   0.5f,  0.0f,  0.3f, 0.2f, 0.8f,
     0.25f,  0.25f, 0.0f,  0.0f, 0.9f, 0.6f,
    -0.5f,   0.5f,  0.0f,  0.8f, 0.1f, 0.7f,
    -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.3f,
    -0.5f,  -0.5f,  0.0f,  0.2f, 0.7f, 0.1f,
    -0.25f, -0.25f, 0.0f,  0.9f, 0.3f, 0.4f
};
```
Shaders are now also loaded from files which is much nicer to work with than editing a const char*. Since I was starting to have a fair amount of loose files I decided to make a shader folder for the shader files and a src folder for the cpp files. I also made a Shader class to handle the shader interactions more tidily. I'm thinking of doing something similar for verticies but I'll probably leave that until I am reading from .obj files.
I did also learn about uniforms, which are effictivly global variables that are visable to all vertices as they are being processed, allowing for interesting effects like animating colors.
### goal:
My next feature will be support for textures which I don't imagine will take me too long as I already have a decent understanding of image files and texture coordinates work.
## Version 0.0.4
### description:
Textures are now supported, with texture coordinates stored in Vertex. I also moved Vertex to a class instead of a struct, which while I didn't necessarily need it for textures, I imagine it will make the code a lot tidier when Vertex is doing more.
Textures are loaded using stb_image.h. Currently it only seems to work for texture sizes of powers of 2 (eg 512x512). I'm not sure if this is a bug in my code or a limitation of the way I've implemented it.
I've also updated the cmake file to include glm, which contains math functionality for OpenGL. I will need this for rotating objects later.
I also changed colors from being stored as 4 floats to a uint. This is to allow me to work with hex values which I'm more familiar with, instead of rgb percents. This also saves 12 bytes of memory per Vertex.
I also updated the Shader class as there was a bug causing the shaders to not compile correctly sometimes, due to how I was reading them into the char*. Reading into an std::string and using .c_str() seemed to fix this.
### goal:
Next is transformations, which allow for motion and 3D. This will require vector and matrix operations which I have a lot of practice with. It will be interesting to apply some of my math to a programming project as I haven't needed to operate on matrices for a project before.
