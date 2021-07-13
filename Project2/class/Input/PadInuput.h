#pragma once
#include "Controller.h"
class PadInuput :
    public Controller
{
public:
  PadInuput(int padNo = 0x0001);
  ~PadInuput();
private:
  void Update() override;
  CntType GetCntType(void) override { return CntType::Pad; };
  const int padNo;

};

