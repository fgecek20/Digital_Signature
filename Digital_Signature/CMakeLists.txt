cmake_minimum_required(VERSION 3.5)

project(Digital_Signature VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        home.cpp
        home.h
        home.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Digital_Signature
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        txtmsgencryption.h txtmsgencryption.cpp txtmsgencryption.ui
        textencryption.h
        txtmsgdecryption.h txtmsgdecryption.cpp txtmsgdecryption.ui
        textdecryption.h

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Digital_Signature APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Digital_Signature SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Digital_Signature
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(Boost REQUIRED COMPONENTS filesystem)

target_link_libraries(Digital_Signature PRIVATE Qt${QT_VERSION_MAJOR}::Widgets /usr/lib/x86_64-linux-gnu/libcryptopp.so PRIVATE Boost::filesystem)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Digital_Signature)
endif()
set_target_properties(Digital_Signature PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Digital_Signature
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Digital_Signature)
endif()

include_directories(/usr/include/cryptopp)

link_directories(/usr/lib/x86_64-linux-gnu)
