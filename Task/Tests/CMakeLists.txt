cmake_minimum_required(VERSION 3.10)

# Создаем исполняемый файл для тестов
add_executable(RunTests
    TestRunner.cpp
    Test.cpp
    TestLog.cpp
    TestWorkFlow.cpp
    
    # Добавляем исходники из ConsoleApp
    #${CMAKE_SOURCE_DIR}/Task/Src/ConsoleApp/MainFlow.cpp
    ${CMAKE_SOURCE_DIR}/Task/Src/ConsoleApp/WorkFlow.cpp
)

# Подключаем библиотеки (включая новую CommonLib, если она создана)
target_link_libraries(RunTests PRIVATE
    Library
    pthread
)

# Пути включения (добавляем заголовки ConsoleApp, если они нужны)
target_include_directories(RunTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Task/Src/Library
    ${CMAKE_SOURCE_DIR}/Task/Src/ConsoleApp
)

# Опции компиляции
target_compile_options(RunTests PRIVATE
    -Wall
    -Wextra
    -Werror
)

# Цель для запуска тестов
add_custom_target(test
    COMMAND ./RunTests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS RunTests
    COMMENT "Running unit tests"
)

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-undefined,dynamic_lookup")
endif()