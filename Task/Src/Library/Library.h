#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <memory>

// Макросы экспорта
#if defined(BUILD_STATIC)  // Макросы обеспечивающие экспорт и импорт символов при статической сборке
    #define LIBRARY_API
    #define LIBRARY_LOCAL
#else // Макросы обеспечивающие экспорт и импорт символов при динамической сборке
        #define LIBRARY_API __attribute__((visibility("default"))) // Экспортируемые символы
        #define LIBRARY_LOCAL __attribute__((visibility("hidden"))) // Скрытые символы
#endif

// Интерфейс для Log
class LIBRARY_API ILog {
public:
    virtual ~ILog() = default;
    virtual void log(const std::string& message, const std::string& level) = 0; // Делаем абстрактный класс
};

// Реализация FileLogger
class LIBRARY_API FileLog : public ILog {
public:
    explicit FileLog(const std::string& logFilePath); // Запрещает неявное преобразование строки в FileLog
    void log(const std::string& message, const std::string& level) override; // Реализация виртуального метода из ILog
    ~FileLog();

private:
    std::ofstream logFile; // Поток для записи в файл
    std::string filePath; // Путь к файлу лога
};

// Статический метод создания лога
//Умный указатель, который автоматически управляет памятью
//Хранит указатель на интерфейс, а не на конкретную реализацию
class LIBRARY_API LogFactory {
public:
    static std::unique_ptr<ILog> createFileLog(const std::string& filePath);
};
