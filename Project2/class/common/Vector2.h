#pragma once

//using Vector2 = Vector2Tmple<int>;



//�e���v���[�g�N���X
template <class T = int> class Vector2Tmple //���܂蕶��@template <class T> class
{
public:



	Vector2Tmple();
	Vector2Tmple(T x, T y);
	~Vector2Tmple();
	T x;
	T y;


	//2�����Z�q
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

	//������Z�q
	Vector2Tmple& operator=(const Vector2Tmple& num);		//���������Q�Ɠn���ł�����
	template<class F>
	Vector2Tmple<T> operator=(const Vector2Tmple<F>& num);
	//�Y�������Z�q
	int& operator[](const int& cnt);

	//�P�����Z�q
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

	Vector2Tmple operator+()const; //�������const �͊֐����ł�this�̃����o�[�̕ύX�𔛂� 

	Vector2Tmple operator-()const;
	//cast
	template<class F>
	Vector2Tmple<F> cast(void) const;

	//��r���Z�q
	bool operator<(const Vector2Tmple& num)const;
	bool operator<=(const Vector2Tmple& num)const;
	bool operator>(const Vector2Tmple& num)const;
	bool operator>=(const Vector2Tmple& num)const;
	bool operator==(const Vector2Tmple& num)const;
	bool operator!=(const Vector2Tmple& num)const;


	//�x�N�g���̑傫����Ԃ�
	float Magnitude()const;//���̒��ł͒l�̕ύX�����Ȃ���
	//�x�N�g����2���Ԃ�
	float SQ_Magnitude()const;
	//���K������
	void Normalize(); 
	Vector2Tmple Normalized();
	//�p�x��Ԃ�
	float Theta();
	//90�x��]
	void Rotate90();


private:
};

template<class T> //�錾�O�Ȃ̂ōēx�錾���ċ����Ă����Ȃ��Ƃ����Ȃ�
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

