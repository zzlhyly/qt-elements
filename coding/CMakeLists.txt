cmake_minimum_required(VERSION 4.0)
set(VCPKG_ROOT "D:/code/github/vcpkg" CACHE STRING "Path to vcpkg root directory")

# vcpkg integration — must be set before project()
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain")

if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
    message(STATUS "Building for x86 (32-bit)")
    set(VCPKG_TARGET_TRIPLET "x86-windows")
else()
    message(STATUS "Building for x64 (64-bit)")
    set(VCPKG_TARGET_TRIPLET "x64-windows")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "Using VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(qtproject)

set(Qt5_DIR ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/share/cmake/Qt5)
message(STATUS "Using Qt5_DIR: ${Qt5_DIR}")
set(Qt5_Include_DIR ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include/qt5)
message(STATUS "Using Qt5_Include_DIR: ${Qt5_Include_DIR}")
set(Qt5_Version "5.15.18")
message(STATUS "Using Qt5_Version: ${Qt5_Version}")

# Helper: apply common Qt5 setup to a target (find_package, includes, link, output dir)
function(qtproject_setup_target TARGET)
    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    file(GLOB_RECURSE INCLUDE_SUBDIRS LIST_DIRECTORIES true ${Qt5_Include_DIR}/*)
    target_include_directories(${TARGET} PRIVATE
        ${Qt5_Include_DIR}
        ${INCLUDE_SUBDIRS}
    )
    target_link_libraries(${TARGET} Qt5::Core Qt5::Widgets Qt5::Gui)

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_target_properties(${TARGET} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${TARGET}"
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${TARGET}"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${TARGET}"
        )
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set_target_properties(${TARGET} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${TARGET}"
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${TARGET}"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${TARGET}"
        )
    endif()
endfunction()

add_subdirectory(practice)
add_subdirectory(uicontrols)
