cmake_minimum_required(VERSION 3.10)
project(SDLTest06 LANGUAGES CXX)

# 使用 pkg-config
find_package(PkgConfig REQUIRED)

# 搜索 SDL2 和 SDL2_image
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

# 链接时添加库路径
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_IMAGE_LIBRARY_DIRS})

# 添加可执行文件
add_executable(main main.cpp)

# 包含目录
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# 链接库
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# message(STATUS "SDL2_image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
# message(STATUS "SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")
# message(STATUS "SDL2_image libraries dir: ${SDL2_IMAGE_LIBRARY_DIRS}")
