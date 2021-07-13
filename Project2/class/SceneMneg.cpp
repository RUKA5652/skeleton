#include "SceneMneg.h"
#include<chrono> //���Ԏ���
#include<DxLib.h>
#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"
#include"TitleScene.h"//filter�̏ꏊ���猩�Ă��`


//SceneMneg* SceneMneg::s_Instance = nullptr;�@���I�ȃV���O���g���̎��̂ݕK�v

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
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))	//ProcessMessage() == 0 �ŃE�B���h�E�����񂾂Ƃ���while�̊O�ɏo��
	{
		_dbgStartDraw();
		timeEnd = timeStart;
		timeStart = std::chrono::system_clock::now();
		//---�t���[���̌o�ߎ��Ԍv�Z
		auto delta = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(timeStart - timeEnd).count());
		delta = (delta <= 0 ? delta = 0 : delta / (1000000.0));//double�Ȃ�.0��float�Ȃ�.0f��
		//--�X�V����---
		scene_ = scene_->Update(delta, std::move(scene_));


		//-----------�`��----------------
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		scene_->Draw(delta);
		//�p�t�H�[�}���X�v��
		//�h���[�R�[��
		TRACE("DrawCall%d,FPS%f\n", DxLib::GetDrawCallCount(), DxLib::GetFPS());
		_dbgAddDraw();
		ScreenFlip();
		
	}

	if (ProcessMessage() == 0)//�E�B���h�E������ۂɉ����A�N�V�������N����
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
	SetWindowText("�A�N�V�����Q�[��_2016016_�����@����");		//������̏ꍇ""���ꂪ���� �ۑ�2_�w�Дԍ�_���O		�R�s�y��h������	�E�B���h�E�̖��O
//-----�V�X�e������-----
//�E�B���h�E�T�C�Y�ݒ�
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);		//scnArea_.x�~scnArea_.y�h�b�g65536�F���[�h�ɐݒ�@16bit=65536
	//�E�B���h�E���[�h�Œ�
	ChangeWindowMode(true);
	//DXLib����
	if (DxLib_Init() == -1)
	{
		return false;
	}
	//�f�o�b�N�\���n�@������
	_dbgSetup(ScreenSizeX, ScreenSizeY, 255);			//255�͓����x	

	return true;
}
