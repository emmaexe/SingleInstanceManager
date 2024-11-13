cmake_minimum_required(VERSION 3.10)
project(
    SingleInstanceManagerExample
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/emmaexe/SingleInstanceManager/"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Find libraries
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    DBus
)

# Find all source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

# Enable MOC
set(CMAKE_AUTOMOC ON)

# Add executable and link libraries
qt_add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::DBus)
