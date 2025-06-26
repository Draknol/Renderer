cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(renderer VERSION 0.2.1)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(assimp CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(renderer ${SRC_FILES})

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include $<TARGET_PROPERTY:glm::glm,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(renderer PRIVATE OpenGL::GL GLEW::GLEW glfw assimp::assimp)