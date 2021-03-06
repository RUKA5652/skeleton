#include "ClosOver.h"
#include <DxLib.h>
#include <algorithm>




ClosOver::ClosOver(uniqueScene beforScene, uniqueScene afterScene, const double& limitTime) :
	TransitionScene::TransitionScene(std::move(beforScene), std::move(afterScene)), limitTime_(limitTime)
{
	//DrawOwnScreen(0.0);
}

ClosOver::~ClosOver()
{
}


bool ClosOver::UpdateTransition(const double& delta)
{
	if ((cnt_ += delta) > limitTime_)//後ろ演算だとcntがさきにレジスタに入り＋＋比較演算　前演算だと＋＋が入り何に？cntに＋＋されてからレジスタに入り比較演算
	{
		return true;
	}
	cnt_ = std::clamp(cnt_, 0.0, limitTime_);
	return false;
}

void ClosOver::DrawOwnScreen(const double& delta)
{
	SetDrawScreen(screenID_);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast<int>(cnt_ * 255.0 / limitTime_));
	beforScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(cnt_ * 255.0 / limitTime_));
	afterScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


