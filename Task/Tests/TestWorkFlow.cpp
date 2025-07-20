#include "TestWorkFlow.h"
#include "../Src/ConsoleApp/WorkFlow.h"
#include "../Src/Library/Library.h"
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>

void test_AddTaskToQueue() {
    WorkFlow workflow("test_workflow.log", "INFO");
    workflow.addTask("Test message", "WARNING");
    
    if (!std::ifstream("test_workflow.log").good()) {
        throw std::runtime_error("Log file not created");
    }
    std::remove("test_workflow.log");
}

void test_DefaultLogLevel() {
    WorkFlow workflow("test_workflow.log", "INFO");
    workflow.addTask("Test default level");
    
    std::ifstream logFile("test_workflow.log");
    std::string line;
    std::getline(logFile, line);
    
    if (line.find("[INFO] Test default level") == std::string::npos) {
        throw std::runtime_error("Default log level not working");
    }
    std::remove("test_workflow.log");
}

void test_ThreadSafety() {
    WorkFlow workflow("test_workflow.log", "INFO");
    const int num_threads = 5;
    std::vector<std::thread> threads;
    
    // Запускаем несколько потоков
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&workflow, i]() {
            workflow.addTask("Thread " + std::to_string(i), "DEBUG");
        });
    }
    
    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }
    
    // Проверяем количество записей в файле
    std::ifstream logFile("test_workflow.log");
    int line_count = std::count(
        std::istreambuf_iterator<char>(logFile),
        std::istreambuf_iterator<char>(),
        '\n'
    );
    
    if (line_count != num_threads) {
        throw std::runtime_error("Thread safety issue: expected " + 
            std::to_string(num_threads) + " logs, got " + 
            std::to_string(line_count));
    }
    std::remove("test_workflow.log");
}

void test_MessageOrdering() {
    WorkFlow workflow("test_workflow.log", "INFO");
    
    workflow.addTask("Message 1", "ERROR");
    workflow.addTask("Message 2", "WARNING");
    
    // Даем время на обработку
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Проверяем порядок сообщений
    std::ifstream logFile("test_workflow.log");
    std::string line1, line2;
    std::getline(logFile, line1);
    std::getline(logFile, line2);
    
    if (line1.find("Message 1") == std::string::npos || 
        line2.find("Message 2") == std::string::npos) {
        throw std::runtime_error("Message ordering incorrect");
    }
    std::remove("test_workflow.log");
}

void registerWorkFlowTests() {
    Test::addTest("WorkFlow: AddTaskToQueue", test_AddTaskToQueue);
    Test::addTest("WorkFlow: DefaultLogLevel", test_DefaultLogLevel);
    Test::addTest("WorkFlow: ThreadSafety", test_ThreadSafety);
    Test::addTest("WorkFlow: MessageOrdering", test_MessageOrdering);
}