#pragma once
#include <vector>
#include <functional>
#include <string>

class Test {
public:
    static void addTest(const std::string& name, std::function<void()> test); // Функция добавления новых тестов в список
    static void runAllTests(); // Функция проверок тестов и вывод сводок
};