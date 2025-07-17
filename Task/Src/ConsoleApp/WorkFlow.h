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
    std::string message; // - текст сообщения для записи в лог
    std::string level;  // - уровень важности сообщения
};

//Гарантирует безопасность при работе из нескольких потоков
class ThreadSafeQueue {
public:
    void push(const LogTask& task); // Добавляем задачу в очередь(выбрал именно это так как это потокобезопасно)
    bool pop(LogTask& task); // Извлекаем задачу из очереди(возвращает true если задача была извлечена)

private:
    std::queue<LogTask> queue; // - обычная очередь задач
    std::mutex mtx; // - защищает доступ к очереди
    std::condition_variable cv; // - для уведомления ожидающих потоков
};

class WorkFlow {
public:
    WorkFlow(const std::string& logFilePath, const std::string& defaultLevel); // создаём поток, принимаем путь к файлу лога, а так же автоматический делаем уровень для сообщения по умолчанию
    ~WorkFlow(); // - останавливаем рабочий поток
    void addTask(const std::string& message, const std::string& level = ""); // - добавляем новую задачу в очередь
    void stop(); // - останавливает рабочий поток(дожидаемся завершения обработки оставшихся задач)

private:
    void processTasks();

    std::unique_ptr<ILog> log; // - указатель на объект лога
    ThreadSafeQueue tasks; // - очередь задач для обработки
    std::thread workerThread; // - поток для асинхронной обработки задач
    std::atomic<bool> isRunning; // - атомарный флаг работы потока(позволяет безопасно останавливать поток)
    std::string defaultLevel; // - уровень логирования по умолчанию
};