#include "network_interface.h"
#include "capture.h"
#include "logger.h" //Подключить логгирование на локальный хост в дальнейшем
#include <iostream>

int main() {
    std::string iface = findWorkingInterface();
    if (iface.empty()) {
        std::cerr << "Не найден рабочий интерфейс" << std::endl;//Заменить
        return 1;
    }
    
    std::cerr << "Не найден рабочий интерфейс" << std::endl;//Заменить

    Capture capture(iface);
    capture.start([](const u_char* packet, int len) {
      
    });
    
    return 0;
}