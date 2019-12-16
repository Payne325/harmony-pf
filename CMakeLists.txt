# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11) 

# Forces linking of C runtimes to be dynamic
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 

project ("harmonypf")

add_subdirectory(googletest)

include_directories("Source" "Tests")

file(GLOB source_list "Source/*.cpp" "Source/*.h")

# Add source to this project's executable.
 
add_library(harmonypf STATIC ${source_list})

file(GLOB tests_list "Tests/*.cpp")

add_executable(harmonypftest ${tests_list})
target_link_libraries(harmonypftest harmonypf gtest_main)