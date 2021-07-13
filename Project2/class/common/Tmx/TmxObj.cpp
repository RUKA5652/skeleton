#include "TmxObj.h"
#include "../ImageMneg.h"
#include<sstream>
#include"../../../_debug/_DebugConOut.h"
#include <algorithm>


TmxObj::TmxObj()
{
	virsion_["1.6.0"] = 1;
	//virsion_.emplace("1.6.0", 1);//��Ɠ��� ��������3��ށ@�����������

}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTSX(const std::string& fileName)
{
	//�t�@�C���̓ǂݍ���
	rapidxml::file<> xmlFileName(fileName.c_str()); //�f�[�^�̕ۑ��� //�����̃e���v���[�g�ɉ�������ĂȂ��̂̓f�t�H���g��char������
	tsxDoc_.parse<0>(xmlFileName.data()); //�f�[�^���i�[�i�ڂ��j
	//�m�[�h���擾
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");//�m�[�h��ݒ� first��next�̍l�����@
	//�`�F�b�N�o�[�W����
	if (!CheckTiledVersion(tileset))
	{
		return false;
	}
	/*��ԏ��߂̃m�[�h�����ł�����������o��
	auto node = tsxDoc_.first_node();
	while (node)//�m�[�h��null�ł����H
	{
		if (node->name_size())//���O���Ă�́H
		{
			TRACE("%s��",node->name());
		}
		auto attri = node->first_attribute();//��ԏ��߂̃A�g���r���[�g�����ł�����������o��

		while (attri)//�A�g���r���[�g��null�ł����H
		{
			if (attri->name_size())//���O���Ă�́H
			{
				TRACE("%s��", attri->name());
			}
			TRACE("%s��", attri->value());//�l�́H

			attri = attri->next_attribute();//���̃A�g���r���[�g���擾
		}
		auto chNode = node->first_node();
		TRACE("\n");
		node = node->next_sibling();//���̃m�[�h�� (�e����q�ɉ�����킯�ł͂Ȃ�)
	}*/
	//
	auto node = tsxDoc_.first_node();
	while (node)
	{
		if (node->name_size())
		{
			TRACE("%s", node->name());
		}
		auto atr = node->first_attribute();
		while (atr)
		{
			if (atr->name_size())
			{
				TRACE("->%s", atr->name());
			}
			TRACE("%s", atr->value());
			atr =	atr->next_attribute();
		}		
		node = node->next_sibling();
		TRACE("\n");
	} 
	//<image source = "mapChip.png" width = "208" height = "64" / >
	//<tileset version="1.5" tiledversion="1.6.0" name="mapChip" tilewidth="16" tileheight="16" tilecount="52" columns="13">
	auto imageNode = + tileset->first_node("image");
	std::string filename =  imageNode->first_attribute("source")->value();
	std::string key = filename.substr(filename.find_last_of("/") + 1);
	auto pass = fileName.substr(0,fileName.find_last_of("/")+1);//�p�X���𔲂��ăL�[�̐��� //�v��tsxDoc_.first_node("image")->first_attribute("name");
	auto divSize = Vector2{ atoi(tileset->first_attribute("tilewidth")->value()), atoi(tileset->first_attribute("tileheight")->value())};
	auto imageSize = Vector2{  atoi(imageNode->first_attribute("width")->value()) ,atoi(imageNode->first_attribute("height")->value()) };
	auto divCnt = imageSize / divSize;
	lpImageMneg.GetID(pass + filename, key, divSize, divCnt);


	return true;
}

