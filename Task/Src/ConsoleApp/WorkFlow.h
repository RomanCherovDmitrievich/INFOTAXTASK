#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <string>
#include <memory>

#include "../Library/Library.h"

struct LogTask {
    std::string message; // Текст сообщения для записи в лог
    std::string level;  // Уровень важности сообщения
};

//Гарантирует безопасность при работе из нескольких потоков
class ThreadSafeQueue {
public:
    void push(const LogTask& task); // Добавляет задачу в очередь(выбрал именно это так как это потокобезопасно)
    bool pop(LogTask& task); // Извлекаем задачу из очереди(возвращает true если задача была извлечена)

private:
    std::queue<LogTask> queue; // Обычная очередь задач
    std::mutex mtx; // Защищает доступ к очереди
    std::condition_variable cv; // Для уведомления ожидающих потоков
};

class WorkFlow {
public:
    WorkFlow(const std::string& logFilePath, const std::string& defaultLevel); // Создаёт поток, принимаем путь к файлу лога, а так же автоматический делаем уровень для сообщения по умолчанию
    ~WorkFlow(); // Останавливает рабочий поток
    void addTask(const std::string& message, const std::string& level = ""); // Добавляет новую задачу в очередь
    void stop(); // Останавливает рабочий поток(дожидаемся завершения обработки оставшихся задач)

private:
    void processTasks();

    std::unique_ptr<ILog> log; // Указатель на объект лога
    ThreadSafeQueue tasks; // Очередь задач для обработки
    std::thread workerThread; // Поток для асинхронной обработки задач
    std::atomic<bool> isRunning; // Атомарный флаг работы потока(позволяет безопасно останавливать поток)
    std::string defaultLevel; // Уровень логирования по умолчанию
};