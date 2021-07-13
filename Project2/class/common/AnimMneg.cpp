#include "AnimMneg.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "Vector2.h"
#include "../../_debug/_DebugConOut.h"
#include<sstream>
#include "ImageMneg.h"
#include <DxLib.h>


AnimData_ AnimMneg::GetAnimData(const std::string& key, const std::string& state)
{
	return AnimData_{AnimationCount{0,0},animData_.at(key).at(state).second.begin(),state,key };
}

const std::string AnimMneg::LoadAnim(const std::string& imageNmae)
{
	rapidxml::file<> xmlFileName(imageNmae.c_str()); //データの保存先 //ここのテンプレートに何も入れてないのはデフォルトがcharだから
	rapidxml::xml_document<> actDoc_;
	actDoc_.parse<0>(xmlFileName.data()); //データを格納（移す）
	if (actDoc_.first_node("actionList")->first_attribute("version")->value() != std::string("1.0"))
	{
		TRACE("version違うよ\n");
		return nullptr;
	}
	//生成
	std::string name;
	name = actDoc_.first_node("actionList")->first_attribute("name")->value() ;
	if (!animData_.try_emplace(name).second)
	{
		return name;
	}
	//	auto imageNode = actDoc_.first_node("actionList")->first_node("image");
	for (auto imageNode = actDoc_.first_node("actionList")->first_node("image"); imageNode != nullptr; imageNode = imageNode->next_sibling())
	{	
		//whileは条件がばらばらになりやすくコードが分かりづらくなる
		Vector2 chipSize;
		chipSize.x = atoi(imageNode->first_attribute("divSizeX")->value());
		chipSize.y = atoi(imageNode->first_attribute("divSizeY")->value());
		Vector2 divCnt;
		divCnt.x = atoi(imageNode->first_attribute("divCntX")->value());
		divCnt.y = atoi(imageNode->first_attribute("divCntY")->value());
		//画像のロード
		std::string filename = imageNode->first_attribute("source")->value();
		std::string pass = imageNmae.substr(0, imageNmae.find_last_of("/") + 1);
		std::string key = imageNode->first_attribute("key")->value();
		lpImageMneg.GetID(pass + filename, name+key, chipSize, divCnt);
		//生成
		auto& animData = animData_[name].try_emplace(key).first->second;
		//loppcnt格納
		auto animeNode = imageNode->first_node("anime");
		auto loop = atoi(animeNode->first_attribute("loop")->value());
		animData.first = loop;
		//wait情報格納
		auto waitData = animeNode->first_node();
		std::stringstream dataStream;// = static_cast<std::stringstream>(layerData->value());//getlineのためのデータ作成
		dataStream << waitData->value();//移せるよ～
		std::string stringNum;
		while (getline(dataStream, stringNum, ',') )
		{
			auto id = atoi(stringNum.c_str());
			getline(dataStream, stringNum, ',');
			auto flame = atoi(stringNum.c_str());


			animData.second.emplace_back(AnimData{ AnimeData{ id,flame },ColData{ Vector2{}, Vector2{}}});
		}
		//コライダ情報
		auto colNode = imageNode->first_node("collider");
		rapidxml::xml_node<>* colData = (!colNode) ? nullptr: colNode->first_node();
		std::stringstream colDataStream;
		if (colData)
		{
			colDataStream << colData->value();//移せるよ～
		}
		std::string colStringNum;
		for (auto& data : animData.second)
		{
			Vector2 point = { 0,0 };
			Vector2 size = chipSize;
			if (getline(colDataStream, colStringNum, ','))
			{
				int pointX = atoi(colStringNum.c_str());
				getline(colDataStream, colStringNum, ',');
				int pointY = atoi(colStringNum.c_str());
				getline(colDataStream, colStringNum, ',');
				int endX = atoi(colStringNum.c_str());
				getline(colDataStream, colStringNum, ',');
				int endY = atoi(colStringNum.c_str());
				point = { pointX, pointY };
				size = { endX,endY };
			}
			data.second = ColData{ point,size };
		}


		/*for (int cnt = 0; cnt < divCnt.x * divCnt.y; cnt++)
		{
			AnimData data;
			std::string stringNum;
			getline(dataStream, stringNum, ',');
			data[0] = atoi(stringNum.c_str());
			stringNum.clear();
			getline(dataStream, stringNum, ',');
			data[1] = atoi(stringNum.c_str());
			animTbl_[name].second.emplace_back(data);
		}*/

		//イテレーターでやると
		/*
		//データ格納準備
		auto animData = animTbl_.try_emplace(imageNode->first_attribute("name")->value());
		if (!animData.second)
		{
			continue;
		}
		auto& animDataNode = animData.first->second;
		//loppcnt格納
		auto animeNode = imageNode->first_node("anime");
		auto loop = atoi(animeNode->first_attribute("loop")->value());
		animDataNode.first = loop;
		//wait情報格納
		auto waitData = animeNode->first_node();
		std::stringstream dataStream;// = static_cast<std::stringstream>(layerData->value());//getlineのためのデータ作成
		dataStream << waitData->value();//移せるよ～
		animDataNode.second.resize(divCnt.x * divCnt.y);
		for (auto& data : animDataNode.second)
		{
			std::string stringNum;
			getline(dataStream, stringNum, ',');
			data[0] = atoi(stringNum.c_str());
			stringNum.clear();
			getline(dataStream, stringNum, ',');
			data[1] = atoi(stringNum.c_str());
		}*/


	}
	//state_ = "walk";
	//animItr_ = animTbl_[state_].second.begin();
	//animCount_ = 0;
	//animLoopCnt_ = 0;
	return name;
}


AnimData_& AnimMneg::SetAnimState(AnimData_& animData,const std::string& state)
{
	animData.animCount_ = AnimationCount{ 0,0 };
	animData.state_ = state;
	animData.animItr_ = animData_.at(animData.objID).at(state).second.begin();
	return animData;
}


void AnimMneg::UpdateAnim( AnimData_& animData)
{
		auto& Counter = animData.animCount_;
		auto& animItr = animData.animItr_;
		auto& state = animData.state_;
		//アニメ―ション
		if (Counter[AnimCount]++ >= (*animItr).first.at(InvLimit))
		{
				if (++animItr == animData_.at(animData.objID).at(animData.state_).second.end())
				{
						if (animData_.at(animData.objID).at(animData.state_).first == -1 || ++Counter[AnimLoopCnt] < animData_.at(animData.objID).at(animData.state_).first)//ループ回数に到達してる？それとも無限かい？
						{
								animItr = animData_.at(animData.objID).at(animData.state_).second.begin();
						}
						else
						{
								animItr = --animData_.at(animData.objID).at(animData.state_).second.end();
						}
				}
				Counter[AnimCount] = 0;
		}
}

void AnimMneg::UpdateAnim(AnimData_& animData, const std::string& state )
{
	SetAnimState(animData, state);
	UpdateAnim(animData);
}

void AnimMneg::Draw(const AnimData_& animData, const Vector2Dbl& pos, bool tranFlag ,std::pair<int, int> Blend ) const
{
		SetDrawBlendMode(Blend.first, Blend.second);
		DrawRotaGraph2(pos.x, pos.y, 0, 0,1.0,0, lpImageMneg.GetID(animData.objID + animData.state_)[(*animData.animItr_).first[GraphHD]], true, tranFlag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}

void AnimMneg::DeletAnimData_(const std::string& key)
{
		animData_.erase(key);
}


AnimMneg::AnimMneg()
{
}

AnimMneg::~AnimMneg()
{
}
