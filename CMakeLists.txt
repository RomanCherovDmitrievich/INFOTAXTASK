cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

# Проверка, что используется GCC
#if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  #  message(FATAL_ERROR "Требуется компилятор GCC! Текущий компилятор: ${CMAKE_CXX_COMPILER_ID}")
#endif()

project ("INFOTEXTASK" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
  set(SHORT_RPATH "./")
  set(CMAKE_DOCUMENTS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Doc)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
  set(SHORT_RPATH "../lib")
  set(CMAKE_DOCUMENTS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/doc)
endif()

#Настройка Юнит тестов
#option(TASK_TESTING "Переменная, которая включает построение и запуск автотестов в момент сборки." ON)
#option(TASK_COVERAGE "Переменная, которая включает сбор метрик покрытия unit-тестами." ON)

#set(GTEST_VERSION "release-1.12.1" CACHE STRING "Google test version 1.12.1")
#set(GTEST_VERSION "main" CACHE STRING "Google test main version")
#enable_testing()

option(BUILD_SHARED_LIBS "Собирать динамические библиотеки" ON)

#####
#add_executable(UserTest UserTest.cpp)
#target_link_libraries(UserTest PRIVATE Library)
#####

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output dir (bin): ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Output dir (lib): ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_subdirectory(Task)
