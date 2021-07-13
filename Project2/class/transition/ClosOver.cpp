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
	if ((cnt_ += delta) > limitTime_)//Œã‚ë‰‰Z‚¾‚Æcnt‚ª‚³‚«‚ÉƒŒƒWƒXƒ^‚É“ü‚è{{”äŠr‰‰Z@‘O‰‰Z‚¾‚Æ{{‚ª“ü‚è‰½‚ÉHcnt‚É{{‚³‚ê‚Ä‚©‚çƒŒƒWƒXƒ^‚É“ü‚è”äŠr‰‰Z
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


