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
	const VecInt& GetID(const std::string& key /*�t�@�C����*/); //�O���t�B�b�N�n���h����Ԃ�
	const VecInt& GetID(const std::string& f_name, const std::string& key /*�t�@�C����*/); //�O���t�B�b�N�n���h����Ԃ�
	const VecInt& GetID(const std::string& f_name , const std::string& key /*�t�@�C����*/, const Vector2& divSize, const Vector2& divCnt);//�O���t�B�b�N�n���h����Ԃ� ��������Ă�ꍇ������̂�
	const VecInt& GetID(const std::string& f_name, const std::string& key /*�t�@�C����*/, const Vector2&& divSize, const Vector2&& divCnt);
	const bool DeritID(const std::string& key /*�t�@�C����*/); //�O���t�B�b�N�n���h��������
private:
	ImageMneg();
	~ImageMneg();
	std::map<std::string, VecInt> imageMap_;
};

