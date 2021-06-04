cmake_minimum_required (VERSION 3.15)

project (CG-MineRushProject)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory (external)

include_directories(
	external/glfw-3.3.4/include/GLFW/
	external/glad/include/
	external/glm-0.9.7.1/
	external/stb_image/
	external/assimp-5.0.1/
		MineRush/Models
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	glad
	glm
	assimp
	stb_image
)


add_subdirectory (MineRush)
