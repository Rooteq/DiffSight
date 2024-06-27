
cmake_minimum_required(VERSION 3.5)
project(RobotControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Charts)

set(PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tcpserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/robot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/robotdrawing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/charts.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphicsview.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/languages.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ledwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controlKeys.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/setDestination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stopButton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphicsUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/robotviz.cpp
    )

set(PROJECT_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/tcpserver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/robot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/robotdrawing.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/charts.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/graphicsview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/languages.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/ledwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/controlKeys.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/setDestination.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/stopButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/graphicsUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/robotviz.h

    ${CMAKE_CURRENT_SOURCE_DIR}/inc/mainwindow.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RobotControl
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_INCLUDES}
        res.qrc
    )

qt_add_translations(RobotControl
    TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ts/app_en.ts ${CMAKE_CURRENT_SOURCE_DIR}/ts/app_pl.ts ${CMAKE_CURRENT_SOURCE_DIR}/ts/app_sl.ts
    SOURCES ${PROJECT_SOURCES})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RobotControl APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RobotControl SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_INCLUDES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RobotControl
            ${PROJECT_INCLUDES}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RobotControl PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
target_include_directories(RobotControl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RobotControl)
endif()
set_target_properties(RobotControl PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RobotControl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RobotControl)
endif()
