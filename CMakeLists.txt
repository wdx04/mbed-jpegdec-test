cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Initialize Mbed OS build system.
# Note: This block must be before the include of app.cmake
set(MBED_APP_JSON_PATH mbed_app.json5)

include(mbed-os/tools/cmake/mbed_toolchain_setup.cmake)
project(mbed-app LANGUAGES C CXX ASM)
include(mbed_project_setup)

add_subdirectory(mbed-os)
add_subdirectory(libraries)

# add subdirectories and build targets here
add_executable(mbed-app main.cpp)
target_link_libraries(mbed-app mbed-baremetal jpegdec)
mbed_set_post_build(mbed-app)
