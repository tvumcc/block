cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(blocks)

set(BUILD_SHARED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES TRUE)
add_subdirectory("lib/SFML")
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui-sfml
	${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${CMAKE_PROJECT_NAME} 
	# Dear ImGUI
	lib/imgui/imgui.cpp
	lib/imgui/imgui_widgets.cpp
	lib/imgui/imgui_draw.cpp
	lib/imgui/imgui_tables.cpp

	# imgui-sfml
	lib/imgui-sfml/imgui-SFML.cpp

	# Project
	src/main.cpp
	src/physics_world.cpp
	src/collision_object.cpp
	src/collision.cpp
	src/rectangle.cpp
	src/vec2.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-window sfml-audio sfml-main sfml-network sfml-graphics sfml-system -static-libgcc -static-libstdc++)
