#include <iostream>
#include "ip.h"
#include "gre.h"
#include "depth_guard.h"
#include <cstdint>

void IPParser::parse(const unsigned char* packet, size_t len, bool isV4) {
  TCPParser tcp_p;
  UDPParser udp_p; // Дописать
  SCTPParser sctp_p; // Дописать
  GREParser gre_p;
  DepthGuard depth_guard_;

  if (!depth_guard_.nextLevel()) {
    std::cerr << "Превышена глубина вложенности IP" << std::endl;
    return;
  }

  if (isV4) {
    if (len < 20) {
      std::cerr << "Ошибка парсинга IPv4: недостаточно данных в пакете" << std::endl;
      return;
    }
    uint8_t first_byte = packet[0];
    uint8_t ihl = first_byte & 0x0F;
    if (ihl < 5) {
      std::cerr << "Ошибка парсинга IPv4: недостаточно данных в пакете" << std::endl;
      return;
    }
    int ipLen = ihl * 4;
    uint8_t protocol = packet[9];
    if (protocol == 6) {
      tcp_p.parse(packet + ipLen, len - ipLen);
    }

    if (protocol == 17) {
      udp_p.parse(packet + ipLen, len - ipLen);
    }

    if (protocol == 1) {
      std::cout << "Отработал служебный протокол ICMP" << std::endl;
    }

    if (protocol == 132) {
      sctp_p.parse(packet + ipLen, len - ipLen);
    }

    if (protocol == 44) {
      std::cout << "Отработал фрагмент IPv6" << std::endl;
    }

    if (protocol == 47) {
      gre_p.parse(packet, len, ipLen);
    }

  } else {
    if (len < 40) {
      std::cerr << "Ошибка парсинга IPv6: недостаточно данных в пакете" << std::endl;
      return;
    }
  }
}
