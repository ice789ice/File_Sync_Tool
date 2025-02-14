cmake_minimum_required(VERSION 3.16)
project(FileSync LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 查找 Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools)

# 自动处理ui文件
qt_standard_project_setup()

# 添加可执行文件
qt_add_executable(untitled
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp 
    mainwindow.h
    mainwindow.ui
    FileSyncWorker.cpp 
    FileSyncWorker.h
    file.h
    ${UI_SOURCES}  # 确保 UI 文件被处理
)


# 链接 Qt6 组件
target_link_libraries(untitled PRIVATE Qt::Core Qt::Widgets)

# 生成 Qt 部署脚本（⚠️ 确保 Qt6::CoreTools 组件可用）
if(QT6_FOUND)
    qt_generate_deploy_app_script(
        TARGET untitled
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()

# 安装目标文件
install(TARGETS untitled
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 安装翻译文件
install(FILES ${CMAKE_SOURCE_DIR}/untitled_zh_CN.qm DESTINATION share/translations)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources DESTINATION share/untitled)


if(WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "RPM")
endif()

set(CPACK_PACKAGE_NAME "FileSync")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "A file synchronization tool")
set(CPACK_INSTALL_PREFIX "/usr/local")

# 修正 `CPACK_INSTALL_CMAKE_PROJECTS`
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}" "FileSync" "ALL" "${CMAKE_INSTALL_PREFIX}")

include(CPack)

