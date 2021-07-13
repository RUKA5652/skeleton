#pragma once
#include "BaseScene.h"
#include"common/Tmx/TmxObj.h"
#include <list>

class Obj;

class GameScene :
    public BaseScene
{
public:
  GameScene();
  ~GameScene();



private:
  bool Init(void) override;
  uniqueScene Update(const double& delta, uniqueScene ownScene) override;
  void DrawOwnScreen(const double& delta) override;
  Scene GetSceneID(void) override { return Scene::Game; };
  

  std::list<std::unique_ptr<Obj>> objList_;
  TmxObj tmxObj_;
};

