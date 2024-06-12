cmake_minimum_required(VERSION 3.10)

project(SDLTest05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(main main.cpp)

target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})

# 链接 SDL2 库
target_link_libraries(main ${SDL2_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

