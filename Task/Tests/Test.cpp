#include "Test.h"
#include <iostream>

static std::vector<std::pair<std::string, std::function<void()>>> tests;

void Test::addTest(const std::string& name, std::function<void()> test) {
    tests.emplace_back(name, test);
}

void Test::runAllTests() {
    size_t passed = 0;
    for (const auto& [name, test] : tests) {
        try {
            test();
            std::cout << "[PASS] " << name << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cerr << "[FAIL] " << name << ": " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "[FAIL] " << name << ": Unknown error" << std::endl;
        }
    }
    std::cout << "Summary: " << passed << "/" << tests.size() << " passed" << std::endl;
}