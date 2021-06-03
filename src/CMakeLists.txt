# add glad library

set(
    GLAD_LIB_SOURCES
    glad/glad.c
    glad/glad.h
    glad/khrplatform.h
)

set(
    UTIL_LIB_SOURCES
    utils/Shader.hpp
    utils/Shader.cpp
)

set(
    STB_LIB_SOURCES
    stb/stb_image.h
    stb/stb_image.cpp
)

set(
    ENGINE_LIB_SOURCES
    engine/Window.hpp
    engine/Window.cpp
)

add_library(
    LINK_LIBS
    glad ${GLAD_LIB_SOURCES}
    utils ${UTIL_LIB_SOURCES}
    stb ${STB_LIB_SOURCES}
    engine ${ENGINE_LIB_SOURCES}
)

target_include_directories(
    LINK_LIBS PUBLIC "${CMAKE_CURRENT_SORUCE_DIR}"
    ${OPENGL_LIBRARIES} glfw "${CMAKE_CURRENT_SORUCE_DIR}"
)

target_link_libraries(LINK_LIBS glm)
target_link_libraries(
    LINK_LIBS ${OPENGL_LIBRARIES} glfw
)