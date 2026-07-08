project(uicontrols)
SET(SRC_FILES
    src/main.cpp
    src/testwidget.cpp
    src/testwidget.h
    # Foundation modules
    src/style/style.h
    src/statemachine/statemachine.cpp
    src/statemachine/statemachine.h
    src/painter/painter.cpp
    src/painter/painter.h
    src/icon/icon_manager.cpp
    src/icon/icon_manager.h
    src/animation/animation_manager.cpp
    src/animation/animation_manager.h
    # Widgets
    src/widgets/button/zbutton.cpp
    src/widgets/button/zbutton.h
    src/widgets/tag/ztag.cpp
    src/widgets/tag/ztag.h
    src/widgets/badge/zbadge.cpp
    src/widgets/badge/zbadge.h
    src/widgets/divider/zdivider.cpp
    src/widgets/divider/zdivider.h
    src/widgets/link/zlink.cpp
    src/widgets/link/zlink.h
    src/widgets/text/ztext.cpp
    src/widgets/text/ztext.h
    src/widgets/input/zinput.cpp
    src/widgets/input/zinput.h
    src/widgets/radio/zradio.cpp
    src/widgets/radio/zradio.h
    src/widgets/checkbox/zcheckbox.cpp
    src/widgets/checkbox/zcheckbox.h
    src/widgets/switch/zswitch.cpp
    src/widgets/switch/zswitch.h
    src/widgets/slider/zslider.cpp
    src/widgets/slider/zslider.h
    src/widgets/progress/zprogress.cpp
    src/widgets/progress/zprogress.h
    src/widgets/alert/zalert.cpp
    src/widgets/alert/zalert.h
    src/popup/zpopup.cpp
    src/popup/zpopup.h
    src/widgets/tooltip/ztooltip.cpp
    src/widgets/tooltip/ztooltip.h
    src/theme/theme.h
)
if(WIN32)
    SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
endif(WIN32)
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
qtproject_setup_target(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
