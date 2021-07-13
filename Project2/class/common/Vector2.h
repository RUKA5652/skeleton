#pragma once

//using Vector2 = Vector2Tmple<int>;



//テンプレートクラス
template <class T = int> class Vector2Tmple //決まり文句　template <class T> class
{
public:



	Vector2Tmple();
	Vector2Tmple(T x, T y);
	~Vector2Tmple();
	T x;
	T y;


	//2項演算子
	Vector2Tmple operator+(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple operator+(const Vector2Tmple<F> num);

	Vector2Tmple operator-(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple operator-(const F num);

	Vector2Tmple operator*(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple operator*(const Vector2Tmple<F> num);
	template<class F>
	Vector2Tmple operator*(const F num);

	Vector2Tmple operator/(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple operator/(const Vector2Tmple<F> num);
	template<class F>
	Vector2Tmple operator/(const F num);

	Vector2Tmple operator%(const Vector2Tmple& num);

	//代入演算子
	Vector2Tmple& operator=(const Vector2Tmple& num);		//代入だから参照渡しでもおｋ
	template<class F>
	Vector2Tmple<T> operator=(const Vector2Tmple<F>& num);
	//添え字演算子
	int& operator[](const int& cnt);

	//単項演算子
	Vector2Tmple& operator+=(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple& operator+=(const Vector2Tmple<F>& num);
	template<class F>
	Vector2Tmple& operator+=(const F& num);
	Vector2Tmple& operator-=(const Vector2Tmple& num);
	template<class F>
	Vector2Tmple& operator-=(const F& num);
	Vector2Tmple& operator*=(const Vector2Tmple& num);

	Vector2Tmple& operator/=(const Vector2Tmple& num);

	Vector2Tmple& operator%=(const Vector2Tmple& num);

	Vector2Tmple operator+()const; //おしりのconst は関数内でのthisのメンバーの変更を縛る 

	Vector2Tmple operator-()const;
	//cast
	template<class F>
	Vector2Tmple<F> cast(void) const;

	//比較演算子
	bool operator<(const Vector2Tmple& num)const;
	bool operator<=(const Vector2Tmple& num)const;
	bool operator>(const Vector2Tmple& num)const;
	bool operator>=(const Vector2Tmple& num)const;
	bool operator==(const Vector2Tmple& num)const;
	bool operator!=(const Vector2Tmple& num)const;


	//ベクトルの大きさを返す
	float Magnitude()const;//この中では値の変更をしないよ
	//ベクトルの2乗を返す
	float SQ_Magnitude()const;
	//正規化する
	void Normalize(); 
	Vector2Tmple Normalized();
	//角度を返す
	float Theta();
	//90度回転
	void Rotate90();


private:
};

template<class T> //宣言外なので再度宣言して教えてあげないといけない
Vector2Tmple<T> operator*(const Vector2Tmple<T>& me, const  T& num);
template<class T> 
Vector2Tmple<T> operator/(const Vector2Tmple<T>& me, const  T& num);
template<class T>
Vector2Tmple<T> operator*(const T& num, const Vector2Tmple<T>& me);




using Vector2Flt = Vector2Tmple<float>;

using Vector2Dbl = Vector2Tmple<double>;

using Vector2 = Vector2Tmple<int>;

using Position2 = Vector2Tmple<int>;

#include"detail/Vector2.h"

