cmake_minimum_required(VERSION 3.23)
project(my_hunter C)

set(CMAKE_C_STANDARD 11)

add_executable(my_hunter
        include/display.h
        src/boucle.c
        src/fonc.c
        src/init.c
        src/main.c
        src/more_fonc.c
        src/hit_marker.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(my_hunter PRIVATE /opt/homebrew/Cellar/csfml/2.5.1/include)
    target_link_directories(my_hunter PRIVATE /opt/homebrew/Cellar/csfml/2.5.1/lib)
endif()

target_include_directories(my_hunter PRIVATE include)
target_link_libraries(my_hunter csfml-graphics csfml-system csfml-audio csfml-window csfml-network)