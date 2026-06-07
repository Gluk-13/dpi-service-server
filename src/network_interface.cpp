#include <ifaddrs.h>
#include <iostream>
#include <net/if.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>

std::string findWorkingInterface() {
  struct ifaddrs *ifaddr;

  if (getifaddrs(&ifaddr) == -1) {
    std::cerr << "Ошибка при поиске адресов" << std::endl;//Заменить
    return "";
  }

  for (struct ifaddrs *ptr = ifaddr; ptr != nullptr; ptr = ptr -> ifa_next) {
    if (ptr -> ifa_flags & IFF_LOOPBACK) continue;
    if (ptr -> ifa_addr == nullptr) continue;
    if (ptr -> ifa_addr->sa_family != AF_INET) continue;

    std::string result = ptr->ifa_name;
    freeifaddrs(ifaddr);
    return result;
  }

  return "";
}