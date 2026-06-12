#include <iostream>
#include <cstdint>
#include "ip.h"
#include "ethernet.h"

void EthernetParser::parse(const unsigned char* packet, size_t len) {
  if (len < 14) {
    std::cerr << "Ошибка: недостаточно данных в пакете" << std::endl;
    return;
  }

  uint16_t ethertype = (packet[12] << 8) | packet[13];

  if (ethertype == 0x0800) {
    ip_parser_.parse(packet + 14, len - 14);
  }

  if (ethertype == 0x86DD) {
    ip_parser_.parse(packet + 14, len - 14);
  }
};