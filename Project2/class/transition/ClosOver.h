#pragma once
#include"TransitionScene.h"

class ClosOver :
    public TransitionScene
{
public:
  ClosOver(uniqueScene beforScene, uniqueScene afterScene,const double& limitTime = 3);
  ~ClosOver();
private:
  double limitTime_;
  bool UpdateTransition(const double& delta) override;
  void DrawOwnScreen(const double& delta) override;
};

