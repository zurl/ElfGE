cmake_minimum_required(VERSION 3.6)
project(elfge)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        GameEngine/Core/GameObject.cpp
        GameEngine/Core/GameObject.h
        GameEngine/Common.h
        Main.cpp
        GameEngine/Components/Component.cpp
        GameEngine/Components/Component.h
        GameEngine/Components/MeshRenderer.cpp
        GameEngine/Components/MeshRenderer.h
        GameEngine/Shader/Material.cpp
        GameEngine/Shader/Material.h
        GameEngine/Shader/Shader.cpp
        GameEngine/Shader/Shader.h
        GameEngine/Core/Scene.cpp
        GameEngine/Core/Scene.h
        GameEngine/Core/Transform.cpp
        GameEngine/Core/Transform.h
        GameEngine/Utility.cpp
        GameEngine/Utility.h
        GameEngine/Components/Mesh.cpp
        GameEngine/Components/Mesh.h
        GameEngine/Exception.cpp
        GameEngine/Exception.h
        GameEngine/Components/Model.cpp
        GameEngine/Components/Model.h
        GameEngine/DefaultComponents/DefaultModel.cpp
        GameEngine/DefaultComponents/DefaultModel.h
        GameEngine/DefaultComponents/DefaultMesh.cpp
        GameEngine/DefaultComponents/DefaultMesh.h
        GameEngine/Components/Camera.cpp
        GameEngine/Components/Camera.h
        GameEngine/DefaultComponents/DefaultCamera.cpp
        GameEngine/DefaultComponents/DefaultCamera.h
        GameEngine/Core/Runtime.cpp
        GameEngine/Core/Runtime.h
        GameEngine/Core/Input.cpp
        GameEngine/Core/Input.h
        GameEngine/Components/GameScript.cpp
        GameEngine/Components/GameScript.h
        StandardAssets/Meshs/CubeMesh.cpp
        StandardAssets/Meshs/CubeMesh.h
        Assets/Scenes/DemoScene.h
        Assets/Entry.cpp
        Assets/Entry.h
        GameEngine/ELFGE.h
        GameEngine/DefaultComponents/DefaultMaterial.cpp
        GameEngine/DefaultComponents/DefaultMaterial.h
        GameEngine/Shader/ShaderManager.cpp
        GameEngine/Shader/ShaderManager.h
        Assets/Prefabs.h GameEngine/Shader/LightingManager.cpp GameEngine/Shader/LightingManager.h GameEngine/Components/Lighting.cpp GameEngine/Components/Lighting.h StandardAssets/Lightings/PointLighting.cpp StandardAssets/Lightings/PointLighting.h)

find_library(OPENGL OpenGL)
find_library(GLFW glfw)
find_library(GLEW glew)
find_library(ASSIMP assimp)
link_libraries(${GLFW} ${GLEW} ${OPENGL} ${ASSIMP})
add_executable(elfge ${SOURCE_FILES})