#include<DxLib.h>	//""�_�u���R�[�e�[�V�����̓v���W�F�N�g�̏ꏊ���猩��@��Ɏ���������������w�b�_�@<>�̓p�X���o�^����Ă�z��������@��ɊO�����C�u����
//�C���N���[�h�̎d���ŃR���p�C���ɂ����鎞�Ԃ��ς��
#include"class/SceneMneg.h"
//#include"_debug/_DebugConOut.h"
//#include"_debug/_DebugDispOut.h"
//#include"class/TitleScene.h"//filter�̏ꏊ���猩�Ă��`
//#include<chrono> //���Ԏ���


//constexpr int ScreenSizeX = 1024;
//constexpr int ScreenSizeY = 768;



//bool SysInit(void)
//{
//	SetWindowText("�A�N�V�����Q�[��_2016016_�����@����");		//������̏ꍇ""���ꂪ���� �ۑ�2_�w�Дԍ�_���O		�R�s�y��h������	�E�B���h�E�̖��O
//	//-----�V�X�e������-----
//	//�E�B���h�E�T�C�Y�ݒ�
//	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);		//scnArea_.x�~scnArea_.y�h�b�g65536�F���[�h�ɐݒ�@16bit=65536
//	//�E�B���h�E���[�h�Œ�
//	ChangeWindowMode(true);
//	//DxLib����
//	if (DxLib_Init() == -1)
//	{
//		return false;
//	}
//	//�f�o�b�N�\���n�@������
//	_dbgSetup(ScreenSizeX, ScreenSizeY, 255);			//255�͓����x	
//
//	return true;
//}






int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�G���g���[�|�C���g 
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
	//while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))	//ProcessMessage() == 0 �ŃE�B���h�E�����񂾂Ƃ���while�̊O�ɏo��
	//{
	//	_dbgStartDraw();
	//	auto timeEnd = timeStart;
	//	auto timeStart = std::chrono::system_clock::now();
	//	//---�t���[���̌o�ߎ��Ԍv�Z
	//	auto delta = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(timeStart - timeEnd).count());
	//	delta = (delta <= 0 ? delta = 0 : delta / (1000000.0));//double�Ȃ�.0��float�Ȃ�.0f��
	//	//--�X�V����---
	//	scene->Update(delta);
	//	


	//	//-----------�`��----------------
	//	//SetDrawScreen(DX_SCREEN_BACK);
	//	ClearDrawScreen();
	//	scene->Draw(delta);
	//	_dbgAddDraw();
	//	ScreenFlip();

	//}

	//if (ProcessMessage() == 0)//�E�B���h�E������ۂɉ����A�N�V�������N����
	//{

	//}
	return 1;
}

