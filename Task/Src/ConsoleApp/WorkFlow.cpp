#include "WorkFlow.h"
#include <iostream>

// Добавление задачи в потокобезопасную очередь.
void ThreadSafeQueue::push(const LogTask& task) {
    std::lock_guard<std::mutex> lock(mtx); // Блокировка мьютекса
    queue.push(task); // Добавление задачи в очередь
    cv.notify_one(); // Уведомление одного ожидающего потока(пробуждает один поток, ожидающий на condition variable)
}

// Извлечение задачи из очереди
bool ThreadSafeQueue::pop(LogTask& task) {
    std::unique_lock<std::mutex> lock(mtx); // - блокируем мьютекс
    cv.wait(lock, [this] { return !queue.empty(); }); // Ожидаем задачи
    task = queue.front(); //  - копируем задачу
    queue.pop(); // - удаляем задачу из очереди
    return true;
}

// Инициализация системы логирования.
WorkFlow::WorkFlow(const std::string& logFilePath, const std::string& level)
    : isRunning(true), defaultLevel(level)  {
    log = LogFactory::createFileLog(logFilePath); // - создаём лог
    workerThread = std::thread(&WorkFlow::processTasks, this); // - запускаем поток обработки задач
}

WorkFlow::~WorkFlow() {
    stop();
}

// Добавление сообщения в очередь на логирование.
void WorkFlow::addTask(const std::string& message, const std::string& level) {
    tasks.push({message, level.empty() ? defaultLevel : level});  // Исправлен синтаксис push
}

//  Основной цикл обработки задач
void WorkFlow::processTasks() {
    while (isRunning) {
        LogTask task;
        if (tasks.pop(task)) { // Извлекаем задачу (блокируем, если очередь пуста)
            log->log(task.message, task.level); // Выполняем запись в лог
        }
    }
}

// Остановка системы логирования.
void WorkFlow::stop() {
    isRunning = false;
    tasks.push({"", ""});  // Разблокировать поток
    if (workerThread.joinable()) {
        workerThread.join(); // - ожидание завершения потока
    }
}