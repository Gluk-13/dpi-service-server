#pragma once
#include "ip.h"

class GREParser {
  private:
    IPParser ip_parser_;
  public: 
    void parse(const unsigned char* packet, size_t len, int ipLen, bool isV4);
};