#include "RayCast.h"
#include <DxLib.h>
#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"


float RayCast::InnerProduct(Vector2Dbl vec1, Vector2Dbl vec2)
{
		return vec1.x * vec2.x + vec1.y * vec2.y;
}

double RayCast::ExteriorProduct(Vector2Dbl vec1, Vector2Dbl vec2)
{
	return  vec1.x * vec2.y - vec1.y * vec2.x;
}



std::pair<Vector2Dbl, bool> RayCast::CheckBoxCollison(Ray ray, Colison col)
{
		Line line[4]{
				{ {col.first.cast<double>()}, Vector2{col.first.x,col.first.y + col.second.y}.cast<double>() },
				{Vector2{col.first.x + col.second.x,col.first.y }.cast<double>(),  Vector2{col.first.x + col.second.x,col.first.y + col.second.y }.cast<double>()},
				{ col.first.cast<double>() , Vector2{col.first.x + col.second.x,col.first.y  }.cast<double>() },
				{ Vector2{col.first.x,col.first.y + col.second.y}.cast<double>(), Vector2{col.first.x + col.second.x ,col.first.y + col.second.y}.cast<double>() }
		};
		Vector2Dbl moveVec = ray.vec;
		bool flag = false;
		for (auto& lin : line)
		{
				auto result = CheckRay(ray, lin);
				moveVec = result.second ? result.first: moveVec;
				flag |= result.second;
		}
	// bool flag = CheckRay(ray, { col.first, {col.first.x,col.first.y + col.second.y} }).second||//左
	//CheckRay(ray, { {col.first.x + col.second.x,col.first.y },  {col.first.x + col.second.x,col.first.y + col.second.y } }).second||//右
	//CheckRay(ray, { col.first , {col.first.x + col.second.x,col.first.y  } }).second||//上
	//CheckRay(ray, { {col.first.x,col.first.y + col.second.y}, col.first + col.second }).second;//下

	return  std::pair<Vector2Dbl, bool>{moveVec, flag};
}

std::pair<Vector2Dbl, bool> RayCast::CheckRay(Ray ray, Line line)
{
	//エンジンに投げる
	//auto Vec1_pos1 = DxLib::VECTOR{(float)ray.point.x,(float)ray.point.y,0 };
	//auto Vec1_pos2 = DxLib::VECTOR{ (float)ray.end().x,(float)ray.end().y,0};
	//auto Vec2_pos1 = DxLib::VECTOR{ (float)line.point.x,(float)line.point.y,0 };
	//auto Vec2_pos2 = DxLib::VECTOR{ (float)line.end.x,(float)line.end.y,0 };
	//auto result = SEGMENT_SEGMENT_RESULT{};
	//DxLib::Segment_Segment_Analyse(&Vec1_pos1, &Vec1_pos2, &Vec2_pos1, &Vec2_pos2, &result);
	//bool flag = (result.SegA_MinDist_Pos.x == result.SegB_MinDist_Pos.x &&
	//	result.SegA_MinDist_Pos.y == result.SegB_MinDist_Pos.y);
	//return std::pair<Vector2, bool>{(flag ? Vector2{ (int)result.SegA_MinDist_Pos.x ,(int)result.SegA_MinDist_Pos.y } : ray.end()), flag};
	//---
	_dbgDrawLine(line.point.x,line.point.y,line.end.x,line.end.y,0xff0000);

	
	//授業版
	bool flag = false;
	Vector2Dbl vecRay = ray.vec,vecLine = line.vec();
	double clossRayLine = ExteriorProduct(vecRay, vecLine);
	if (clossRayLine == 0)
	{
			return std::pair<Vector2Dbl, bool>{ray.vec, flag};
	}
	Vector2Dbl v{ line.point.x - ray.point.x,line.point.y - ray.point.y };
	auto cross_vRay = ExteriorProduct(v, vecRay);	auto cross_vLine = ExteriorProduct(v, vecLine);
	double ans1 = cross_vRay / clossRayLine,ans2 = cross_vLine/ clossRayLine;
	flag = (ans1 > 0.0f && ans1 <= 1.0f && ans2 > 0.0f && ans2 <= 1.0f);
	Vector2Dbl move = flag ? Vector2Dbl{vecRay*ans2 } : Vector2Dbl{ ray.vec};
	//_dbgDrawLine(ray.point.x, ray.point.y, ray.point.x + move.x, ray.point.y + move.y, 0xffffff);
	_dbgDrawCircle(ray.point.x + move.x, ray.point.y + move.y, 6, 0xffffff, true);
	
	return std::pair<Vector2Dbl, bool>{move, flag};
	//---
	

	/*
	//自作
	//交わってるか？
	Vector2 AB = ray.vec, AC{ line.point - ray.point }, AD{line.end-ray.point},
		CD{ line.vec() }, CA{ ray.point - line.point }, CB{ray.end()-line.point};
	auto check = [&](Vector2& vec1, Vector2& vec2, Vector2& vec3) {
		return (ExteriorProduct(vec1, vec2) * ExteriorProduct(vec1, vec3) < 0.0f); };
	bool flag = check(AB, AC, AD) && check(CD, CA, CB);

	if (flag)
	{
		Vector2 dotVec{ ray.point + AB.Normalized() * (int)ExteriorProduct(AB.Normalized(), AC) };
		_dbgDrawCircle(dotVec.x, dotVec.y,5,0x00ff00,true);
		return std::pair<Vector2, bool>{dotVec, flag};
	}
	else
	{
		return std::pair<Vector2, bool>{ray.end(), flag};
	}

	return std::pair<Vector2, bool>{ray.end(), flag};
	//---
	*/
}
