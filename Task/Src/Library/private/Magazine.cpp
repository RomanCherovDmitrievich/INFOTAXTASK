#include "../Library.h"
#include <chrono>
#include <iomanip>

//Принимаем путь к файлу для записи. Создаём директорию если её нет, открываем файл для записи в режиме добавления
FileLog::FileLog(const std::string& logFilePath) : filePath(logFilePath) {
    std::filesystem::path dir = std::filesystem::path(logFilePath).parent_path();
    if (!dir.empty() && !std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }
    logFile.open(logFilePath, std::ios::app);
}

//Принимаем сообщение и его уровень, смотрим время получения сообщения и тоже записываем в файл
void FileLog::log(const std::string& message, const std::string& level) {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    logFile << std::put_time(std::localtime(&now_time), "[%Y-%m-%d %H:%M:%S] ");
    logFile << "[" << level << "] " << message << std::endl;
}

//Уничтожаем объект logfile
FileLog::~FileLog() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

//Используем фабричный метод для создания объектов
std::unique_ptr<ILog> LogFactory::createFileLog(const std::string& filePath) {
    return std::make_unique<FileLog>(filePath); // Умный указатель который будет управлять памятью(Он хранит указатель на интерфейс, а не на конкретную реализацию)
}