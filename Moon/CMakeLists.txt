cmake_minimum_required (VERSION 3.20)

project("Moon")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_compile_definitions(MOON_DEBUG)
endif()

set(RESOURCE "${CMAKE_SOURCE_DIR}/Moon/Resources/Engine.rc")

add_library (${PROJECT_NAME} "main.cpp" 
"Graphics/RenderDevice.h" "Graphics/RenderDevice.cpp"
"Graphics/RenderCore.h" 
"Core/MoonCore.h" 
"Log/Log.h"  
"FileSystem/FileSystem.h" "FileSystem/FileSystem.cpp" 
"Window/Window.h" "Window/WindowCore.h" "Window/Window.cpp" 
"Resources/Resource.h" 
"Assets/ConstantBufferTypes.h" 
"Timer/Timer.h" "Timer/Timer.cpp" 
"Assets/TextureObject.h" "Assets/TextureObject.cpp" 
"Assets/SpriteObject.h" "Assets/SpriteObject.cpp" 
"EntityComponent/Entity.h" 
"EntityComponent/EntityCore.h" 
"EntityComponent/Components/SpriteAnimation.h" 
"EntityComponent/Components/Transform.h" 
"EntityComponent/Components/SpriteRenderer.h" 
"EntityComponent/Components/BoxCollision2D.h" 
"EntityComponent/Component.h" 
"Assets/AnimationClipObject.h" "Assets/SpriteObjectData.h" "Assets/RenderObject.h" "Assets/RenderObject.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} "d3d11.lib")
target_link_libraries(${PROJECT_NAME} "dxgi.lib")
target_link_libraries(${PROJECT_NAME} "d3dcompiler.lib")
target_link_libraries(${PROJECT_NAME} "Stbi")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)