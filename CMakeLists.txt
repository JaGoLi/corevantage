cmake_minimum_required(VERSION 3.5)

project(corevantage LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

INCLUDE(GNUInstallDirs)


#Set default prefix to /usr
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(X200_SOURCES
        src/x200/main.cpp
        src/x200/readcfg.h
        src/x200/readcfg.cpp
        src/x200/corevantage.cpp
        src/x200/corevantage.h
        src/x200/corevantage.ui
	src/x200/infowindow.cpp
	src/x200/infowindow.h
	src/x200/infowindow.ui
	src/x200/aboutwindow.cpp
	src/x200/aboutwindow.h
	src/x200/aboutwindow.ui
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


set(X201_SOURCES
        src/x201/main.cpp
        src/x201/readcfg.h
        src/x201/readcfg.cpp
        src/x201/corevantage.cpp
        src/x201/corevantage.h
        src/x201/corevantage.ui
	src/x201/infowindow.cpp
	src/x201/infowindow.h
	src/x201/infowindow.ui
	src/x201/aboutwindow.cpp
	src/x201/aboutwindow.h
	src/x201/aboutwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(x201
        ${X201_SOURCES}
    )
else()
    if(ANDROID)
        add_library(x201 SHARED
            ${X201_SOURCES}
        )
    else()
        add_executable(x201
            ${X201_SOURCES}
        )
    endif()
endif()

target_link_libraries(x201 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(x201 PROPERTIES OUTPUT_NAME corevantage)


set(X220_SOURCES
        src/x220/main.cpp
        src/x220/readcfg.h
        src/x220/readcfg.cpp
        src/x220/corevantage.cpp
        src/x220/corevantage.h
        src/x220/corevantage.ui
	src/x220/infowindow.cpp
	src/x220/infowindow.h
	src/x220/infowindow.ui
	src/x220/aboutwindow.cpp
	src/x220/aboutwindow.h
	src/x220/aboutwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(x220
        ${X220_SOURCES}
    )
else()
    if(ANDROID)
        add_library(x220 SHARED
            ${X220_SOURCES}
        )
    else()
        add_executable(x220
            ${X220_SOURCES}
        )
    endif()
endif()

target_link_libraries(x220 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(x220 PROPERTIES OUTPUT_NAME corevantage)

set(X230_SOURCES
        src/x230/main.cpp
        src/x230/readcfg.h
        src/x230/readcfg.cpp
        src/x230/corevantage.cpp
        src/x230/corevantage.h
        src/x230/corevantage.ui
	src/x230/infowindow.cpp
	src/x230/infowindow.h
	src/x230/infowindow.ui
	src/x230/aboutwindow.cpp
	src/x230/aboutwindow.h
	src/x230/aboutwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(x230
        ${X230_SOURCES}
    )
else()
    if(ANDROID)
        add_library(x230 SHARED
            ${X230_SOURCES}
        )
    else()
        add_executable(x230
            ${X230_SOURCES}
        )
    endif()
endif()

target_link_libraries(x230 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(x230 PROPERTIES OUTPUT_NAME corevantage)

install(TARGETS x200 x201 x220 x230 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES icon/16x16.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps
    RENAME corevantage.png)
install(FILES icon/22x22.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/22x22/apps
    RENAME corevantage.png)
install(FILES icon/32x32.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps
    RENAME corevantage.png)
install(FILES icon/48x48.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/48x48/apps
    RENAME corevantage.png)
install(FILES icon/64x64.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/64x64/apps
    RENAME corevantage.png)
install(FILES icon/128x128.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/128x128/apps
    RENAME corevantage.png)
install(FILES icon/256x256.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/256x256/apps
    RENAME corevantage.png)
install(FILES icon/512x512.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/512x512/apps
    RENAME corevantage.png)

install(FILES icon/aboutIcon.png
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/corevantage)

install(FILES desktop/corevantage.desktop
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

install(FILES polkit/org.jagoli.nvramtool.policy polkit/org.jagoli.reboot.policy
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/polkit-1/actions)

##set default target to null
add_executable(ALL)
