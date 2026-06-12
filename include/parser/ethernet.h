#pragma once
#include "ip.h"
#include <iostream>

class EthernetParser {
  private: 
    IPParser ip_parser_;
  public:
    void parse(const unsigned char* packet, size_t len);
};