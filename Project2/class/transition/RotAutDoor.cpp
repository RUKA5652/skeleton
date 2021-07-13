#include "RotAutDoor.h"
#include <DxLib.h>




RotAutDoor::RotAutDoor(uniqueScene beforScene, uniqueScene nextScene, Vector2 pos)
	: TransitionScene::TransitionScene(std::move(beforScene), std::move(nextScene))
{
	count_ = 0;
	Init_();
	//DrawOwnScreen(0.0);
}

RotAutDoor::~RotAutDoor()
{

}

bool RotAutDoor::UpdateTransition(const double& delta)
{
	count_ += 180 * delta;
	return (0 > (screenSize_.y / 2) - (count_ * count_) / 200);
}



void RotAutDoor::DrawOwnScreen(const double& delta)
{
	SetDrawScreen(screenID_);
	ClearDrawScreen();
	afterScene_->Draw(delta);
	DrawRotaGraphFast(-count_ + (screenSize_.x / 2) / 2, (screenSize_.y / 2) - (count_ * count_) / 200, cos((count_) / 200.0), (n_ / 180) * count_ * 2, Screen_[0], true, false);
	DrawRotaGraphFast(screenSize_.x - (screenSize_.x / 2) / 2 + count_, (screenSize_.y / 2) - (count_ * count_) / 200, cos(-((count_) / 200.0)), (n_ / 180) * count_ * 2, Screen_[1], true, false);
}

void RotAutDoor::Init_(void)
{
	beforScreen = MakeScreen(screenSize_.x, screenSize_.y, true);
	SetDrawScreen(beforScreen);
	ClsDrawScreen();
	beforScene_->Draw(0.0f);
	for (int a = 0; a < NUM; a++)
	{
		Screen_[a] = MakeScreen(screenSize_.x/2, screenSize_.y, true);
		SetDrawScreen(Screen_[a]);
		ClsDrawScreen();
		if (a == 0)
		{
			DrawGraph(0,0, beforScreen, true);
		}
		else
		{
			DrawGraph(-(screenSize_.x / 2),0, beforScreen, true);
		}
	}
}
