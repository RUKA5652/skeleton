#include "ImageMneg.h"
#include<DxLib.h>
#include "../../_debug/_DebugConOut.h"


const VecInt& ImageMneg::GetID(const std::string& key)
{
	//if (imageMap_.find(key) == imageMap_.end())
	if (!imageMap_.count(key))
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(key.c_str());
	}
	return	imageMap_[key];

}

const VecInt& ImageMneg::GetID(const std::string& f_name, const std::string& key)
{
	//if (imageMap_.find(key) == imageMap_.end())
	if (!imageMap_.count(key))
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());
	}
	return	imageMap_[key];
}

const VecInt& ImageMneg::GetID(const std::string& f_name, const std::string& key, const Vector2&& divSize, const Vector2&& divCnt)
{
	return GetID(f_name, key,divSize, divCnt);
}

const bool ImageMneg::DeritID(const std::string& key)
{
	if (imageMap_.count(key))
	{
		auto flag = false;
		for (auto image : imageMap_.at(key))
		{
			if (DeleteGraph(image))
			{
				flag = true;
			}
		}
		return flag;
	}
	return false;
}

const VecInt& ImageMneg::GetID(const std::string& f_name, const std::string& key, const Vector2& divSize, const Vector2& divCnt)
{
	//if (imageMap_.find(key) == imageMap_.end())		//最後まで行くとendがくる
	if(!imageMap_.count(key))
	{
		TRACE("ファイル読み込み\n");
		imageMap_[key].resize(static_cast<UINT64>(divCnt.x) * static_cast<UINT64>(divCnt.y));

		LoadDivGraph(f_name.c_str()/*変換*/, divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0], true);
	
	}
	return	imageMap_[key];
}




ImageMneg::ImageMneg()
{

}

ImageMneg::~ImageMneg()
{

}
