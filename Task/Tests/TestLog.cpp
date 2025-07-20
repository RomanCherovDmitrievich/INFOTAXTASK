#include "TestLog.h"          // Новый заголовочный файл
#include "../Src/Library/Library.h"
#include <cassert>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void testLogCreation() {
    const std::string testFile = "test_log.txt";
    auto logger = LogFactory::createFileLog(testFile);
    assert(logger != nullptr && "Logger creation failed");
    assert(fs::exists(testFile) && "Log file not created");
    fs::remove(testFile);
}

void testLogWriting() {
    const std::string testFile = "test_log_write.txt";
    const std::string testMessage = "Test message";
    const std::string testLevel = "INFO";
    
    auto logger = LogFactory::createFileLog(testFile);
    logger->log(testMessage, testLevel);
    
    std::ifstream file(testFile);
    std::string content((std::istreambuf_iterator<char>(file)), 
                        std::istreambuf_iterator<char>());
    
    assert(content.find(testMessage) != std::string::npos && "Message not found in log");
    assert(content.find(testLevel) != std::string::npos && "Log level not found");
    fs::remove(testFile);
}

void registerLogTests() {
    Test::addTest("Log: Creation", testLogCreation);
    Test::addTest("Log: Writing", testLogWriting);
}