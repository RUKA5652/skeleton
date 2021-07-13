#include "TransitionScene.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"
#include <DxLib.h>





TransitionScene::TransitionScene(uniqueScene beforScene, uniqueScene afterScene): beforScene_(std::move(beforScene)),afterScene_(std::move(afterScene))
{
	Init();
}


TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init(void)
{
	cnt_ = 0;
	SetDrawScreen(screenID_);
	ClearDrawScreen();
	beforScene_->Draw(0.0);
	return false;
}

uniqueScene TransitionScene::Update(const double& delta, uniqueScene ownScene)
{
	if (UpdateTransition(delta))
	{
		return	std::move(afterScene_);
	}
	DrawOwnScreen(delta);
	return ownScene;
}
