cmake_minimum_required(VERSION 3.6)

option(OPENGL_LIB_BUILD_EXAMPLE "Build Example Font Renderer" ON)
if(OPENGL_LIB_BUILD_EXAMPLE)
    list(APPEND VCPKG_MANIFEST_FEATURES "example")
endif()

project(opengl_lib_proj)

include(GNUInstallDirs)

file(GLOB_RECURSE OPENGL_LIB_SOURCES "src/*.cpp" "src/*.h" "src/*.hpp")
add_library(opengl_lib ${OPENGL_LIB_SOURCES})
add_library(opengl_lib::opengl_lib ALIAS opengl_lib)

target_include_directories(opengl_lib 
    PUBLIC 
     "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
     "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_compile_features(opengl_lib PUBLIC cxx_std_20)

# Add glad 
find_package(glad REQUIRED)
target_link_libraries(opengl_lib PRIVATE glad::glad)

# Add glfw
find_package(glfw3 REQUIRED)
target_link_libraries(opengl_lib PRIVATE glfw)

# Add glm
find_package(glm REQUIRED)
target_link_libraries(opengl_lib PRIVATE glm::glm)

# Add imgui
find_package(imgui REQUIRED)
target_link_libraries(opengl_lib PRIVATE imgui::imgui)

# Add example project
if(OPENGL_LIB_BUILD_EXAMPLE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/font_renderer)
endif()

install(TARGETS opengl_lib
    EXPORT opengl_lib_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY src/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT opengl_lib_targets
    FILE opengl_lib_targets.cmake
    NAMESPACE opengl_lib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/opengl_lib
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/opengl_libConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/opengl_lib
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/opengl_libConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/opengl_lib
)