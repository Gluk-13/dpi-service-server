#pragma once
#include "tcp.h"

class IPParser {
  private:
    TCPParser tcp_parser_;
  public: 
    void parse(const unsigned char* packet, size_t len);
};
//Описать TCP parse и оставшейся цепочки.