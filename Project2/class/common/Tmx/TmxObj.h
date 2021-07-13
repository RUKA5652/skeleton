#pragma once
#include"../rapidxml/rapidxml.hpp"
#include"../rapidxml/rapidxml_utils.hpp"
#include <map>
#include<string>
#include<vector>
#include"../Vector2.h"
#include <list>
#include"../Collision.h"

using MapData = std::map<std::string, std::vector<int>>;


class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	bool LoadTSX(const std::string& fileName); //tsxをロードする
	bool LoadTMX(const std::string& fileName); //tmxをロードする
	bool SetMap(void);
	bool SetCol(void);
	const unsigned int GetFirstGID(void) const { return firstGID_; };
	const unsigned int GetLayerSize(void) const  { return layerSize_; };
	const Vector2& GetWordArea(void) const  { return wordArea_; };
	const Vector2& GetTileSize(void) const  { return tileSize_; };
	const MapData& GetMapData(void) const  { return mapData_;};
	const int GetMapData(const std::string& layer, Position2& pos) const;//posは座標
	const std::list<int> GetMapData(Position2& pos) const;
	ColList& GetColData();
	std::list<Colison>& GetColData(std::string& key);
	const int GetMapData(const std::string &layer, int& x,int& y) const;

private:
	std::map<std::string, int> virsion_;	//対応バージョンを格納する

	//tsx
	rapidxml::xml_document<> tsxDoc_; //tsxのドキュメントデータ保
	//tmx
	rapidxml::xml_document<> tmxDoc_;	
	unsigned int firstGID_;
	unsigned int layerSize_;
	Vector2 wordArea_;
	Vector2 tileSize_;
	MapData  mapData_;//mapData
	//コリジョン
	std::map<std::string, std::list<Colison>> colData_;
	ColList colList_;
	//checkタイルドバージョン
	bool CheckTiledVersion(const rapidxml::xml_node<>* node);

};

