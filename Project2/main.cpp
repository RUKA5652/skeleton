#include<DxLib.h>	//""ダブルコーテーションはプロジェクトの場所から見る　主に自分たちが作ったヘッダ　<>はパスが登録されてる奴らを見るよ　主に外部ライブラリ
//インクルードの仕方でコンパイルにかかる時間が変わる
#include"class/SceneMneg.h"
//#include"_debug/_DebugConOut.h"
//#include"_debug/_DebugDispOut.h"
//#include"class/TitleScene.h"//filterの場所から見てるよ～
//#include<chrono> //時間周り


//constexpr int ScreenSizeX = 1024;
//constexpr int ScreenSizeY = 768;



//bool SysInit(void)
//{
//	SetWindowText("アクションゲーム_2016016_杉岡　竜二");		//文字列の場合""これがいる 課題2_学籍番号_名前		コピペを防ぐため	ウィンドウの名前
//	//-----システム処理-----
//	//ウィンドウサイズ設定
//	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);		//scnArea_.x×scnArea_.yドット65536色モードに設定　16bit=65536
//	//ウィンドウモード固定
//	ChangeWindowMode(true);
//	//DxLib準備
//	if (DxLib_Init() == -1)
//	{
//		return false;
//	}
//	//デバック表示系　初期化
//	_dbgSetup(ScreenSizeX, ScreenSizeY, 255);			//255は透明度	
//
//	return true;
//}






int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//エントリーポイント 
{
	lpSceneMneg.Run();


	//if (!SysInit())
	//{
	//	return 0;
	//}

	//std::unique_ptr<BaseScene> scene ;
	//scene = std::make_unique<TitleScene>();


	//auto timeStart = std::chrono::system_clock::now();
	//auto timeEnd = timeStart;
	//while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))	//ProcessMessage() == 0 でウィンドウが死んだときにwhileの外に出る
	//{
	//	_dbgStartDraw();
	//	auto timeEnd = timeStart;
	//	auto timeStart = std::chrono::system_clock::now();
	//	//---フレームの経過時間計算
	//	auto delta = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(timeStart - timeEnd).count());
	//	delta = (delta <= 0 ? delta = 0 : delta / (1000000.0));//doubleなら.0をfloatなら.0fを
	//	//--更新処理---
	//	scene->Update(delta);
	//	


	//	//-----------描画----------------
	//	//SetDrawScreen(DX_SCREEN_BACK);
	//	ClearDrawScreen();
	//	scene->Draw(delta);
	//	_dbgAddDraw();
	//	ScreenFlip();

	//}

	//if (ProcessMessage() == 0)//ウィンドウが閉じる際に何かアクションを起こす
	//{

	//}
	return 1;
}

