#pragma once
#include "tcp.h"
#include "depth_guard.h"

class IPParser {
  private:
    TCPParser tcp_parser_;
    DepthGuard depth_guard_{5};
  public: 
    void parse(const unsigned char* packet, size_t len);
};