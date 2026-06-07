#include <iostream>
#include <pcap.h>
#include <cstring>
#include "capture.h"

Capture::Capture(const std::string& iface)
  : iface_(iface)
  , handle_(nullptr)
  , running_(false)
  , callback_(nullptr)
{

}

Capture::~Capture() {
  stop();
}

bool Capture::start(Callback callback) {
  callback_ = callback;

  char errbuf[PCAP_ERRBUF_SIZE];

  pcap_t* handle = pcap_open_live(iface_.c_str(),BUFSIZ,1,1000,errbuf);

  if (handle_ == nullptr) {
    std::cerr << "Ошибка pcap_open_live: " << errbuf << std::endl;//Заменить
    return false;
  }

  running_ = true;

  int result = pcap_loop((pcap_t*)handle_, -1, packetHandler, (unsigned char*)this);

  if (result == -1) {
    std::cerr << "Ошибка pcap_loop: " << pcap_geterr((pcap_t*)handle_) << std::endl;//Заменить
    return false;
  }

  return true;
}

void Capture::stop() {
  if (handle_ != nullptr) {
    pcap_breakloop((pcap_t*)handle_);
    pcap_close(handle_);
    handle_ = nullptr;
  }
  running_ = false;
}

void Capture::packetHandler(unsigned char* user, const struct pcap_pkthdr* header, const unsigned char* packet) {
  Capture* self = (Capture*)user;

  if(self != nullptr && self->running_ && self->callback_) {
    self->callback_(packet, header->len);
  }
}

