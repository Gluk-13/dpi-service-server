#pragma once

class TCPParser {
  private: 
  
  public: 
    void parse(const unsigned char* packet, int len);
    
    bool isHTTP(const unsigned char* data, size_t len);
};