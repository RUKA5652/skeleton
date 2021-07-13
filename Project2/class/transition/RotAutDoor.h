#pragma once
#include "TransitionScene.h"
#include "../common/Vector2.h"

constexpr int NUM = 2;


class RotAutDoor :
	public TransitionScene
{
public:
	RotAutDoor(uniqueScene beforScene, uniqueScene nextScene, Vector2 pos);
	~RotAutDoor(); 
private:

	bool UpdateTransition(const double& delta) override;


	void DrawOwnScreen(const double& delta) override;

	void Init_(void);

	int beforScreen;

	int Screen_[NUM];

	double count_;


	double n_ = 3.14;
};

