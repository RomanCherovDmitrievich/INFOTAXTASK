cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

project ("INFOTEXTASK" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#### Настройка путей для "stdlib.h"
if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Полный набор путей для GCC на macOS
    set(GCC_INCLUDE_DIRS
        /opt/homebrew/Cellar/gcc/15.1.0/include/c++/15
        /opt/homebrew/Cellar/gcc/15.1.0/include/c++/15/aarch64-apple-darwin23
        /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
        /usr/local/include
        /usr/include
    )
    
    # Добавляем как системные директории
    foreach(DIR ${GCC_INCLUDE_DIRS})
        if(EXISTS ${DIR})
            include_directories(SYSTEM ${DIR})
            add_compile_options(-isystem ${DIR})
        endif()
    endforeach()
    
    # Специфичные флаги для GCC
    add_compile_options(
        -Wno-implicit-function-declaration
        -D__STDC_WANT_LIB_EXT1__=0
    )
    
    # Пути для линковки
    link_directories(/opt/homebrew/Cellar/gcc/15.1.0/lib/gcc/15)
endif()

####### Настройка путей для  "_bonus.h"
if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Отключаем проблемные системные заголовки
    add_compile_options(
        -D__STDC_WANT_LIB_EXT1__=0
        -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
        -Wno-implicit-function-declaration
    )
    include_directories(
        /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
    )
endif()
#######

if(APPLE)
    add_compile_options(-D__STDC_WANT_LIB_EXT1__=0)
    message(STATUS "Disabling __STDC_WANT_LIB_EXT1__ for MacOS build")
endif()

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
  set(SHORT_RPATH "../lib")
  set(CMAKE_DOCUMENTS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/doc)


option(BUILD_SHARED_LIBS "Собирать динамические библиотеки" ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output dir (bin): ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Output dir (lib): ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_subdirectory(Task) 
