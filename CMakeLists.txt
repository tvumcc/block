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
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-window sfml-audio sfml-main sfml-network sfml-graphics sfml-system -static-libgcc -static-libstdc++)
