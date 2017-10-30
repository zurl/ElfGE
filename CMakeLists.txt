cmake_minimum_required(VERSION 3.6)
project(elfge)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        GameObject.cpp
        GameObject.h
        Common.h
        Main.cpp
        Component.cpp
        Component.h
        MeshRenderer.cpp
        MeshRenderer.h
        Material.cpp
        Material.h
        Shader.cpp
        Shader.h
        Scene.cpp
        Scene.h
        Transform.cpp
        Transform.h
        Utility.cpp
        Utility.h
        Mesh.cpp
        Mesh.h
        Exception.cpp
        Exception.h
        Model.cpp
        Model.h
        DefaultModel.cpp
        DefaultModel.h
        DefaultMesh.cpp
        DefaultMesh.h
        Camera.cpp
        Camera.h
        DefaultCamera.cpp
        DefaultCamera.h
        Runtime.cpp
        Runtime.h Input.cpp Input.h GameScript.cpp GameScript.h)

find_library(OPENGL OpenGL)
find_library(GLFW glfw)
find_library(GLEW glew)
find_library(ASSIMP assimp)
link_libraries(${GLFW} ${GLEW} ${OPENGL} ${ASSIMP})
add_executable(elfge ${SOURCE_FILES})