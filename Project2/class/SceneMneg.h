//#pragma once	//シングルトンクラス　動的
//class SceneMneg
//{
//public:
//	static  SceneMneg& GetInstance(void)
//	{
//		Create();//勿体ない処理になるけれど安全装置にはなる
//		return *s_Instance;
//	}
//
//	static	void Create(void) //プログラムがロードされたときにアドレスが割り当てられる　アドレスがあるならアクセスできる
//	{
//		if (!s_Instance)
//		{
//			s_Instance = new SceneMneg();
//		}
//	}
//	static	void Destroy(void) //プログラムがロードされたときにアドレスが割り当てられる　アドレスがあるならアクセスできる
//	{
//		delete s_Instance;//自分のアクセス権がない場所にアクセスしてdeleteしようとすると吹っ飛ぶ
//		s_Instance = nullptr;
//	}
//
//	void Update(void);
//	void Draw(void);
//
//private:
//	static SceneMneg* s_Instance;	//ユニークポインタで管理すれば自動でデストロイできる
//	SceneMneg();
//	~SceneMneg();
//
//};

#pragma once	//シングルトンクラス　静的
#include<memory>
#include"BaseScene.h"

#define lpSceneMneg  SceneMneg::GetInstance()

constexpr int ScreenSizeX = 1024;
constexpr int ScreenSizeY = 768;


class SceneMneg
{
public:
	static  SceneMneg& GetInstance(void)
	{
		static SceneMneg s_Instance;
		return s_Instance;
	}

	void Run(void);

	void Update(void);
	void Draw(void);

private:	
	SceneMneg();
	~SceneMneg();
	bool initFlag;
	bool SysInit(void);
	uniqueScene scene_;

};
