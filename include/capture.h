#pragma once
#include <iostream>
#include <functional>
#include <pcap/pcap.h>

class Capture {
  public: 

  using Callback = std::function<void(const unsigned char*, int)>;

  Capture(const std::string& iface);

  ~Capture();

  bool start(Callback callback);

  void stop();

  private:
  static void packetHandler(unsigned char* user, const pcap_pkthdr* header, const unsigned char* packet);

  std::string iface_;
  pcap_t* handle_;
  bool running_;
  Callback callback_;
};