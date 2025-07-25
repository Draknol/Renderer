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
learnopengl.com
    return 0;
}
```
### goal:
My eventual goal for this project is to make a simple 3D renderer with textures, file loading (eg .obj), camera controls and hopefully some lighting.
## Version 0.0.1
### description:
I've added a `GLFWwindow` with a plain blue background, resizing (not visible on blank window) using a callback, which works similar to sfml's event system, and input processing (escape closes window).
I found a good tutorial at [learnopengl.com](https://learnopengl.com) which covers most of the basics of OpenGL with clear explanations which has been a big help.
I decided to use OpenGL 3.3 as it is a common starting point and later versions mostly only add features beyond the scope of this project.
### goal:
Next I'm planning to get to the stage of rendering a triangle and by extension, other simple 2D geometry. I have a decent understanding of vertex arrays from sfml but it will be interesting getting to use shaders which I haven't used for anything before.
## Version 0.0.2
### description:
Rendering of 2D geometry is now possible. I have tested triangles, squares and messed around with circles. Even at 10 million vertices my PC was still able to render at ~30fps which while I imagine that will decrease as I add more complexity I am definitely getting a feel for the efficiency of OpenGL. I have learnt about `VAO`s (Vertex Array Objects), which are very effectively the same as vertex arrays in sfml, `VBO`s (Vertex Buffer Objects), which allow batching vertices together to improve efficiency of sending information to the GPU, and touched on shaders, compiling a very simple vertex and fragment shader as a placeholder. Shaders were something I hadn't made use of in sfml so I am looking forward to gaining a better understanding of how they work. The tutorial also covers `EBO`s (Element Buffer Objects), which are arrays of indices that allow for reuse of vertices. I haven't implemented an `EBO` yet although they will likely be very useful once I get to more complex geometry.
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
Shaders are now also loaded from files which is much nicer to work with than editing a `const char*`. Since I was starting to have a fair number of loose files I decided to make a shader folder for the shader files and a src folder for the cpp files. I also made a `Shader` class to handle the shader interactions more tidily. I'm thinking of doing something similar for verticies but I'll probably leave that until I am reading from `.obj` files.
I did also learn about uniforms, which are effictivly global variables that are visable to all vertices as they are being processed, allowing for interesting effects like animating colors.
### goal:
My next feature will be support for textures which I don't imagine will take me too long as I already have a decent understanding of image files and texture coordinates work.
## Version 0.0.4
### description:
Textures are now supported, with texture coordinates stored in `Vertex`. I also moved `Vertex` to a class instead of a struct, which while I didn't necessarily need it for textures, I imagine it will make the code a lot tidier when `Vertex` is doing more.
`Texture`s are loaded using `stb_image.h`. Currently it only seems to work for texture sizes of powers of 2 (eg 512x512). I'm not sure if this is a bug in my code or a limitation of the way I've implemented it.
I've also updated the cmake file to include `glm`, which contains math functionality for OpenGL. I will need this for rotating objects later.
I also changed colors from being stored as 4 `float`s to a `uint`. This is to allow me to work with hex values which I'm more familiar with, instead of rgb percents. This also saves 12 bytes of memory per `Vertex`.
I also updated the `Shader` class as there was a bug causing the shaders to not compile correctly sometimes, due to how I was reading them into the `char*`. Reading into an `std::string` and using `.c_str()` seemed to fix this.
### goal:
Next is transformations, which allow for motion and 3D. This will require vector and matrix operations which I have a lot of practice with. It will be interesting to apply some of my math to a programming project as I haven't needed to operate on matrices for a project before.
## Version 0.1.0
![Spinning cubes preview](screenshots/Spinning%20Cubes.gif)
### description:
3D is now supported! I've added a `VertexArray` class to make using `VBO`s, `VAO`s and `EBO`s tidier. I've also given it a transform matrix using `glm`, along with functions for scaling, rotating and translating.
I've added a temporary camera in `VertexArray` to get perspective.
```c++
// Temporary camera
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
```
This isn't ideal but it works for now until I have a camera class (and likely a window class). As a result of the perspective the view now also extends when the window is resized instead of stretching.
I also merged the 2 load shader functions into one. It now takes a `GLenum` to determine what type of shader it is loading in.
I wanted to stress test what I have so far so there is also now an fps counter. I was able to get ~60fps with 20k cubes which is decent but I imagine I could do a lot better if I add instancing.
In `Vertex.h` I decided to change the `GLfloats` and `GLuint` to use `glm` instead. While this likely has little effect on performance it makes the code tidier and slightly more readable.
`EBO`s are also now supported. After trying to only have 8 vertices per cube I discovered that textures limit how I can use `EBO`s. This is due to each `Vertex` having its texture coordinates, requiring each face's textures to have the same coordinate at the corners of the cube. I'm fairly confident that this is mathematically impossible and that I will likely need to make a UV texture if I want to reduce vertex count further.
Back face culling is now also enabled, and after adjusting the winding order of a few triangles only the outside of the cubes render.
### goal:
I'm hoping to get both a camera and window class working next, along with potentially support for instancing meshes.
## Version 0.1.1
### description:
There are now `Window` and `View` classes. This a smaller change, not really adding anything functionally.
The `Window` class handles the GLFWwindow and the drawing of VertexArrays, while `View` is mostly empty for now but will have more when I add a proper camera.
I also wasn't super happy with only 20k cubes (240k vertices) at 60fps so I ran a profiler on the code.
In the end I found it wasn't due to my code but just that drawing lots of objects separately is inefficient.
Increasing the vertex count of each cube instead of drawing more objects I could get a much higher vertex count in real time (3 million verts at ~45fps). This was reassuring as it means once I can read meshes in from files I should be able to render some decently high poly models. I also noticed that the CPU was spending a lot of time finding out what the current shader program was and the location of the uniform for transform. Changing this so the locations are stored and only updated when the program is changed massively reduced CPU usage when drawing lots of vertices to practically 0 (which makes sense since the almost entire load should be on the GPU).
### goal:
As I still haven't added it, a camera is still next on my list
## Version 0.1.2
### description:
A proper camera has now been added, with the ability to fly and look around. For now variables like fov and sensitivity are stored in the view class, which I would like to change eventually to make them easier to change.
Using cross products to get left and right was also very interesting and not how I would've thought to do it.
I've now also finished the "getting started" chapter and can now move on to more advanced features like lighting, model loading and maybe some PBR.
### goal:
Next on the list is lighting but I would like to have a proper model to light first. Up until now I've needed to make meshes vertex by vertex which is very slow and I'm really looking forward to loading a proper model into my engine.
## Version 0.1.3
![Donut model](screenshots/Donut.png)
### description:
Models can now be loaded in from .obj files. I've added a donut model I made a while ago following a [BlenderGuru](https://www.youtube.com/@blenderguru) tutorial.
Adding this broke a lot more things that any other previous addition.
Due to `Textures` being copied during the loading process, when the old copy was deleted the texture would get unloaded, causing them to not display. My solution was to add a `GLuint*` shared between copies that keeps track of how many there are, only deleting the texture when the last `~Texture` is called. I also removed `VertexArray` as it has been fully replaced by `Mesh`. This does mean that transforms no longer work but I'm planning to fix this when I do instancing.
### goal:
My next goal is getting instancing working and hopefully fixing the transforms so I can get a few donuts spinning around.
## Version 0.2.0
![Donut model](screenshots/1m%20Spinning%20Cubes.gif)
### description:
Models now support instancing. Instancing didn't have as big of an impact as I had hoped for the donut model, however I can now draw lots of smaller models (I tested with cubes). I am able to render 1 million spinning cubes at around 200fps. The idea of using something like this to make a voxel engine intrests me and is something I would like to have a go at in the future.
Instances each have their own `worldTransform`, but also share a `localTransform`. This allows for making adjustments to all the models at the same time, which is both easier to work with and lighter on the CPU.
I also added a cache to the `Shader` class to store uniform locations as the CPU was spending a lot of time asking for them. This reduced CPU usage (for 1m cubes) from 10% down to <1%.
### goal:
The next feature to add is Phong lighting.
## Version 0.2.1
![Donut model](screenshots/Lighting%20Donut.gif)
### description:
There is now basic lighting with specular. Material properties (ambient, specular and shininess) are loaded from the .mtl file. I am currently doing a lot of the calculations that only need to be done per instance, per vertex. I'm not sure if it's worth moving them to the CPU but it is something I would like to look into.
Understanding why the diffuse works is fairly intuitive to me but I'm not sure I fully understand the effect of shininess just yet and will need to have a look for a more detailed explaination of how the `pow` effects the final result.

### goal:
Next on the list is adding multiple types of lights (directional, point and spotlight).
## Version 0.2.2
![Different lights](screenshots/Multiple%20Lights.gif)
### description:
Directional, point and spotlights are now added.
Directional:
```c++
struct DirectionalLight {
    vec3 direction;
    vec3 color;
};
```
Directional lights have only a direction and a color. This works like the light I had to start with, with the only difference being the `lightDir` is fixed instead of taking into account the locations of the light and fragment.

Point:
```c++
struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};
```

The point lights have a position and 3 terms to determine the fade out of the light over distance. This works like the first light but now with an attenuation, causing it to be brighter closer.
This decay is calculated with:
```c++
1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist)
```
The constant, linear and quadratic terms controling the rate of decay with respect to distance.

Spotlight:
```c++
struct Spotlight {
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutOff;
    float constant;
    float linear;
    float quadratic;
};
```

Spotlight is similar to point light but with a direction and cut off angle. The direction is used to calculate the angle between the light and the fragment which is then compared with the cut off. For now anything beyond the cut off is 0 and anything inside is 1 but ideally I would add a fade to smoothen the edge out which is on the to do list.

I've also added support for multiple lights. Currently the number of point/spotlights is constant which wouldn't be ideal in practice but it works for the sake of learning lighting. Apparently there are better options for having variable light counts in later versions of openGL which I might look into in a future project.
### goal:
My next goal is to update the lighting to Blinn-Phong lighting. I imagine this will be more a matter of learning how it works as opposed to being particularly hard to add as a feature.
## Version 0.2.3
### description:
I've updated the lighting to Blinn-Phong which used the halfway vector between the light and the view instead of the reflection direction. In theory this is faster but as I am currently recalculating it for every fragment (not ideal but good enough for what I'm doing) it would likely be slightly slower. The other benefit is that it produces better results with low shininesses where Phong lighting can cut off part of the specular lighting.
Since this was a fairly quick addition I also made the scroll wheel adjust the camera speed, which I've been meaning to add for a while.
### goal:
The next and likely final (at least for now) goal is to add shadows.
## Version 1.0.0
![Shadows](screenshots/Shadows.png)
### description:
Shadows were definitely the most challenging addition by far. I started with the directional lights and after many failed attempts got the shadow map rendering correctly.
When rendering shadow maps since the light is at an angle to the surface only some of the shadow is visible. This is called shadow acne and it makes the shadows render in stripes.
To fix this I needed to add a bias, based on the angle, to move the shadow map to ensure the whole shadow is above the surface. This however has 2 side-effects, objects close together can end up self shadowing and there can be a gap (peter-panning) between the shadow and the object. The solution to peter-panning is to cull the front faces instead of the back faces. It took a lot of trial and error, adjusting values and updating the donut mesh to not have as much overlapping geometry, to get a result I was reasonably happy with.
After tidying up my directional light implementation, adding spotlights wasn't much different. I quickly noticed a massive drop in performance compared to before. I eventually found it was due to effectively rendering 50 fairly high poly donut meshes 6 times (1 directional, 4 spotlight and 1 to window) which is around 23m vertices being rendered. While I'm sure there is a nice way to avoid this, I opted for reducing the vertex count of the donuts which increased performance by roughly 10x.
For the point lights I opted to not add shadows as while it would be better I'm content for now with having directional and spotlight shadows and pointlights unshadowed.
I also added MSAA to reduce aliasing and PFC to the shadows, which effectively blurs the shadows by averaging the surrounding pixels to remove the sharp edges caused by the pixels of the shadow map.
### future plans:
I am happy with where this project is for now and plan to move onto something else now. I have definitely learnt a lot about OpenGL and rendering in general. Going forward I'd like to have a go at making something with voxels or marching cubes, maybe some terrain generation. I'm looking forward to applying my new knowledge to a project and seeing what I can make.