cmake_minimum_required(VERSION 3.6)
project(elfge)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        GameEngine/Core/GameObject.cpp
        GameEngine/Core/GameObject.h
        GameEngine/Common.h
        Main.cpp
        GameEngine/Core/Component.cpp
        GameEngine/Core/Component.h
        GameEngine/Graphics/Components/Renderer.cpp
        GameEngine/Graphics/Components/Renderer.h
        GameEngine/Graphics/Components/Material.h
        GameEngine/Graphics/Shader.cpp
        GameEngine/Graphics/Shader.h
        GameEngine/Core/Scene.cpp
        GameEngine/Core/Scene.h
        GameEngine/Core/Transform.cpp
        GameEngine/Core/Transform.h
        GameEngine/Core/Utility.cpp
        GameEngine/Core/Utility.h
        GameEngine/Graphics/Components/Mesh.h
        GameEngine/Exception.cpp
        GameEngine/Exception.h
        GameEngine/Graphics/Components/Model.h
        StandardAssets/Models/DefaultModel.cpp
        StandardAssets/Models/DefaultModel.h
        StandardAssets/Meshs/DefaultMesh.cpp
        StandardAssets/Meshs/DefaultMesh.h
        GameEngine/Core/Camera.h
        StandardAssets/Cameras/FirstPlayerCamera.cpp
        StandardAssets/Cameras/FirstPlayerCamera.h
        GameEngine/Core/Runtime.cpp
        GameEngine/Core/Runtime.h
        GameEngine/Core/Input.cpp
        GameEngine/Core/Input.h
        GameEngine/Core/GameScript.cpp
        GameEngine/Core/GameScript.h
        StandardAssets/Meshs/CubeMesh.cpp
        StandardAssets/Meshs/CubeMesh.h
        Assets/Scenes/DemoScene.h
        Assets/Entry.cpp
        Assets/Entry.h
        GameEngine/GameEngine.h
        StandardAssets/Materials/BlankMaterial.cpp
        StandardAssets/Materials/BlankMaterial.h
        GameEngine/Graphics/ShaderManager.cpp
        GameEngine/Graphics/ShaderManager.h
        StandardAssets/ShadowMapping/DirectionalShadowMappingManager.cpp
        StandardAssets/ShadowMapping/DirectionalShadowMappingManager.h
        StandardAssets/BoringHow/Terrain.cpp
        StandardAssets/BoringHow/Terrain.h
        Assets/Prefabs.h GameEngine/Graphics/LightingManager.cpp GameEngine/Graphics/LightingManager.h GameEngine/Graphics/Components/Lighting.cpp GameEngine/Graphics/Components/Lighting.h StandardAssets/Lightings/PointLighting.cpp StandardAssets/Lightings/PointLighting.h StandardAssets/Lightings/DirectLighting.cpp StandardAssets/Lightings/DirectLighting.h StandardAssets/Materials/StandardMaterial.cpp StandardAssets/Materials/StandardMaterial.h StandardAssets/Cameras/DefaultCamera.cpp StandardAssets/Cameras/DefaultCamera.h StandardAssets/StandardAssets.h GameEngine/Graphics/TextureManager.cpp GameEngine/Graphics/TextureManager.h GameEngine/Graphics/Texture.h Assets/FuckScript.cpp Assets/FuckScript.h StandardAssets/Physics/Colliders/AABBCollider.cpp StandardAssets/Physics/Colliders/AABBCollider.h StandardAssets/Physics/Colliders/Collider.h StandardAssets/Physics/RigidBody.cpp StandardAssets/Physics/RigidBody.h GameEngine/UI/Text.cpp GameEngine/UI/Text.h GameEngine/UI/Canvas.cpp GameEngine/UI/Canvas.h GameEngine/UI/Font/FontManager.cpp GameEngine/UI/Font/FontManager.h GameEngine/UI/Font/FontFace.cpp GameEngine/UI/Font/FontFace.h GameEngine/UI/UI.h GameEngine/Graphics/GraphicsRuntime.cpp GameEngine/Graphics/GraphicsRuntime.h GameEngine/Graphics/ShadowMappingManager.h GameEngine/Graphics/DebugUtility.cpp GameEngine/Graphics/DebugUtility.h StandardAssets/ShadowMapping/OmnidirectionalShadowMappingManager.cpp StandardAssets/ShadowMapping/OmnidirectionalShadowMappingManager.h GameEngine/UI/Image.cpp GameEngine/UI/Image.h Assets/Prefabs.cpp GameEngine/Core/Prefab.h)

include_directories("./Dependency")
include_directories("./GameEngine")
include_directories("./StandardAssets")

IF (WIN32)
    MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
    include_directories("/usr/local/Cellar/freetype/2.7.1/include/freetype2")
    MESSAGE(STATUS "Now is Apple systens.")
    find_library(OPENGL OpenGL)
    find_library(GLFW glfw)
    find_library(GLEW glew)
    find_library(ASSIMP assimp)
    find_library(FREETYPE freetype)
    link_libraries(${GLFW} ${GLEW} ${OPENGL} ${ASSIMP} ${FREETYPE})
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's. Including aPPLE os x  and CygWin")
ENDIF ()

add_executable(elfge ${SOURCE_FILES})