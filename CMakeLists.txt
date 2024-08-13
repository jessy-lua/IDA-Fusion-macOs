cmake_minimum_required(VERSION 3.12)
project(fusion64)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the new definitions
add_definitions(-D__MACOSX__ -D__ARM__)
add_definitions(-D__EA64__)
# Set compiler flags
add_compile_options(-O3 -w -Wreturn-type -fpermissive)

# Set output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find IDA SDK
set(IDA_SDK_DIR "${CMAKE_SOURCE_DIR}/sdk" CACHE PATH "Path to IDA SDK")
include_directories(${IDA_SDK_DIR}/include)

# Link IDA libraries
link_directories(${IDA_SDK_DIR}/lib/arm64_mac_clang_64/)

# Add source files
file(GLOB SDK_SOURCES "${IDA_SDK_DIR}/includes/*.cpp")
file(GLOB PLUGIN_SOURCES "src/*.cpp")

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SDK_SOURCES} ${PLUGIN_SOURCES})

# Link against IDA library
target_link_libraries(${PROJECT_NAME} PRIVATE "${IDA_SDK_DIR}/lib/arm64_mac_clang_64/libida64.dylib")

target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")

# Set output name
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".dylib")

# Disable symbol exporting
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-dead_strip -Wl,-exported_symbol,_PLUGIN")