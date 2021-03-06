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

static InputID begin(InputID) { return InputID::Up; };//begin関数を作る
static InputID end(InputID) { return InputID::MAX; };//end関数を作る
static InputID operator++(InputID& StateID) { return StateID = static_cast<InputID>(std::underlying_type<InputID>::type(StateID) +1)/*基底の型にして+１*/; };//++関数を作る ガード処理はない
static InputID operator*(const InputID& StateID) { return StateID; };//*関数を作る

using InputBit = unsigned int;