bool TmxObj::LoadTMX(const std::string& fileName)
{
	//�t�@�C���̓ǂݍ���
	rapidxml::file<> xmlFileName(fileName.c_str()); //�f�[�^�̕ۑ��� //�����̃e���v���[�g�ɉ�������ĂȂ��̂̓f�t�H���g��char������
	tmxDoc_.parse<0>(xmlFileName.data()); //�f�[�^���i�[�i�ڂ��j
	//�m�[�h���擾
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");//�m�[�h��ݒ� first��next�̍l�����@
	//�`�F�b�N�o�[�W����
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}
	//TSX�f�[�^�̃��[�h
	auto tileset = mapNode->first_node("tileset");
	std::string pass = fileName.substr(0, fileName.find_last_of("/") + 1);
	if (! LoadTSX(pass + static_cast<std::string>(tileset->first_attribute("source")->value())))
	{
		return false;
	}
	//firstgid
	firstGID_ = atoi(tileset->first_attribute("firstgid")->value());
	//layerSize_
	layerSize_ = atoi(mapNode->first_attribute("nextlayerid")->value()) -1 ;
	//wordArea_
	wordArea_ = { atoi(mapNode->first_attribute("width")->value()), atoi(mapNode->first_attribute("height")->value()) };
	//tileSize_
	tileSize_ = { atoi(mapNode->first_attribute("tilewidth")->value()), atoi(mapNode->first_attribute("tileheight")->value()) };
	//�}�b�v�����i�[
	bool flag = SetMap();
	if (!flag)
	{
		return false;
	}
	flag = SetCol();
	//rapidxml::xml_node<>* layer = mapNode->first_node("layer");
	//while (layer)
	//{
	//	std::vector<int> mapData;
	//	mapData.reserve(static_cast<UINT64>(atoi(layer->first_attribute("width")->value())) * static_cast<UINT64>(atoi(layer->first_attribute("height")->value())));
	//	tmxMapData_.try_emplace(layer->first_attribute("name")->value(),std::move(mapData));
	//	layer = layer->next_sibling("layer");
	//}


	return flag;
}

bool TmxObj::SetMap(void)
{
	auto mapNode = tmxDoc_.first_node("map");
	//�`�F�b�N�o�[�W����
	if (!mapNode)
	{
		TRACE("map�m�[�h�擾�G���[");
		return false;
	}
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}

	rapidxml::xml_node<>* layerNode = mapNode->first_node("layer");
	if (!layerNode)
	{
		TRACE("layer�m�[�h�擾�G���[");
		return false;
	}
	//�e��layer�̃f�[�^���i�[
	while (layerNode)
	{
		auto layer = mapData_.try_emplace(layerNode->first_attribute("name")->value());//�C�e���[�^�[�Ɛ��������s��bool�������Ă���
		if (layer.second)//�������Ă���vec�z��̃T�C�Y�����������Ȃ��Ƃ����Ȃ�
		{
			layer.first->second.resize(/*static_cast<UINT64>*/(wordArea_.x) * /*static_cast<UINT64>*/(wordArea_.y));
		}
	//	TRACE("%s\n", layer.first->first.c_str());
		//csv�f�[�^��vec�Ɋi�[����
		auto layerData = layerNode->first_node("data")->first_node();
		std::stringstream dataStream;// = static_cast<std::stringstream>(layerData->value());//getline�̂��߂̃f�[�^�쐬
		dataStream << layerData->value();//�ڂ����`
		for (auto& data : layer.first->second)
		{
			std::string stringNum;
			getline(dataStream, stringNum, ',');
			data = atoi(stringNum.c_str());
	//		TRACE("%d,", atoi(stringNum.c_str()));
		}
	//	TRACE("\n");
		/*std::string stringLine;
		int cnt = 0;
		while (getline(dataStream, stringLine, ','))//�u,�v��؂育�ƂɃf�[�^���Ƃ肾��
		{
			//if (none_of(stringLine.begin(), stringLine.end(), isdigit))//������ɐ������Ȃ�������
			//{
			//	continue;
			//}
			layer.first->second[cnt] = atoi(stringLine.c_str());
			TRACE("%d,", layer.first->second[cnt]);
			cnt++;
		}
		TRACE("\n");*/
		
		/*std::string stringLine;
		int cnt = 0;
		while (getline(dataStream, stringLine))//��s�̃f�[�^�������Ă���
		{
			if (none_of(stringLine.begin(), stringLine.end(), isdigit))//������ɐ������Ȃ�������
			{
				continue;
			}
			// �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
			std::istringstream i_stream(stringLine);
			std::string stringConma;
			while (getline(i_stream, stringConma, ','))//�u,�v��؂育�ƂɃf�[�^���Ƃ肾��
			{
				if (none_of(stringConma.begin(), stringConma.end(), isdigit))//������ɐ������Ȃ�������
				{
					continue;
				}
				layer.first->second[cnt] = atoi(stringConma.c_str());
				TRACE("%d,", layer.first->second[cnt]);
				cnt++;
			}
			TRACE("\n");
		}*/
		layerNode = layerNode->next_sibling("layer");
	}
	return true;
}

