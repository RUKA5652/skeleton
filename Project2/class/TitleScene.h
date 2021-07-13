#pragma once
#include "BaseScene.h"

class TitleScene :
    public BaseScene
{
public:
  TitleScene();
  ~TitleScene();


private:
   bool Init(void)override;
   uniqueScene Update(const double& delta, uniqueScene ownScene) override;
   void DrawOwnScreen(const double& delta) override;
   Scene GetSceneID(void) override { return Scene::Title; };
};

