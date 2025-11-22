cmake_minimum_required(VERSION 3.6)
project(opengl_lib_proj)

add_library(opengl_lib INTERFACE)
target_include_directories(opengl_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(opengl_lib INTERFACE cxx_std_20)

# Build glad 
add_library(glad external/glad/src/glad.c external/glad/include/glad/glad.h external/glad/include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC external/glad/include)
target_link_libraries(opengl_lib INTERFACE glad)

# Add glfw
add_subdirectory(external/glfw)
target_link_libraries(opengl_lib INTERFACE glfw)

# Add glm
add_subdirectory(external/glm)
target_link_libraries(opengl_lib INTERFACE glm::glm)

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
target_link_libraries(opengl_lib INTERFACE imgui)

# Add example project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/font_renderer)

