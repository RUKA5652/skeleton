#include "BaseScene.h"
#include<DxLib.h>

BaseScene::BaseScene()
{
  GetGraphSize(DX_SCREEN_BACK, &screenSize_.x, &screenSize_.y);
  //SetDrawScreen(DX_SCREEN_BACK);
  //GetDrawScreenSize( &screenSize_.x, &screenSize_.y);
  screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);
  oldKey = CheckHitKeyAll();
}

BaseScene::~BaseScene()
{

}

void BaseScene::Draw(const double& delta)
{
  DrawGraph(0, 0, screenID_, true);
}


