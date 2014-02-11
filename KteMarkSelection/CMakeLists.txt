project(ktexteditor_ktemarkselection)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ktexteditor_ktemarkselection_SRCS ktemarkselectionconfig.cpp ktemarkselectionplugin.cpp)

kde4_add_ui_files(ktexteditor_ktemarkselection_SRCS ktemarkselectionconfig.ui)

kde4_add_plugin(ktexteditor_ktemarkselection ${ktexteditor_ktemarkselection_SRCS})

target_link_libraries(ktexteditor_ktemarkselection ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_ktemarkselection DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ktemarkselectionui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor_ktemarkselection)

install(FILES ktexteditor_ktemarkselection.desktop ktexteditor_ktemarkselection_config.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
