#include <iostream>
#include "gre.h"
#include <cstdint>

void GREParser::parse(const unsigned char* packet, size_t len, int ipLen) {
    const unsigned char* gre_start = packet + ipLen;

    if (len - ipLen < 4) {
      std::cerr << "Ошибка: слишком короткий GRE-заголовок" << std::endl;
      return;
    }

    uint16_t gre_flags = (gre_start[0] << 8) | gre_start[1];
    uint16_t gre_protocol = (gre_start[2] << 8) | gre_start[3];

    int gre_header_len = 4;

    if (gre_flags & 0x8000) gre_header_len += 4;
    if (gre_flags & 0x4000) gre_header_len += 4;
    if (gre_flags & 0x2000) gre_header_len += 4;

    if (len - ipLen < gre_header_len) {
      std::cerr << "Ошибка: недостаточно данных для полного GRE-заголовка" << std::endl;
      return;
    }

    const unsigned char* payload = gre_start + gre_header_len;
    size_t payload_len = len - ipLen - gre_header_len;

    if (gre_protocol == 0x0800) {
    ip_parser_.parse(payload, payload_len, true);
  } else if (gre_protocol == 0x86DD) {
    ip_parser_.parse(payload, payload_len, false);
  } else if (gre_protocol == 0x2F) {
    parse(payload, payload_len, 0);
  } else {
    std::cout << "Неизвестный GRE Protocol Type: 0x" << std::hex << gre_protocol << std::endl;
  }
}