cmake_minimum_required(VERSION 3.16)
project(qaldav-popup-caldendar LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Sql Xml StateMachine Core5Compat)

qt_add_executable(qaldav-popup-caldendar
    main.cpp
    eventmodel.cpp eventmodel.h
    CalDAVCalendar/CalendarClient.cpp CalDAVCalendar/CalendarClient.h
    CalDAVCalendar/CalendarClient_CalDAV.cpp CalDAVCalendar/CalendarClient_CalDAV.h
    CalDAVCalendar/CalendarClient_CalDAV_ReceiveResonse.cpp
    CalDAVCalendar/CalendarClient_CalDAV_SendRequest.cpp
    CalDAVCalendar/CalendarClient_CalDAV_StateMachine.cpp
    CalDAVCalendar/CalendarClient_CalDAV_Utils.cpp
    CalDAVCalendar/CalendarEvent.cpp CalDAVCalendar/CalendarEvent.h
    CalDAVCalendar/DateUtils.cpp CalDAVCalendar/DateUtils.h
)

set_target_properties(qaldav-popup-caldendar PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qaldav-popup-caldendar PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Sql
    Qt6::Xml
    Qt6::StateMachine
    Qt6::Core5Compat
)

qt_add_qml_module(qaldav-popup-caldendar
    URI App
    QML_FILES
        MonthGridDelegate.qml
        main.qml
    RESOURCES
        qtquickcontrols2.conf
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS qaldav-popup-caldendar
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET qaldav-popup-caldendar
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
