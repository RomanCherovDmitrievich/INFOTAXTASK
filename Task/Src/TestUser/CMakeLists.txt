add_executable(UserTest 
    ${CMAKE_CURRENT_SOURCE_DIR}/UserTest.cpp  # Явный путь
)

# Проверяем, существует ли цель Library
if(NOT TARGET Library)
    message(FATAL_ERROR "Цель 'Library' не найдена! Сначала соберите библиотеку.")
endif()
target_link_libraries(UserTest Library)

set_property(TARGET UserTest PROPERTY COMPILE_WARNING_AS_ERROR ON)

#Настройки компилятора
  target_compile_options(UserTest PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference)

# Настройки для динамической библиотеки (только если Library собрана как SHARED)
if(BUILD_SHARED_LIBS AND NOT MSVC)
  # Устанавливаем относительный путь для поиска .so в Linux/MacOS
  target_link_options(UserTest PRIVATE "-Wl,-rpath,$ORIGIN/../lib")
endif()