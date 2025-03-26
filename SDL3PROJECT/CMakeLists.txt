cmake_minimum_required(VERSION 3.20)

project(SDL3PROJECT)
add_executable(roguework) # WIN 32 - hide the console like this
#set_target_properties(roguework PROPERTIES WIN32_EXECUTABLE "TRUE")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libs)

# add CPM if it doesn't exist
if(NOT(EXISTS $(CPM_DOWNLOAD_LOCATION)))
	message(STATUS "Downloading CPM.cmake")
	file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

set(LIBS)

if(NOT DEFINED EMSCRIPTEN)
SET(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD_SHARED_LIBS" FORCE)
SET(BUILD_STATIC_LIBS ON CACHE BOOL "BUILD_STATIC_LIBS" FORCE)
SET(POSITION_INDEPENDENT_CODE ON CACHE BOOL "POSITION_INDEPENDENT_CODE" FORCE)

# SDL
string(TIMESTAMP BEFORE "%s")
CPMAddPackage(
        NAME SDL3
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG release-3.2.8
)
find_package(SDL3 REQUIRED)

    file(GLOB SDL3_HEADERS "${SDL3_SOURCE_DIR}/include/*.h")

    # Create a target that copies headers at build time, when they change
    add_custom_target(sdl_copy_headers_in_build_dir
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${SDL3_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/SDLHeaders/SDL3"
            DEPENDS ${SDL3_HEADERS})

    # Make SDL depend from it
    add_dependencies(SDL3-static sdl_copy_headers_in_build_dir)

    # And add the directory where headers have been copied as an interface include dir
    target_include_directories(SDL3-static INTERFACE "${CMAKE_BINARY_DIR}/SDLHeaders")

    set (SDL3_INCLUDE_DIR ${SDL3_SOURCE_DIR}/include)

include_directories(${SDL3_INCLUDE_DIR})
string(TIMESTAMP AFTER "%s")
math(EXPR DELTASDL "${AFTER} - ${BEFORE}")
MESSAGE(STATUS "SDL3 TIME: ${DELTASDL}s")

list(APPEND LIBS SDL3::SDL3)


## SDL_ttf
#string(TIMESTAMP BEFORE "%s")
#CPMAddPackage(GITHUB_REPOSITORY libsdl-org/SDL_ttf
#        GIT_TAG release-2.20.1
#        OPTIONS
#        "SDL2TTF_INSTALL OFF"
#        "SDL2TTF_BUILD_SHARED_LIBS OFF"
#        "SDL2TTF_VENDORED ON"
#        "SDL2TTF_SAMPLES OFF"
#) # vendor is required for mingw builds
#find_package(SDL_ttf REQUIRED)
#include_directories(${SDL_ttf_SOURCE_DIR})
#string(TIMESTAMP AFTER "%s")
#math(EXPR DELTASDL_ttf "${AFTER} - ${BEFORE}")
#MESSAGE(STATUS "SDL_ttf TIME: ${DELTASDL_ttf}s")


#
### SDL_mixer
#string(TIMESTAMP BEFORE "%s")
#CPMAddPackage(GITHUB_REPOSITORY libsdl-org/SDL_mixer
#        GIT_TAG release-2.6.2
#        OPTIONS
#        "SDL2MIXER_INSTALL OFF"
#        "SDL2MIXER_VENDORED ON"
#        "SDL2MIXER_SAMPLES OFF"
#        "SDL2MIXER_BUILD_SHARED_LIBS OFF"
#)
#find_package(SDL_mixer REQUIRED)
#include_directories(${SDL_mixer_SOURCE_DIR}/include)
#string(TIMESTAMP AFTER "%s")
#math(EXPR DELTASDL_mixer "${AFTER} - ${BEFORE}")
#MESSAGE(STATUS "SDL_mixer TIME: ${DELTASDL_mixer}s")
ENDIF()


target_include_directories(roguework PRIVATE "headers/")


file(GLOB sources "src/*.cpp")

target_sources(roguework PRIVATE ${sources} "main.cpp")
target_link_libraries(roguework PRIVATE ${LIBS})

# add images
file(GLOB RESOURCE_FILES "images/*.bmp")
set(RESOURCE_FILE_NAMES)
set(RESOURCE_FILES_BINDIR)
foreach(resource_file IN LISTS RESOURCE_FILES)
    get_filename_component(res_file_name ${resource_file} NAME)
    list(APPEND RESOURCE_FILE_NAMES "${res_file_name}")
    set(resource_file_bindir "${CMAKE_CURRENT_BINARY_DIR}/${res_file_name}")
    add_custom_command(OUTPUT "${resource_file_bindir}"
        COMMAND "${CMAKE_COMMAND}" -E copy "${resource_file}" "${resource_file_bindir}"
        DEPENDS "${resource_file}"
    )
    list(APPEND RESOURCE_FILES_BINDIR "${resource_file_bindir}")
endforeach()
add_custom_target(copy-resources DEPENDS "${RESOURCE_FILES_BINDIR}")
add_dependencies(roguework copy-resources)
