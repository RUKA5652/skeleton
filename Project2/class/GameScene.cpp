#include "GameScene.h"
#include<DxLib.h>
#include"TitleScene.h"
#include "transition/ClosOver.h"
#include "transition/RotAutDoor.h"
#include "SceneMneg.h"
#include "common/ImageMneg.h"
#include "../_debug/_DebugConOut.h"
#include"obj/Player.h"


GameScene::GameScene()
{
  Init();
  DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
  //lpImageMneg.GetID("resource/B.png", "B.png");
  tmxObj_.LoadTMX("resource/Map.tmx");
  objList_.emplace_back(std::make_unique<Player>(CntType::Key));
 // objList_.emplace_back(std::make_unique<Player>(CntType::Pad));
  return false;
}

uniqueScene GameScene::Update(const double& delta, uniqueScene ownScene)
{

  if (CheckHitKeyAll())
  {
    if (oldKey != CheckHitKeyAll())
    {
      //return std::make_unique<RotAutDoor>(std::move(ownScene), std::make_unique<TitleScene>(),Vector2(ScreenSizeX, ScreenSizeY));
    }
  }  
  for (const auto& obj : objList_)
  {
    obj->Update(&tmxObj_,delta);
  }
 
  oldKey = CheckHitKeyAll();
  DrawOwnScreen(delta);
  return ownScene;
}



void GameScene::DrawOwnScreen(const double& delta)
{
  SetDrawScreen(screenID_);
  ClearDrawScreen();
  //DrawGraph(0, 0, lpImageMneg.GetID("B.png")[0], true);
  
 /* auto DrawMapChip = [&](const std::string layer) {    
    auto& size = tmxObj_.GetTileSize();
    for (int x = 0; x < tmxObj_.GetWordArea().x; x++)
    {
      for (int y = 0; y < tmxObj_.GetWordArea().y; y++)
      {
        int no = tmxObj_.GetMapData(layer, x, y);
        if (no < tmxObj_.GetFirstGID())
        {
          continue;
        }
        no -= tmxObj_.GetFirstGID();

        DrawGraph(x * size.x , y * size.y , lpImageMneg.GetID("mapChip.png")[no], true);
      }
    }
  };
  DrawMapChip("block");
  DrawMapChip("line");
  DrawMapChip("pipe");*/
    auto& size = tmxObj_.GetTileSize();
  for (const auto& layer : tmxObj_.GetMapData())
  {
    auto& layerString = layer.first;
    for (int x = 0; x < tmxObj_.GetWordArea().x; x++)
    {
      for (int y = 0; y < tmxObj_.GetWordArea().y; y++)
      {   
        //auto gid = layer.second[y * tmxObj_.GetWordArea().x + x]- static_cast<int>(tmxObj_.GetFirstGID();//‚Ç‚¿‚ç‚Å‚à‰Â
        auto gid = tmxObj_.GetMapData(layerString,x,y) - static_cast<int>(tmxObj_.GetFirstGID());
        if (gid < 0)
        {
          continue;
        }
        DrawGraph(x * size.x, y * size.y, lpImageMneg.GetID("mapChip.png")[gid], true);
      }
    }
  }
  for (const auto& obj : objList_)
  {
    obj->Draw();
  }
}
