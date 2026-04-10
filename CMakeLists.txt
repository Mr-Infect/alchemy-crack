cmake_minimum_required(VERSION 3.10)
project(alchemy_crack)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Find dependencies
find_package(OpenSSL REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(alchemy-crack ${SOURCES})

# Link libraries
target_link_libraries(alchemy-crack 
    OpenSSL::SSL 
    OpenSSL::Crypto 
    ${CURSES_LIBRARIES}
)
