add_executable(stratosphereElite-exe stratosphereElite.cpp)



target_link_libraries(
    stratosphereElite-exe PRIVATE 
    ${OPENGL_LIBRARIES} glfw
    LINK_LIBS
)