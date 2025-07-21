#include "WorkFlow.h"
#include <iostream>
#include <string>

// Проверяет корректность уровня логирования.
bool isValidLevel(const std::string& level) {
    return level == "INFO" || level == "WARNING" || level == "ERROR";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    const std::string logFile = argv[1];
    std::string defaultLevel = "INFO";

    if (argc > 2) {
        defaultLevel = argv[2];
        if (!isValidLevel(defaultLevel)) {
            std::cerr << "Ошибка: Неверный уровень'" << defaultLevel << "'\n";
            return 1;
        }
    }

    try {
        WorkFlow worker(logFile, defaultLevel);

        std::cout << "Приложение работает. Уровень сообщений по умолчанию: " << defaultLevel << "\n"
                  << "Сообщение выглядит: '<message> [LEVEL]'\n"
                  << "Пример: 'Hello ERROR'\n"
                  << "Нажмите Ctrl+C для выхода\n";

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
            std::cout << "Сообщение:" << message << "[" << level << "] "  << "\n";
        }

    } catch (const std::exception& e) { // Обработка ошибок
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}