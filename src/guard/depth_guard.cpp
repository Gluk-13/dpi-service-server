#include "depth_guard.h"

DepthGuard::DepthGuard(int max_depth) 
    : current_depth_(0), max_depth_(max_depth) {}

bool DepthGuard::nextLevel() {
    if (current_depth_ + 1 > max_depth_) {
      return false;
    }
    current_depth_++;
    return true;
}

int DepthGuard::getDepth() const { return current_depth_; };