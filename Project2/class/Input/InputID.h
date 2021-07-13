#pragma once
#include<type_traits>


enum class InputID
{
	Up,
	Down,
	Left,
	Right,
	Btn1,
	Btn2,
	Btn3,
	Btn4,
	MAX,
};

static InputID begin(InputID) { return InputID::Up; };//begin�֐������
static InputID end(InputID) { return InputID::MAX; };//end�֐������
static InputID operator++(InputID& StateID) { return StateID = static_cast<InputID>(std::underlying_type<InputID>::type(StateID) +1)/*���̌^�ɂ���+�P*/; };//++�֐������ �K�[�h�����͂Ȃ�
static InputID operator*(const InputID& StateID) { return StateID; };//*�֐������

using InputBit = unsigned int;

