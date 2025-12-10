cmake_minimum_required(VERSION 3.16)

project(cinema VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Network)

# --- МИ ВИДАЛИЛИ БЛОК set(PROJECT_SOURCES ...) ---

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

    qt_add_executable(cinema
        MANUAL_FINALIZATION

        # --- І ВСТАВИЛИ СПИСОК ФАЙЛІВ ПРЯМО СЮДИ ---
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        apimanager.h apimanager.cpp
        moviewidget.h moviewidget.cpp
        loadposter.h loadposter.cpp
        windowsessions.h windowsessions.cpp
        sessionwidget.h sessionwidget.cpp
        app_resources.qrc

    )
# Define target properties for Android with Qt 6 as:
#   set_property(TARGET cinema APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cinema SHARED
            # --- І СЮДИ ТЕЖ (для сумісності з Qt 5) ---
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#   set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cinema
            # --- І СЮДИ ТЕЖ (для сумісності з Qt 5) ---
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
        )
    endif()
endif()

target_link_libraries(cinema PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(cinema PRIVATE Qt6::Core Qt6::Core Qt6::Network)
target_link_libraries(cinema PRIVATE Qt6::Core)
target_link_libraries(cinema PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(cinema PRIVATE Qt6::Core)
target_link_libraries(cinema PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(cinema PRIVATE Qt6::Core Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.cinema)
endif()
set_target_properties(cinema PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS cinema
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cinema)
endif()
