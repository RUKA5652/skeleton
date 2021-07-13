#include "TmxObj.h"
#include "../ImageMneg.h"
#include<sstream>
#include"../../../_debug/_DebugConOut.h"
#include <algorithm>


TmxObj::TmxObj()
{
	virsion_["1.6.0"] = 1;
	//virsion_.emplace("1.6.0", 1);//上と同じ ざっくり3種類　入れ方がある

}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTSX(const std::string& fileName)
{
	//ファイルの読み込み
	rapidxml::file<> xmlFileName(fileName.c_str()); //データの保存先 //ここのテンプレートに何も入れてないのはデフォルトがcharだから
	tsxDoc_.parse<0>(xmlFileName.data()); //データを格納（移す）
	//ノードを取得
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");//ノードを設定 firstとnextの考え方　
	//チェックバージョン
	if (!CheckTiledVersion(tileset))
	{
		return false;
	}
	/*一番初めのノードを何でもいいから取り出す
	auto node = tsxDoc_.first_node();
	while (node)//ノードがnullですか？
	{
		if (node->name_size())//名前ついてるの？
		{
			TRACE("%s→",node->name());
		}
		auto attri = node->first_attribute();//一番初めのアトリビュートを何でもいいから取り出す

		while (attri)//アトリビュートはnullですか？
		{
			if (attri->name_size())//名前ついてるの？
			{
				TRACE("%s→", attri->name());
			}
			TRACE("%s→", attri->value());//値は？

			attri = attri->next_attribute();//次のアトリビュートを取得
		}
		auto chNode = node->first_node();
		TRACE("\n");
		node = node->next_sibling();//次のノードへ (親から子に下りれるわけではない)
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
	auto pass = fileName.substr(0,fileName.find_last_of("/")+1);//パス情報を抜いてキーの生成 //没案tsxDoc_.first_node("image")->first_attribute("name");
	auto divSize = Vector2{ atoi(tileset->first_attribute("tilewidth")->value()), atoi(tileset->first_attribute("tileheight")->value())};
	auto imageSize = Vector2{  atoi(imageNode->first_attribute("width")->value()) ,atoi(imageNode->first_attribute("height")->value()) };
	auto divCnt = imageSize / divSize;
	lpImageMneg.GetID(pass + filename, key, divSize, divCnt);


	return true;
}

bool TmxObj::LoadTMX(const std::string& fileName)
{
	//ファイルの読み込み
	rapidxml::file<> xmlFileName(fileName.c_str()); //データの保存先 //ここのテンプレートに何も入れてないのはデフォルトがcharだから
	tmxDoc_.parse<0>(xmlFileName.data()); //データを格納（移す）
	//ノードを取得
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");//ノードを設定 firstとnextの考え方　
	//チェックバージョン
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}
	//TSXデータのロード
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
	//マップ情報を格納
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
	//チェックバージョン
	if (!mapNode)
	{
		TRACE("mapノード取得エラー");
		return false;
	}
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}

	rapidxml::xml_node<>* layerNode = mapNode->first_node("layer");
	if (!layerNode)
	{
		TRACE("layerノード取得エラー");
		return false;
	}
	//各種layerのデータを格納
	while (layerNode)
	{
		auto layer = mapData_.try_emplace(layerNode->first_attribute("name")->value());//イテレーターと成功か失敗のboolが入っている
		if (layer.second)//成功してたらvec配列のサイズを初期化しないといけない
		{
			layer.first->second.resize(/*static_cast<UINT64>*/(wordArea_.x) * /*static_cast<UINT64>*/(wordArea_.y));
		}
	//	TRACE("%s\n", layer.first->first.c_str());
		//csvデータをvecに格納する
		auto layerData = layerNode->first_node("data")->first_node();
		std::stringstream dataStream;// = static_cast<std::stringstream>(layerData->value());//getlineのためのデータ作成
		dataStream << layerData->value();//移せるよ～
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
		while (getline(dataStream, stringLine, ','))//「,」区切りごとにデータをとりだす
		{
			//if (none_of(stringLine.begin(), stringLine.end(), isdigit))//文字列に数字がなかったら
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
		while (getline(dataStream, stringLine))//一行のデータを持ってくる
		{
			if (none_of(stringLine.begin(), stringLine.end(), isdigit))//文字列に数字がなかったら
			{
				continue;
			}
			// 「,」区切りごとにデータを読み込むためにistringstream型にする
			std::istringstream i_stream(stringLine);
			std::string stringConma;
			while (getline(i_stream, stringConma, ','))//「,」区切りごとにデータをとりだす
			{
				if (none_of(stringConma.begin(), stringConma.end(), isdigit))//文字列に数字がなかったら
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
	//チェックバージョン
	if (!mapNode)
	{
		TRACE("mapノード取得エラー");
		return false;
	}
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}

	rapidxml::xml_node<>* ColNode = mapNode->first_node("objectgroup");
	if (!ColNode)
	{
		TRACE("layerノード取得エラー");
		return false;
	}
	//各種layerのデータを格納
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
	return GetMapData(layer, point.x, point.y);//ジャンプで処理効率がすこし下がるがデバッグの面では楽
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
		TRACE("ノードがありません\n");
		return false;
	}
	auto tiledversion = node->first_attribute("tiledversion");//アトリビュートを設定
	//アトリビュートの中身をしりたい
	auto data = tiledversion->value();//アトリビュートの中身を取り出し値を取り出す
	//取り出したデータから
	if (!virsion_.count(/*static_cast<std::string>*/(data)))//そもそもバージョンリストにない
	{
		TRACE("Tiled非対応バージョンです\n");
		return false;
	}
	if (!virsion_.at(/*static_cast<std::string>*/(data)))
	{
		TRACE("Tiled非対応バージョンです\n");
		return false;
	}
	TRACE("Tiled対応バージョンです\n");
	return true;
}
