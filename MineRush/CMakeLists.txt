file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB source_files
        "*.h"
        "*.cpp"
        )
add_executable(
        MineRush
        ${source_files}
)


target_link_libraries(
        MineRush
        LINK_PUBLIC
        glfw
        glad
        stb_image
        assimp
        ${CMAKE_DL_LIBS}
)

