add_executable(ConsoleApp
    MainFlow.cpp
    WorkFlow.cpp
)

# Проверяем, существует ли цель Library
if(NOT TARGET Library)
    message(FATAL_ERROR "Цель 'Library' не найдена! Сначала соберите библиотеку.")
endif()

target_link_libraries(ConsoleApp PRIVATE Library)

target_include_directories(ConsoleApp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Library
)

#target_include_directories(User PRIVATE ${CMAKE_SOURCE_DIR}/Task/Src/Library)

set_property(TARGET ConsoleApp PROPERTY COMPILE_WARNING_AS_ERROR ON)

#Настройки компилятора
#target_compile_options(User PRIVATE ${DEFAULT_COMPILE_FLAGS})
if(MSVC)
  target_compile_options(ConsoleApp PRIVATE /W4 /WX)
else()
  target_compile_options(ConsoleApp PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference)
endif()



# Настройки для динамической библиотеки (только если Library собрана как SHARED)
if(BUILD_SHARED_LIBS AND NOT MSVC)
  # Устанавливаем относительный путь для поиска .so в Linux/MacOS
  target_link_options(ConsoleApp PRIVATE "-Wl,-rpath,$ORIGIN/../lib")
endif()