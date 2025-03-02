cmake_minimum_required(VERSION 3.20)

project(SDL3PROJECT)
add_executable(roguework) # WIN 32 - hide the console like this
set_target_properties(roguework PROPERTIES WIN32_EXECUTABLE "TRUE")

target_sources(roguework PRIVATE main.cpp)

find_package(SDL3)
target_link_libraries(roguework PRIVATE SDL3::SDL3)
target_compile_definitions(roguework PRIVATE SDL_MAIN_USE_CALLBACKS)
target_link_options(roguework PRIVATE -static)