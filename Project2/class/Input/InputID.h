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

static InputID begin(InputID) { return InputID::Up; };//beginŠÖ”‚ğì‚é
static InputID end(InputID) { return InputID::MAX; };//endŠÖ”‚ğì‚é
static InputID operator++(InputID& StateID) { return StateID = static_cast<InputID>(std::underlying_type<InputID>::type(StateID) +1)/*Šî’ê‚ÌŒ^‚É‚µ‚Ä+‚P*/; };//++ŠÖ”‚ğì‚é ƒK[ƒhˆ—‚Í‚È‚¢
static InputID operator*(const InputID& StateID) { return StateID; };//*ŠÖ”‚ğì‚é

using InputBit = unsigned int;

