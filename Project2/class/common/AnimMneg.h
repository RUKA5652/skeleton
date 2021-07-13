#pragma once
#include <map>
#include <string>
#include <list>
#include<array>
#include"Vector2.h"

#define lpAnimMneg  AnimMneg::GetInstance()
using ColData = std::pair<Position2, Vector2>;
using AnimeData = std::array<int, 2>;
using AnimData = std::pair<AnimeData, ColData>;
using AnimNode = std::pair<int, std::list<AnimData>>;
using AnimationCount = std::array<int, 2>;
constexpr int  GraphHD = 0;
constexpr int  InvLimit = 1;
constexpr int  AnimCount = 0;
constexpr int  AnimLoopCnt = 1;

struct AnimData_
{
		AnimationCount animCount_;
		std::list<AnimData>::iterator animItr_;
		std::string state_;
		std::string objID;
};

class AnimMneg
{
public:
	static  AnimMneg& GetInstance(void)
	{
		static AnimMneg s_Instance;
		return s_Instance;
	}
	AnimData_ GetAnimData(const std::string& key,const std::string& state);
	const std::string LoadAnim(const std::string& imageNmae);
	AnimData_& SetAnimState(AnimData_& animData,const std::string& state);//	randomアクセスできないからitrの場所を知りたい
	void UpdateAnim(AnimData_& animData);
	void UpdateAnim(AnimData_& animData, const std::string& state);
	void	Draw(const AnimData_& animData, const Vector2Dbl& pos, bool turnFlag = false,std::pair<int, int> Blend = { 0,0 }) const;
	void DeletAnimData_(const std::string& key);
private:
	AnimMneg();
	~AnimMneg();
	AnimMneg(const AnimMneg&) = delete;
	void operator=(const AnimMneg&) = delete;

	std::map<std::string, std::map<std::string, AnimNode>> animData_;
	//std::map < std::string, AnimationCount> animCount_;
	//std::map<std::string, std::list<AnimData>::iterator > animItr_;

	//int animCount_;
	//int animLoopCnt_;

};