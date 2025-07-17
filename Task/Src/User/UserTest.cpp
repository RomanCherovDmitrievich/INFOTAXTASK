#include "../Library/Library.h"
#include <iostream>

int main() {
    try {
        auto logger = LogFactory::createFileLog("logs/magazine.log");
        logger->log("Test message", "INFO");
        logger->log("Warning message", "WARNING");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}