#include "WorkFlow.h"
#include <iostream>
#include <string>

void printUsage() {
    std::cout << "Usage:\n"
              << "  ConsoleApp <log_file> [default_level]\n"
              << "  Default level: INFO\n"
              << "  Available levels: INFO, WARNING, ERROR\n"
              << "Example:\n"
              << "  ConsoleApp logs/app.log WARNING\n";
}

bool isValidLevel(const std::string& level) {
    return level == "INFO" || level == "WARNING" || level == "ERROR";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    const std::string logFile = argv[1];
    std::string defaultLevel = "INFO";

    if (argc > 2) {
        defaultLevel = argv[2];
        if (!isValidLevel(defaultLevel)) {
            std::cerr << "Error: Invalid level '" << defaultLevel << "'\n";
            printUsage();
            return 1;
        }
    }

    try {
        WorkFlow worker(logFile, defaultLevel);

        std::cout << "Logger started. Default level: " << defaultLevel << "\n"
                  << "Enter messages in format: '<message> [LEVEL]'\n"
                  << "Example: 'Hello ERROR'\n"
                  << "Press Ctrl+C to exit\n";

        std::string input;
        while (std::getline(std::cin, input)) {
            if (input.empty()) continue;

            size_t lastSpace = input.rfind(' ');
            std::string message, level;

            if (lastSpace != std::string::npos) {
                level = input.substr(lastSpace + 1);
                if (isValidLevel(level)) {
                    message = input.substr(0, lastSpace);
                } else {
                    message = input;
                    level = defaultLevel;
                }
            } else {
                message = input;
                level = defaultLevel;
            }

            worker.addTask(message, level);
            std::cout << "Logged: [" << level << "] " << message << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}