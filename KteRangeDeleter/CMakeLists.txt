project(ktexteditor_kterangedeleter)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ktexteditor_kterangedeleter_SRCS kterangedeleterplugin.cpp)

kde4_add_plugin(ktexteditor_kterangedeleter ${ktexteditor_kterangedeleter_SRCS})

target_link_libraries(ktexteditor_kterangedeleter ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_kterangedeleter DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES kterangedeleterui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor_kterangedeleter)

install(FILES ktexteditor_kterangedeleter.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
