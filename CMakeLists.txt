cmake_minimum_required( VERSION 3.11 )

project ( frameless-qt-poc
    LANGUAGES CXX
    VERSION 0.0.1
)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package ( QT NAMES Qt5 Qt6 REQUIRED )
find_package ( Qt${QT_VERSION_MAJOR} 5.15 COMPONENTS Core Gui Widgets REQUIRED )

add_executable ( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME} PRIVATE
    framelesswindow.cpp
    framelesswindow.h
    demowindow.cpp
    demowindow.h
    main.cpp
)

target_link_libraries ( ${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)
