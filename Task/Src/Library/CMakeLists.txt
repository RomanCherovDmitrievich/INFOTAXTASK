cmake_minimum_required(VERSION 3.10)
project(Library)

# Опция для выбора типа сборки (по умолчанию — динамическая)
option(BUILD_SHARED_LIBS "Build as a shared library" ON)

# Добавляем библиотеку
add_library(Library
    ${CMAKE_CURRENT_SOURCE_DIR}/private/Magazine.cpp
)

# Устанавливаем свойства для экспорта символов
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_SHARED_LIBS)
    # Для динамической библиотеки
    target_compile_definitions(Library PRIVATE LIBRARY_EXPORTS)
else()
    # Для статической
    target_compile_definitions(Library PRIVATE BUILD_STATIC)
endif()
