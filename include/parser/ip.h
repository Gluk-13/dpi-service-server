#pragma once
#include "tcp.h"

class IPParser {
  private:
    TCPParser tcp_parser_; // Дописать
  public: 
    void parse(const unsigned char* packet, size_t len, bool isV4);
};