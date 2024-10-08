cmake_minimum_required(VERSION 3.7...3.26)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Temp_project
    VERSION 0.1
    DESCRIPTION "An example project."
    LANGUAGES CXX)

enable_testing()


set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(ALL_LIBS glfw GLEW::GLEW glm::glm)

set(LIBRARY "Example_library")
add_library(${LIBRARY} STATIC)
target_include_directories(${LIBRARY} PUBLIC include)
target_link_libraries(${LIBRARY} ${ALL_LIBS})
set_target_properties(${LIBRARY}
    PROPERTIES 
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)

include_directories(include)


# Add Google C++ Testing Framework as part of this project
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(test)

