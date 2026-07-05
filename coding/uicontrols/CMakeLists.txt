project(uicontrols)
SET(SRC_FILES
    src/main.cpp
    src/testwidget.cpp
    src/testwidget.h
    src/button/zbutton.cpp
    src/button/zbutton.h
    src/tag/ztag.cpp
    src/tag/ztag.h
    src/badge/zbadge.cpp
    src/badge/zbadge.h
    src/divider/zdivider.cpp
    src/divider/zdivider.h
    src/link/zlink.cpp
    src/link/zlink.h
    src/text/ztext.cpp
    src/text/ztext.h
    src/input/zinput.cpp
    src/input/zinput.h
    src/radio/zradio.cpp
    src/radio/zradio.h
    src/checkbox/zcheckbox.cpp
    src/checkbox/zcheckbox.h
    src/switch/zswitch.cpp
    src/switch/zswitch.h
    src/slider/zslider.cpp
    src/slider/zslider.h
    src/progress/zprogress.cpp
    src/progress/zprogress.h
    src/theme/theme.h
)
if(WIN32)
    SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
endif(WIN32)
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
qtproject_setup_target(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
