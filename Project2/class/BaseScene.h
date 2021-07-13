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
	virtual void Draw(const double& delta) ;//最終描画 
	virtual void DrawOwnScreen(const double& delta) = 0;//自分のスクリーンに描画

	virtual Scene GetSceneID(void) = 0; //変数に入れて返す仕組みだと初期化を忘れたことに気付きづらいので純粋仮想でミスしたときに絶対に怒ってくれるようにしとく

private:

protected:
	int screenID_;
	Vector2 screenSize_;

	int oldKey;
};

