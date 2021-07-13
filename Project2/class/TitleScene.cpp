#include "TitleScene.h"
#include"../_debug/_DebugConOut.h"
#include<DxLib.h>
#include"GameScene.h"
#include"transition/ClosOver.h"
#include "common/ImageMneg.h"

TitleScene::TitleScene()
{
	Init();
  DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{

}

bool TitleScene::Init(void)
{
  lpImageMneg.GetID("resource/A.png","A.png");//LoadGraph("resource/A.png");
  return false;
}

uniqueScene TitleScene::Update(const double& delta, uniqueScene ownScene)
{

  if (CheckHitKeyAll())
  {
    if (oldKey != CheckHitKeyAll())
    {
      return std::make_unique<ClosOver>(std::move(ownScene), std::make_unique<GameScene>());
    }
  }  
  oldKey = CheckHitKeyAll();
  DrawOwnScreen(delta);
	return  ownScene;//std::move(ownScene)って書かなくてよくなった　暗黙的ムーブをしてくれてる明示的に書きたいなら書いてね
}


void TitleScene::DrawOwnScreen(const double& delta)
{
  SetDrawScreen(screenID_);
  ClearDrawScreen();
  DrawGraph(0, 0, lpImageMneg.GetID("A.png")[0], true);
}
