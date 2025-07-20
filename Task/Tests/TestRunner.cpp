#include "Test.h"
#include "TestLog.h"       // Подключаем тесты Log
#include "TestWorkFlow.h"  // Подключаем тесты WorkFlow

int main() {
    // Регистрируем все тесты
    registerLogTests();
    registerWorkFlowTests();
    
    // Запускаем все тесты
    Test::runAllTests();
    return 0;
}