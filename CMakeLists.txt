cmake_minimum_required(VERSION 3.6)
project(opengl_ui_proj)

file(GLOB OPENGL_SOURCES src/*.h src/*.cpp)
add_executable(opengl_ui ${OPENGL_SOURCES})
target_compile_features(opengl_ui PUBLIC cxx_std_23)
target_include_directories(opengl_ui PUBLIC src)

target_compile_definitions(opengl_ui PRIVATE ASSET_DIR=${CMAKE_CURRENT_SOURCE_DIR}/data)

set(OPENGL_VERSION_MAJOR "4" CACHE STRING "OpenGL Version Major" )
set(OPENGL_VERSION_MINOR "6" CACHE STRING "OpenGL Version Minor")

target_compile_definitions(opengl_ui PRIVATE OPENGL_VERSION_MAJOR=${OPENGL_VERSION_MAJOR})
target_compile_definitions(opengl_ui PRIVATE OPENGL_VERSION_MINOR=${OPENGL_VERSION_MINOR})

# Build glad 
add_library(glad external/glad/src/glad.c external/glad/include/glad/glad.h external/glad/include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC external/glad/include)
target_link_libraries(opengl_ui PUBLIC glad)

# Add glfw
add_subdirectory(external/glfw)
target_link_libraries(opengl_ui PUBLIC glfw)

# Add glm
add_subdirectory(external/glm)
target_link_libraries(opengl_ui PUBLIC glm::glm)

# Add FreeType
add_subdirectory(external/freetype)
target_link_libraries(opengl_ui PUBLIC freetype)

# Build imgui
add_library(imgui external/imgui-docking/imconfig.h
                  external/imgui-docking/imgui_demo.cpp
                  external/imgui-docking/imgui_draw.cpp
                  external/imgui-docking/imgui_internal.h
                  external/imgui-docking/imgui_tables.cpp 
                  external/imgui-docking/imgui_widgets.cpp 
                  external/imgui-docking/imgui.cpp 
                  external/imgui-docking/imgui.h 
                  external/imgui-docking/imstb_rectpack.h 
                  external/imgui-docking/imstb_textedit.h 
                  external/imgui-docking/imstb_truetype.h 
                  external/imgui-docking/misc/cpp/imgui_stdlib.cpp 
                  external/imgui-docking/misc/cpp/imgui_stdlib.h
                  external/imgui-docking/backends/imgui_impl_opengl3.h
                  external/imgui-docking/backends/imgui_impl_opengl3.cpp
                  external/imgui-docking/backends/imgui_impl_glfw.h
                  external/imgui-docking/backends/imgui_impl_glfw.cpp )

target_include_directories(imgui PUBLIC external/imgui-docking/backends external/imgui-docking external/imgui-docking/misc/cpp)
target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(opengl_ui PUBLIC imgui)

