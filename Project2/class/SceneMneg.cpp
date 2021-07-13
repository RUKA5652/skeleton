#include "SceneMneg.h"
#include<chrono> //時間周り
#include<DxLib.h>
#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"
#include"TitleScene.h"//filterの場所から見てるよ～


//SceneMneg* SceneMneg::s_Instance = nullptr;　動的なシングルトンの時のみ必要

void SceneMneg::Run(void)
{
	if (!initFlag)
	{
		if (!SysInit())
		{
			return;
		}
	}

	scene_ = std::make_unique<TitleScene>();

	auto timeStart = std::chrono::system_clock::now();
	auto timeEnd = timeStart;
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))	//ProcessMessage() == 0 でウィンドウが死んだときにwhileの外に出る
	{
		_dbgStartDraw();
		timeEnd = timeStart;
		timeStart = std::chrono::system_clock::now();
		//---フレームの経過時間計算
		auto delta = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(timeStart - timeEnd).count());
		delta = (delta <= 0 ? delta = 0 : delta / (1000000.0));//doubleなら.0をfloatなら.0fを
		//--更新処理---
		scene_ = scene_->Update(delta, std::move(scene_));


		//-----------描画----------------
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		scene_->Draw(delta);
		//パフォーマンス計測
		//ドローコール
		TRACE("DrawCall%d,FPS%f\n", DxLib::GetDrawCallCount(), DxLib::GetFPS());
		_dbgAddDraw();
		ScreenFlip();
		
	}

	if (ProcessMessage() == 0)//ウィンドウが閉じる際に何かアクションを起こす
	{

	}

}

void SceneMneg::Update(void)
{
}

void SceneMneg::Draw(void)
{
}

SceneMneg::SceneMneg()
{
	initFlag = SysInit();
}

SceneMneg::~SceneMneg()
{
}

bool SceneMneg::SysInit(void)
{
	SetWindowText("アクションゲーム_2016016_杉岡　竜二");		//文字列の場合""これがいる 課題2_学籍番号_名前		コピペを防ぐため	ウィンドウの名前
//-----システム処理-----
//ウィンドウサイズ設定
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);		//scnArea_.x×scnArea_.yドット65536色モードに設定　16bit=65536
	//ウィンドウモード固定
	ChangeWindowMode(true);
	//DXLib準備
	if (DxLib_Init() == -1)
	{
		return false;
	}
	//デバック表示系　初期化
	_dbgSetup(ScreenSizeX, ScreenSizeY, 255);			//255は透明度	

	return true;
}
