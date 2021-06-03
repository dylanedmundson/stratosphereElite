cmake_minimum_required(VERSION 3.0.0)
set(this stratosphereElite)
project(${this} VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(stratosphereElite-exe)
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(tests) 
endif()

# add glfw
include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_subdirectory(libs/glfw)

add_subdirectory(libs/glm)
include_directories(libraries/glm/glm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)