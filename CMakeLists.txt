cmake_minimum_required(VERSION 3.5)

project(corevantage LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE(GNUInstallDirs)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(X200_SOURCES
        src/x200/main.cpp
        src/x200/readcfg.h
        src/x200/readcfg.cpp
        src/x200/corevantage.cpp
        src/x200/corevantage.h
        src/x200/corevantage.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(x200
        ${X200_SOURCES}
    )
else()
    if(ANDROID)
        add_library(x200 SHARED
            ${X200_SOURCES}
        )
    else()
        add_executable(x200
            ${X200_SOURCES}
        )
    endif()
endif()

target_link_libraries(x200 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(x200 PROPERTIES OUTPUT_NAME corevantage)


install(TARGETS x200 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES icons/16x16.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps
    RENAME corevantage.png)
install(FILES icons/32x32.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps
    RENAME corevantage.png)
install(FILES icons/64x64.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/64x64/apps
    RENAME corevantage.png)
install(FILES icons/128x128.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/128x128/apps
    RENAME corevantage.png)
install(FILES icons/256x256.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/256x256/apps
    RENAME corevantage.png)
install(FILES icons/512x512.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/512x512/apps
    RENAME corevantage.png)

install(FILES desktop/corevantage.desktop
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

##set default target to null
add_executable(ALL)
