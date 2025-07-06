cmake_minimum_required(VERSION 3.10)

project(visualizer C)

# Use o padrão C99
set(CMAKE_C_STANDARD 99)

# Adiciona os arquivos-fonte
file(GLOB SOURCES "src/*.c")

# Adiciona os headers
include_directories(include)

# Encontra as libs do Allegro (você precisa do pkg-config funcionando)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_font-5 allegro_primitives-5)

include_directories(${ALLEGRO_INCLUDE_DIRS})
link_directories(${ALLEGRO_LIBRARY_DIRS})

# Gera o executável
add_executable(visualizer ${SOURCES})

# Liga as bibliotecas do Allegro
target_link_libraries(visualizer ${ALLEGRO_LIBRARIES} m)
