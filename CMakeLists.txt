cmake_minimum_required(VERSION 3.10)
project(notifica-rabbit C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find required packages
find_package(CURL REQUIRED)

# Platform-specific settings
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32)
    # Windows-specific libraries
    set(PLATFORM_LIBS ws2_32)
else()
    # Linux-specific libraries
    set(PLATFORM_LIBS pthread rt)
    add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CURL_INCLUDE_DIRS}
)

# Add dotenv library with specific compile options
add_library(dotenv STATIC
    include/dotenv.c
)

# Add executable
add_executable(notifica-rabbit
    src/main.c
    src/attach.c
    src/api_request.c
    src/config.c
)

# Link libraries
target_link_libraries(notifica-rabbit
    dotenv
    ${CURL_LIBRARIES}
    ${PLATFORM_LIBS}
)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add compile options
if(MSVC)
    target_compile_options(notifica-rabbit PRIVATE /W4 /Zi)
    target_compile_options(dotenv PRIVATE /W4 /Zi)
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /RTC1")
else()
    target_compile_options(notifica-rabbit PRIVATE -Wall -Wextra -g)
    target_compile_options(dotenv PRIVATE -Wall -Wextra -g)
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g -fno-omit-frame-pointer")
endif()

# Enable debug info
set(CMAKE_BUILD_TYPE Debug) 