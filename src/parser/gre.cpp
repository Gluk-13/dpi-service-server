#include <iostream>
#include "gre.h"
#include <cstdint>

void GREParser::parse(const unsigned char* packet, size_t len, int ipLen, bool isV4) {
    const unsigned char* gre_start = packet + ipLen;
    uint16_t gre_protocol = (gre_start[2] << 8) | gre_start[3];
    if (gre_protocol == 0x0800) {
    uint16_t gre_flags = (gre_start[0] << 8) | gre_start[1];
    int gre_header_len = 4;
    if (gre_flags & 0x8000) gre_header_len += 4;
    if (gre_flags & 0x4000) gre_header_len += 4;
    if (gre_flags & 0x2000) gre_header_len += 4;
    ip_parser_.parse(packet + gre_header_len, len - ipLen - gre_header_len, true);
  } else {
    const unsigned char* gre_start = packet + ipLen;
    uint16_t gre_protocol = (gre_start[2] << 8) | gre_start[3];// это неверная строка
  } //Дописать GRE для IPv6
}