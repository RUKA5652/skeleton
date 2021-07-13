#pragma once
#include "Controller.h"
class KeyInput :
    public Controller
{
public:
  KeyInput();
  ~KeyInput();
private:
  void Update() override;
  //char keystate_[256];
  std::array<char, 256U> keystate_;
  CntType GetCntType(void) override { return CntType::Key; };
};

