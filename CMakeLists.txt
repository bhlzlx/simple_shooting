cmake_minimum_required(VERSION 3.10)

project(HelloSDL3)

add_subdirectory(SDL3-3.2.24)
# add_subdirectory(SDL_ttf-main)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/SDL3_ttf-3.2.2/cmake")    

set(SDL3_ttf_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_ttf-3.2.2/cmake)

find_package(SDL3_ttf REQUIRED)

add_executable(HelloSDL3
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plane.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/bonus_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game_stage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render_context.cpp
)

target_include_directories(HelloSDL3
PRIVATE
    ${SDL3_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_ttf-3.2.2/include
)

target_link_libraries(HelloSDL3
PRIVATE
    SDL3-shared
    SDL_uclibc
    SDL3_ttf::SDL3_ttf-shared
)
