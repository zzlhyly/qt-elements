project(practice)

SET(SRC_FILES
    src/main.cpp
    src/mywidget.cpp
    src/mywidget.h
)
if(WIN32)
    SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
endif(WIN32)
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
qtproject_setup_target(${PROJECT_NAME})
