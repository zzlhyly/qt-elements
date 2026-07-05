project(uicontrols)
SET(SRC_FILES
    src/main.cpp
    src/testwidget.cpp
    src/testwidget.h
    src/button/zbutton.cpp
    src/button/zbutton.h
)
if(WIN32)
    SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
endif(WIN32)
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
file(GLOB_RECURSE INCLUDE_SUBDIRS LIST_DIRECTORIES true ${Qt5_Include_DIR}/*)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Qt5_Include_DIR}
    ${INCLUDE_SUBDIRS}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
    )
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/product/${PROJECT_NAME}"
    )
endif()