bool TmxObj::SetCol(void)
{
	auto mapNode = tmxDoc_.first_node("map");
	//�`�F�b�N�o�[�W����
	if (!mapNode)
	{
		TRACE("map�m�[�h�擾�G���[");
		return false;
	}
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}

	rapidxml::xml_node<>* ColNode = mapNode->first_node("objectgroup");
	if (!ColNode)
	{
		TRACE("layer�m�[�h�擾�G���[");
		return false;
	}
	//�e��layer�̃f�[�^���i�[
	while (ColNode)
	{
		auto colItr = colData_.try_emplace(ColNode->first_attribute("name")->value());
		if (!colItr.second)
		{
			ColNode = ColNode->next_sibling("objectgroup");
			continue;
		}
		for(auto objNode = ColNode->first_node("object");objNode; objNode = objNode->next_sibling("object"))
		{
			Vector2 pos={ atoi(objNode->first_attribute("x")->value()) ,atoi(objNode->first_attribute("y")->value()) };
			Vector2 size={ atoi(objNode->first_attribute("width")->value()) ,atoi(objNode->first_attribute("height")->value()) };
			colItr.first->second.push_back(Colison{ pos, size });
		}
		ColNode = ColNode->next_sibling("objectgroup");
	}
	for (auto& colData : colData_)
	{
		for (auto& data : colData.second)
		{
			colList_.emplace_back(&data);
		}
	}
	return true;
}

const int TmxObj::GetMapData(const std::string& layer, Position2& pos)const
{
	Vector2 point = pos / tileSize_;
	return GetMapData(layer, point.x, point.y);//�W�����v�ŏ��������������������邪�f�o�b�O�̖ʂł͊y
}

const std::list<int> TmxObj::GetMapData(Position2& pos) const
{
		std::list<int> GetList;
		for (const auto& mapData: mapData_)
		{
			GetList.emplace_back(GetMapData(mapData.first, pos));
		}
		return GetList;
}

ColList& TmxObj::GetColData()
{
	return colList_;
}

std::list<Colison>& TmxObj::GetColData(std::string& key)
{
		return colData_.at(key);
}

const int TmxObj::GetMapData(const std::string& layer, int& x, int& y)const
{
	if (!mapData_.count(layer))
	{
		return 0;
	}
	x = std::clamp(x, 0, wordArea_.x -1);
	y = std::clamp(y, 0, wordArea_.y -1);
	int point = std::clamp(x + y * wordArea_.x, 0,static_cast<int>(mapData_.at(layer).size()));
	return mapData_.at(layer)[point];
}

bool TmxObj::CheckTiledVersion(const rapidxml::xml_node<>* node)
{
	if (!node)
	{
		TRACE("�m�[�h������܂���\n");
		return false;
	}
	auto tiledversion = node->first_attribute("tiledversion");//�A�g���r���[�g��ݒ�
	//�A�g���r���[�g�̒��g�����肽��
	auto data = tiledversion->value();//�A�g���r���[�g�̒��g�����o���l�����o��
	//���o�����f�[�^����
	if (!virsion_.count(/*static_cast<std::string>*/(data)))//���������o�[�W�������X�g�ɂȂ�
	{
		TRACE("Tiled��Ή��o�[�W�����ł�\n");
		return false;
	}
	if (!virsion_.at(/*static_cast<std::string>*/(data)))
	{
		TRACE("Tiled��Ή��o�[�W�����ł�\n");
		return false;
	}
	TRACE("Tiled�Ή��o�[�W�����ł�\n");
	return true;
}
