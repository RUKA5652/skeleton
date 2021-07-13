//#pragma once	//�V���O���g���N���X�@���I
//class SceneMneg
//{
//public:
//	static  SceneMneg& GetInstance(void)
//	{
//		Create();//�ܑ̂Ȃ������ɂȂ邯��ǈ��S���u�ɂ͂Ȃ�
//		return *s_Instance;
//	}
//
//	static	void Create(void) //�v���O���������[�h���ꂽ�Ƃ��ɃA�h���X�����蓖�Ă���@�A�h���X������Ȃ�A�N�Z�X�ł���
//	{
//		if (!s_Instance)
//		{
//			s_Instance = new SceneMneg();
//		}
//	}
//	static	void Destroy(void) //�v���O���������[�h���ꂽ�Ƃ��ɃA�h���X�����蓖�Ă���@�A�h���X������Ȃ�A�N�Z�X�ł���
//	{
//		delete s_Instance;//�����̃A�N�Z�X�����Ȃ��ꏊ�ɃA�N�Z�X����delete���悤�Ƃ���Ɛ������
//		s_Instance = nullptr;
//	}
//
//	void Update(void);
//	void Draw(void);
//
//private:
//	static SceneMneg* s_Instance;	//���j�[�N�|�C���^�ŊǗ�����Ύ����Ńf�X�g���C�ł���
//	SceneMneg();
//	~SceneMneg();
//
//};

#pragma once	//�V���O���g���N���X�@�ÓI
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
