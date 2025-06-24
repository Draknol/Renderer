# Renderer
A simple 3D renderer made using OpenGL

![Spinning donuts preview](screenshots/Spinning%20Donuts.gif)

## Description

This is a small project with which I'm aiming towards making a 3D renderer able to load and render .obj (or equivalent) files.
I am currently following [learnopengl.com](https://learnopengl.com) but would like to branch off eventually.
My eventual goal is to implement features including a moveable camera, lighting, post processing effects and hopefully much more.

## Compiling

1. Install [CMake](https://cmake.org/download) (3.28 or later)
2. Install dependencies: OpenGL, GLEW, GLFW3, GLM and assimp
3. Clone the repository: `git clone https://github.com/Draknol/Renderer`
4. Inside a build directory run: `cmake ..` (Change `SHADER_PATH` and `MODEL_PATH` if not running from project root)
5. To build: `cmake --build .`
6. To run: ./renderer

## Features

- Texturing with UV coordinates
- Vertex coloring
- Simple shaders
- GLSL shader file loading
- Texture loading (using stb_image.h)
- Model loading (using assimp)
- Instancing support
- 3D transformation with scaling, rotation, and translation
- Back face culling
- Support for EBOs
- FPS counter