#pragma once
#include"../TitleScene.h"

enum class Transitoin 
{
  ClosOver,
  //CrossFade,
  FadeInOut,
  MAX
};


class TransitionScene :
    public BaseScene
{
public:
  TransitionScene(uniqueScene beforScene, uniqueScene afterScene);
  virtual ~TransitionScene();


private:  
  bool Init(void)override;
  uniqueScene Update(const double& delta, uniqueScene ownScene) override;
  virtual bool UpdateTransition(const double& delta) =0;
  virtual  void DrawOwnScreen(const double& delta) override {} ;
protected:
  double cnt_;
  uniqueScene beforScene_, afterScene_;
  Scene GetSceneID(void) override final { return Scene::Transiton; };
};

