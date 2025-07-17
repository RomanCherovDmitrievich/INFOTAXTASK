cmake_minimum_required(VERSION 3.10)
project(Library)

# Опция для выбора типа сборки
option(BUILD_SHARED_LIBS "Build as a shared library" ON)

# Явно указываем тип библиотеки (важное изменение!)
if(BUILD_SHARED_LIBS)
    add_library(Library SHARED  # Явно указываем SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/private/Magazine.cpp
    )
    # Настройки для динамической библиотеки
    target_compile_definitions(Library PRIVATE LIBRARY_EXPORTS)
    if(APPLE)
        set_target_properties(Library PROPERTIES
            MACOSX_RPATH 1
            OUTPUT_NAME "Library"
        )
    endif()
else()
    add_library(Library STATIC  # Явно указываем STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/private/Magazine.cpp
    )
    # Настройки для статической библиотеки
    target_compile_definitions(Library PRIVATE BUILD_STATIC)
endif()

# Общие настройки для обоих типов
target_include_directories(Library PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Для MacOS специфичные настройки
if(APPLE)
    # Отключаем проблемные системные заголовки при использовании GCC
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(Library PRIVATE 
            -D__STDC_WANT_LIB_EXT1__=0
            -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
        )
    endif()
endif()