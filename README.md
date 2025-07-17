1. Для сборки статической библиотеки:
   
mkdir build-static && cd build-static

Генерация проекта (ключ BUILD_STATIC)
cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15

Сборка
make -j$(sysctl -n hw.logicalcpu)

2. Для сборки динамической библиотеки

mkdir build-shared && cd build-shared

Генерация проекта (ключ BUILD_SHARED_LIBS)
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15

Сборка
make -j$(sysctl -n hw.logicalcpu)
