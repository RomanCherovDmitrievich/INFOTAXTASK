# Задание 
Разработать библиотеку, которая имеет два вида сборки: динамическая и статическая, для записи сообщений в журнал с разными уровнями важности и приложение, демонстрирующее работу библиотеки. 

В журнале записываются: сообщение, уровень сообщения, дата и время получения сообщения

Уровни сообщений могут быть INFO, WARNING и ERROR

# Основные требования 
__Просьба убедится что у вас установлен компилятор gcc 15 версии а так же cmake для сборки проекта__

__Запускать на операционных системах на базе ядра Linux(Unix-подобных системах)__

# 1. Команды для сборки статической библиотеки:
Подготовка к сборке
```Bash
mkdir build-static && cd build-static
```
Генерация проекта (ключ BUILD_SHARED_LIBS=OFF)
```Bash
cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
```
Сборка
```Bash
make -j$(sysctl -n hw.logicalcpu)
```
Переход в папку к исполняемым файлам
```Bash
cd bin
```
Запуск приложения, не забудьте указать путь к файлу log после уровень сообщения по умолчанию 
```Bash
./ConsoleApp app.log INFO 
```
Очистка
```Bash
cd ../.. && rm -rf build-static
```

# 2. Команды для сборки динамической библиотеки
Подготовка к сборке
```Bash
mkdir build-shared && cd build-shared
```
Генерация проекта (ключ BUILD_SHARED_LIBS=ON)
```Bash
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
```

Сборка
```Bash
make -j$(sysctl -n hw.logicalcpu)
```

Переход в папку к исполняемым файлам
```Bash
cd bin
```

Запуск приложения, не забудьте указать путь к файлу log после уровень сообщения по умолчанию
```Bash
./ConsoleApp app.log INFO 
```

Очистка
```Bash
cd ../.. && rm -rf build-shared
```

# 3. Команды для сборки тестов
Подготовка к сборке
```Bash
mkdir build-test && cd build-test
```

Генерация проекта (ключ Task_TESTING=ON)
```Bash
cmake .. -DTask_TESTING=ON -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
```
Сборка
```Bash
make RunTests -j$(nproc)
```
Переход в папку к исполняемым файлам
```Bash
cd bin     
```

Запуск приложения, не забудьте указать путь к файлу log после уровень сообщения по умолчанию
```Bash
./RunTests app.log INFO
```

Очистка
```Bash
cd ../.. && rm -rf build-test
```

_В тестах есть проверка на качество работы потоков, хоть это нельзя отследить и предугадать так как разные компиляторы по разному работают, но можно убедится что иногда они работают как задумывалось._

# О библиотеке

## 1. Интерфейс ILog (абстракция)

```c++
class ILog {
public:
    virtual ~ILog() = default;
    virtual void log(const std::string& message, const std::string& level) = 0;
};
```

Базовый интерфейс для всех логов.

## 2. FileLog (реализация для файлового логирования)

```c++
class FileLog : public ILog {
...
};
```

>Автоматически создает директории
>Добавляет временные метки к сообщениям
>Закрывает файл при уничтожении

## 3. LogFactory (фабрика логов)

```c++
class LogFactory {
public:
    static std::unique_ptr<ILog> createFileLog(const std::string& filePath);
};
```
>Скрывает реализацию FileLog
>Возвращает unique_ptr для автоматического управления памятью
>Позволяет легко добавить новые типы логов

## 4. Поддержка сборки (макросы)

```c++
#if defined(BUILD_STATIC) 
    #define LIBRARY_API
    #define LIBRARY_LOCAL
#else 
    #define LIBRARY_API __attribute__((visibility("default"))) 
    #define LIBRARY_LOCAL __attribute__((visibility("hidden")))
#endif
```

__LIBRARY_API__ - экспорт символов для динамической библиотеки

__LIBRARY_LOCAL__ - скрытие внутренних реализаций

### Пример формата лога:

Test Message [INFO] [2025-07-17 22:00:36] 