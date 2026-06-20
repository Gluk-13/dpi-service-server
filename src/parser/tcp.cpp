#include <iostream>
#include <cstdint>
#include <cstring>
#include "tcp.h"



bool TCPParser::isHTTP(const unsigned char* data, size_t len) {
    if (len < 4) return false;

    if (strncmp((const char*)data, "GET ", 4) == 0) return true;
    if (strncmp((const char*)data, "POST", 4) == 0) return true;
    if (strncmp((const char*)data, "PUT ", 4) == 0) return true;
    if (strncmp((const char*)data, "HEAD", 4) == 0) return true;
    if (strncmp((const char*)data, "DELE", 4) == 0) return true;
    if (strncmp((const char*)data, "OPTI", 4) == 0) return true;
    if (strncmp((const char*)data, "PATC", 4) == 0) return true;
    if (strncmp((const char*)data, "HTTP", 4) == 0) return true;
    
    return false;
}

void TCPParser::parse(const unsigned char* packet, int len) {
  if (len < 20) {
    std::cerr << "Ошибка парсинга TCP: недостаточно данных в пакете" << std::endl;
    return;
  }

  uint8_t offset_byte = packet[12];
  uint8_t data_offset = (offset_byte >> 4) & 0x0F;
  int tcp_header_len = data_offset * 4;

  if (len < tcp_header_len) {
    std::cerr << "Ошибка парсинга TCP: пакет слишком короткий для заголовка" << std::endl;
    return;
  }

  const unsigned char* data = packet + tcp_header_len;
  size_t data_len = len - tcp_header_len;

  if (data_len == 0) {
    std::cerr << "Нет данных" << std::endl;
    return;
  }
  
  bool result = isHTTP(data, data_len);

  if (result) {
    std::cout << "HTTP: (" << data_len << "байт);" << std::endl;
    std::cout.write((const char*) data, data_len);
    std::cout << std::endl;
  }
};