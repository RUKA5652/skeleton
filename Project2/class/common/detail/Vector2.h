#pragma once
#include"../Vector2.h"
#include<algorithm>

template<class T>
Vector2Tmple<T>::Vector2Tmple()
{
		x = 0;
		y = 0;
}

template<class T>
Vector2Tmple<T>::Vector2Tmple(T x, T y) /*:x(x),y(y)�@���Ȃ����ǂ���ł���*/
{
		Vector2Tmple::x = x;
		Vector2Tmple::y = y;
	//-------����ł��s�����------------
	/*this->x = x;
	this->y = y;*/
	//------------------
}

template<class T>
Vector2Tmple<T>::~Vector2Tmple()
{

}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator+(const Vector2Tmple<T>& num)
{
		return  {this->x + num.x, this->y + num.y };
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator-(const  Vector2Tmple<T>& num)
{
		return { this->x - num.x, this->y - num.y };
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator*(const  Vector2Tmple<T>& num)
{
		return { this->x * num.x, this->y * num.y };
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator/(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}


		return { this->x / num.x, this->y / num.y };
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator%(const  Vector2Tmple<T>& num)
{

		//if (num.x == 0)
		//{
		//		this->x = 0;
		//}
	
		//if (num.y == 0)
		//{
		//		this->y = 0;
		//}
	

		return { this->x % num.x, this->y % num.y };
}

template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator=(const  Vector2Tmple<T>& num)
{
		this->x = num.x;
		this->y = num.y;

		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
int& Vector2Tmple<T>::operator[](const int& cnt)
{
		switch (cnt)
		{
		//case 0:
		//		return x;
				//break;
		case 1:
				return y;
				//break;
		default:
				return x;
				//break;
		}
}

template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const  Vector2Tmple<T>& num)
{
		this->x += num.x;
		this->y += num.y;
		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}
template<class T>
template<class F>
Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const  Vector2Tmple<F>& num)
{
	auto num_ = num.cast<T>();
	this->x += num_.x;
	this->y += num_.y;
	return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
template<class F>
Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const F& num)
{
	auto num_ = static_cast<F>(num);
	this->x += num_;
	this->y += num_;
	return *this;
}

template<class T>
template<class F>
Vector2Tmple<T>& Vector2Tmple<T>::operator-=(const F& num)
{
	auto num_ = static_cast<F>(num);
	this->x -= num_;
	this->y -= num_;
	return *this;
}


template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator-=(const  Vector2Tmple<T>& num)
{
		this->x -= num.x;
		this->y -= num.y;
		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator*=(const  Vector2Tmple<T>& num)
{
		this->x *= num.x;
		this->y *= num.y;
		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator/=(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}
		else
		{
				this->x /= num.x;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}
		else
		{
				this->y /= num.y;
		}
		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
Vector2Tmple<T>& Vector2Tmple<T>::operator%=(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}
		else
		{
				this->x %= num.x;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}
		else
		{
				this->y %= num.y;
		}
		return   *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator+() const
{
		return  *this; //this�̓|�C���^�[����@���̂œn���������*�����悤
}

template<class T>
Vector2Tmple<T> Vector2Tmple<T>::operator-() const
{
		return { -this->x,-this->y };
}

template<class T>
bool Vector2Tmple<T>::operator<(const  Vector2Tmple<T>& num)const
{
//		if (!this->x < num.x)
//		{
//				return false;
//		}
//		if (!this->y < num.y)
//		{
//				return false;
//		}
//		return true;

		return (this->x < num.x && this->y < num.y);
}

template<class T>
bool Vector2Tmple<T>::operator<=(const  Vector2Tmple<T>& num) const
{
		//if (!this->x <= num.x)
		//{
		//		return false;
		//}
		//if (!this->y <= num.y)
		//{
		//		return false;
		//}
		//return true;
		return (this->x <= num.x && this->y <= num.y);
}

template<class T>
bool Vector2Tmple<T>::operator>(const  Vector2Tmple<T>& num)const
{
	/*	if (!this->x > num.x)
		{
				return false;
		}
		if (!this->y > num.y)
		{
				return false;
		}
		return true;*/
		return (this->x > num.x && this->y > num.y);
}

template<class T>
bool Vector2Tmple<T>::operator>=(const  Vector2Tmple<T>& num)const
{
		//if (!this->x >= num.x)
		//{
		//		return false;
		//}
		//if (!this->y >= num.y)
		//{
		//		return false;
		//}
		//return true;
		return (this->x >= num.x && this->y >= num.y);
}

template<class T>
bool Vector2Tmple<T>::operator==(const  Vector2Tmple<T>& num)const
{
	/*	if (!this->x == num.x)
		{
				return false;
		}
		if (!this->y == num.y)
		{
				return false;
		}
		return true;*/

		return (this->x == num.x && this->y == num.y);
}

template<class T>
bool Vector2Tmple<T>::operator!=(const  Vector2Tmple<T>& num) const
{
		//if (!this->x != num.x)
		//{
		//		return false;
		//}
		//if (!this->y != num.y)
		//{
		//		return false;
		//}
		//return true;
		return !(this->x == num.x && this->y == num.y);;

}

template<class T>
float Vector2Tmple<T>::Magnitude() const
{
	return hypot(x, y);
}

template<class T>
float Vector2Tmple<T>::SQ_Magnitude() const
{
	return	x * x + y * y;
}

template<class T>
void Vector2Tmple<T>::Normalize()
{
	auto mag = Magnitude();
	if (mag == 0.0f) { return;};
	x = x / mag;
	y = y / mag;
}

template<class T>
 Vector2Tmple<T> Vector2Tmple<T>::Normalized()
{
		 Vector2Tmple<T> vec = (*this);
		 vec.Normalize();
		 return vec;
}

template<class T>
inline float Vector2Tmple<T>::Theta()
{
	return atan2(this.y, this.x); 
}




template<class T>
void Vector2Tmple<T>::Rotate90()
{
	swap(x, y);
	x = -x;
}

template<class T>
Vector2Tmple<T> operator*(const  Vector2Tmple<T>& me, const T& num)
{
		return { (me.x * num),(me.y * num) };
}

template<class T>
Vector2Tmple<T> operator/(const  Vector2Tmple<T>& me, const T& num)
{
	return { (me.x / num),(me.y / num) };
}



template<class T>
Vector2Tmple<T> operator*(const T& num, const  Vector2Tmple<T>& me)
{
		return { (me.x * num),(me.y * num) };
}




template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator+(const Vector2Tmple<F> num)
{
	return   { this->x +static_cast<T>(num.x), this->y +static_cast<T>(num.y) };
}
template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator-(const F num)
{
	return  { this->x - static_cast<T>(num), this->y - static_cast<T>(num) };
}
template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator*(const Vector2Tmple<F> num)
{
	return    { this->x * static_cast<T>(num.x), this->y * static_cast<T>(num.y) };
}
template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator*(const F num)
{
	return  { this->x * static_cast<T>(num), this->y * static_cast<T>(num) };
}
template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator/(const Vector2Tmple<F> num)
{
	return   { this->x / static_cast<T>(num.x), this->y / static_cast<T>(num.y) };
}

template<class T>
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator/(const F num)
{
	return   { this->x / static_cast<T>(num), this->y / static_cast<T>(num) };
}

template<class T>
template<class F>
Vector2Tmple<T> Vector2Tmple<T>::operator=(const Vector2Tmple<F>& num)
{
	return   { this->x = static_cast<T>(num.x), this->y = static_cast<T>(num.y) };
}

template<class T>
template<class F>
Vector2Tmple<F> Vector2Tmple<T>::cast(void) const
{
	return Vector2Tmple<F>{static_cast<F>(x), static_cast<F>(y) };
}

