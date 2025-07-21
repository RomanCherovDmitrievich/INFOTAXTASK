Перед сборкой проекта убедится что у вас установлен компилятор gcc 15 версии а так же cmake
Уровни сообщений могут быть INFO, WARNING и ERROR

1. Для сборки статической библиотеки:
Очистка и подготовка
rm -rf build-static
mkdir build-static && cd build-static

Генерация проекта (ключ BUILD_SHARED_LIBS=OFF)
cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15

Сборка
make -j$(sysctl -n hw.logicalcpu)

cd bin

./ConsoleApp app.log INFO - запуск приложения - путь к файлу журнала - уровень сообщений по умолчанию

2. Для сборки динамической библиотеки
Очистка и подготовка
rm -rf build-shared
mkdir build-shared && cd build-shared

Генерация проекта (ключ BUILD_SHARED_LIBS=ON)
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15

Сборка
make -j$(sysctl -n hw.logicalcpu)

cd bin

./ConsoleApp app.log - запуск приложения - путь к файлу журнала - уровень сообщений по умолчанию

3. Для сборки тестов

mkdir build-test && cd build-test

Генерация проекта 
cmake .. -DTask_TESTING=ON   

Сборка
make RunTests -j$(nproc)

cd bin     

./RunTests app.log INFO - запуск тестов - путь к файлу журнала - уровень сообщений по умолчанию


В тестах есть проверка на качество работы потоков   , хоть это нельзя отследить и предугадать,
так как разные компиляторы по разному работают, но можно убедится что иногда они работают как задумывалось.
