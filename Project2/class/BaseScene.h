#pragma once
#include <memory>
#include "common/Vector2.h"

class BaseScene;
using uniqueScene = std::unique_ptr<BaseScene>;

enum class Scene
{
	Transiton,
	Title,
	Game,
	MAX,
};


class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual bool Init(void) = 0;
	virtual uniqueScene Update( const double& delta, uniqueScene ownScene) = 0;
	virtual void Draw(const double& delta) ;//�ŏI�`�� 
	virtual void DrawOwnScreen(const double& delta) = 0;//�����̃X�N���[���ɕ`��

	virtual Scene GetSceneID(void) = 0; //�ϐ��ɓ���ĕԂ��d�g�݂��Ə�������Y�ꂽ���ƂɋC�t���Â炢�̂ŏ������z�Ń~�X�����Ƃ��ɐ�΂ɓ{���Ă����悤�ɂ��Ƃ�

private:

protected:
	int screenID_;
	Vector2 screenSize_;

	int oldKey;
};

