cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(console-component-generator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

if(NOT EXISTS "${CMAKE_HOME_DIRECTORY}/cmake/CPM.cmake")
  file(DOWNLOAD https://raw.githubusercontent.com/TheLartians/CPM.cmake/master/cmake/CPM.cmake "${CMAKE_HOME_DIRECTORY}/cmake/CPM.cmake")
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME console
  GITHUB_REPOSITORY edenreich/console-component
  VERSION 1.0.6
  OPTIONS
    "WITH_TESTS Off"
)

include_directories(${CMAKE_BINARY_DIR}/dist/include)
set(SOURCES_CXX_FILES
  src/main.cpp
  src/commands/make_command.h
  src/commands/make_command.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SOURCES_CXX_FILES})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES 
    OUTPUT_NAME "console-gen"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  target_compile_options(${PROJECT_NAME} PUBLIC /MT)
  target_link_options(${PROJECT_NAME} PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
else()
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()
target_link_libraries(${PROJECT_NAME} stdc++fs console)
