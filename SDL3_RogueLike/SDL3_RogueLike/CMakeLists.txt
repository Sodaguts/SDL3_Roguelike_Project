# CMakeList.txt : CMake project for SDL3_RogueLike, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SDL3_RogueLike "SDL3_RogueLike.cpp" "SDL3_RogueLike.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL3_RogueLike PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
