#include "TestWorkFlow.h"
#include "../Src/ConsoleApp/WorkFlow.h"
#include "../Src/Library/Library.h"
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>

//Проверяем что задачи добавляются в очередь и создаётся лог-файл.
void test_AddTaskToQueue() {
    WorkFlow workflow("test_workflow.log", "INFO"); // Создаёт тестовый файл и уровень по умолчанию
    workflow.addTask("Тестовое сообщение", "WARNING"); // Записывает тестовое  сообщение и уровень в файл
    
    // Проверяем, что файл создан
    if (!std::ifstream("test_workflow.log").good()) {
        throw std::runtime_error("Файл журнала не создан");
    }
    std::remove("test_workflow.log"); // Удаляем временный файл
}

// Проверяем что используется правильный уровень логирования по умолчанию.
void test_DefaultLogLevel() {
    WorkFlow workflow("test_workflow.log", "INFO"); // Создаёт тестовый файл и уровень по умолчанию - INFO
    workflow.addTask("Тестовый уровень по умолчанию "); // Добавляем сообщение без указания уровня
    
    // Читаем файл и проверяем, что уровень INFO
    std::ifstream logFile("test_workflow.log");
    std::string line;
    std::getline(logFile, line);
    
    if (line.find("Тестовый уровень по умолчанию [INFO]") == std::string::npos) {
        throw std::runtime_error("Уровень журнала по умолчанию не работает");
    }
    std::remove("test_workflow.log"); // Удаляем временный файл
}

// Проверяем что WorkFlow корректно работает в многопоточном режиме.
void test_ThreadSafety() {
    WorkFlow workflow("test_workflow.log", "INFO");
    const int num_threads = 5; // Количество потоков
    std::vector<std::thread> threads; // Вектор потоков
    
    // Создаем 5 потоков, каждый добавляет свое сообщение
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&workflow, i]() {
            workflow.addTask("Проверка " + std::to_string(i), "DEBUG");
        });
    }
    
    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }
    
    // Проверяем, что все сообщения записаны
    std::ifstream logFile("test_workflow.log");
    int line_count = std::count(
        std::istreambuf_iterator<char>(logFile),
        std::istreambuf_iterator<char>(),
        '\n'
    );
    
    // Проверяет что количество записей в логе = количеству потоков
    if (line_count != num_threads) {
        throw std::runtime_error("Проблема потокобезопасности: ожидаемая " + 
            std::to_string(num_threads) + " logs, got " + 
            std::to_string(line_count));
    }
    std::remove("test_workflow.log"); // Удаляем временный файл
}

// Проверяем что сообщения сохраняют порядок добавления.
void test_MessageOrdering() {
    WorkFlow workflow("test_workflow.log", "INFO");
    
    workflow.addTask("Сообщение 1", "ERROR"); // Первое сообщение
    workflow.addTask("Сообщение 2", "WARNING"); // Второе сообщение
    
    // Даем время на обработку
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Проверяем порядок сообщений
    std::ifstream logFile("test_workflow.log");
    std::string line1, line2;
    std::getline(logFile, line1); // Должно быть Сообщение 1
    std::getline(logFile, line2); // Должно быть Сообщение 2
    
    if (line1.find("Сообщение 1") == std::string::npos || 
        line2.find("Сообщение 2") == std::string::npos) {
        throw std::runtime_error("Неправильный порядок следования сообщений");
    }
    std::remove("test_workflow.log"); // Удаляем временный файл
}

void registerWorkFlowTests() {
    Test::addTest("Проверка потоков: Добавление задач в очередь", test_AddTaskToQueue);
    Test::addTest("Проверка потоков: Уровень логирования", test_DefaultLogLevel);
    Test::addTest("Проверка потоков: Многопоточный режим", test_ThreadSafety);
    Test::addTest("Проверка потоков: Порядок сообщений", test_MessageOrdering);
}