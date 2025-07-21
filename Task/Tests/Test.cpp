#include "Test.h"
#include <iostream>

static std::vector<std::pair<std::string, std::function<void()>>> tests; // Список всех тестов

void Test::addTest(const std::string& name, std::function<void()> test) { // Добавляем новый тест в список
    tests.emplace_back(name, test);
}

void Test::runAllTests() {
    size_t passed = 0; // Счётчик пройденных тестов
    for (const auto& [name, test] : tests) {
        try {
            test();
            std::cout << "[Удачно] " << name << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cerr << "[Не удачно] " << name << ": " << e.what() << std::endl; // При известных исключениях
        } catch (...) {
            std::cerr << "[Не удачно] " << name << ": неизвестная ошибка" << std::endl; // При неизвестных исключениях 
        }
    }
    std::cout << "Сводка: " << passed << "/" << tests.size() << " пройдены" << std::endl; // Выводим итоговую сводку
}