#pragma once
#include<vector>
#include<string>
#include"Vector2.h"
#include <map>

#define lpImageMneg  ImageMneg::GetInstance()

using VecInt = std::vector<int>;

class ImageMneg
{
public:
	static  ImageMneg& GetInstance(void)
	{
		static ImageMneg s_Instance;
		return s_Instance;
	}
	const VecInt& GetID(const std::string& key /*ファイル名*/); //グラフィックハンドルを返す
	const VecInt& GetID(const std::string& f_name, const std::string& key /*ファイル名*/); //グラフィックハンドルを返す
	const VecInt& GetID(const std::string& f_name , const std::string& key /*ファイル名*/, const Vector2& divSize, const Vector2& divCnt);//グラフィックハンドルを返す 分割されてる場合もあるので
	const VecInt& GetID(const std::string& f_name, const std::string& key /*ファイル名*/, const Vector2&& divSize, const Vector2&& divCnt);
	const bool DeritID(const std::string& key /*ファイル名*/); //グラフィックハンドルを消す
private:
	ImageMneg();
	~ImageMneg();
	std::map<std::string, VecInt> imageMap_;
};

