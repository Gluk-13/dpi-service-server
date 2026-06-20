#pragma once

class DepthGuard {
  private:
    int max_depth_;
    int current_depth_;

  public:
    DepthGuard(int max_depth = 5) : current_depth_(0), max_depth_(max_depth) {}

    bool nextLevel();

    int getDepth() const;
};
