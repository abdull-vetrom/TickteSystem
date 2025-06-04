cmake_minimum_required(VERSION 3.16)

project(TicketSystem VERSION 0.1 LANGUAGES CXX)

# --- VMime include & lib ---
include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql PrintSupport)

set(PROJECT_SOURCES
    main.cpp
    mailtest.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dbmanager.h dbmanager.cpp
    loginwindow.h loginwindow.cpp
    loginwindow.ui
    user.h user.cpp
    ticket.h ticket.cpp
    ticketcard.ui
    myticketstab.h myticketstab.cpp myticketstab.ui
    myprojectstab.h myprojectstab.cpp myprojectstab.ui
    profiletab.h profiletab.cpp profiletab.ui
    createticketdialog.h createticketdialog.cpp createticketdialog.ui
    utils.h utils.cpp
    resources.qrc
    tickettable.ui
    ticketcard.h ticketcard.cpp
    createprojectdialog.cpp createprojectdialog.h createprojectdialog.ui
    storagemanager.h storagemanager.cpp
    prioritydelegate.h prioritydelegate.cpp
    addemployeedialog.h addemployeedialog.cpp
    userprofileeditdialog.h userprofileeditdialog.cpp userprofileeditdialog.ui
    editemployeedialog.h editemployeedialog.cpp editemployeedialog.ui
    mailtest.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TicketSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mycertverifier.h mycertverifier.cpp
        mailservice.h mailservice.cpp

    )
else()
    if(ANDROID)
        add_library(TicketSystem SHARED ${PROJECT_SOURCES})
    else()
        add_executable(TicketSystem ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(TicketSystem
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::PrintSupport
    vmime
    ssl
    crypto
    ws2_32
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TicketSystem)
endif()

set_target_properties(TicketSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TicketSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TicketSystem)
endif()
