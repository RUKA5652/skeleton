#pragma once
#include"Vector2.h"
#include"Collision.h"


class RayCast
{
public:
	struct Ray
	{
		Vector2Dbl point,vec;//�n�_�@�����x�N�g��
		Vector2Dbl end(){return point + vec; };
		double theta() { return atan2(vec.y, vec.x); };
	};
	struct Line
	{
		Vector2Dbl point, end;//�n�_�A�I�_
		Vector2Dbl vec(){ return end - point; };
		double theta() {return atan2(vec().y, vec().x); };
	};
	float InnerProduct(Vector2Dbl vec1, Vector2Dbl vec2);
	double ExteriorProduct(Vector2Dbl vec1, Vector2Dbl vec2);

	std::pair<Vector2Dbl, bool> CheckBoxCollison(Ray ray,Colison col);
	std::pair < Vector2Dbl, bool> CheckRay(Ray ray,Line line);


private:


};

