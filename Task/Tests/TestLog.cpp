#include "TestLog.h"          // Новый заголовочный файл
#include "../Src/Library/Library.h"
#include <cassert>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Проверяет что лог правильно создает файл для записи логов.
void testLogCreation() { 
    const std::string testFile = "test_log.txt"; // Временный файл для теста
    auto log = LogFactory::createFileLog(testFile); // Создаём лог

    // Проверяем что логер создан и что файл создан 
    assert(log != nullptr && "Не удалось создать журнал");
    assert(fs::exists(testFile) && "Файл журнала не создан");
    
    //Удаляем временный файл
    fs::remove(testFile);
}

// Проверяем что лог правильно записывает сообщения в файл.
void testLogWriting() {
    const std::string testFile = "test_log_write.txt"; // Временный файл для теста
    const std::string testMessage = "Test message"; // Тестовое сообщение 
    const std::string testLevel = "INFO"; // Тестовый уровень сообщения
    
    auto log = LogFactory::createFileLog(testFile); // Создаёт тестовый файл
    log->log(testMessage, testLevel); // Записывает тестовое сообщение в журнал
    

    // Читаем что записалось в файл
    std::ifstream file(testFile);
    std::string content((std::istreambuf_iterator<char>(file)), 
                        std::istreambuf_iterator<char>());
    
    assert(content.find(testMessage) != std::string::npos && "Сообщение не найдено в журнале"); // Ищем тестовое сообщение
    assert(content.find(testLevel) != std::string::npos && "Уровень журнала не найден"); // Ищем тестовый уровень сообщения
    fs::remove(testFile);
}

void registerLogTests() {
    Test::addTest("Журнал: Создание", testLogCreation);
    Test::addTest("Журнал: Запись", testLogWriting);
}