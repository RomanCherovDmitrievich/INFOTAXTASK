#pragma once
#include <vector>
#include <functional>
#include <string>

class Test {
public:
    static void addTest(const std::string& name, std::function<void()> test);
    static void runAllTests();
};