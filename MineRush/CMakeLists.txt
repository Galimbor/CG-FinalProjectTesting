file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(
		MineRush
		Main.cpp
        	Window.cpp
		EBO.cpp
		Camera.cpp
		Lantern.cpp
		Mesh.cpp
		Model.cpp
		MovingBody.cpp
		PlayerChar.cpp
		Shader.cpp
		VAO.cpp
		VBO.cpp
		Window.cpp
		PickUps.cpp
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

