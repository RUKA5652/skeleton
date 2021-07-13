#include "PadInuput.h"
#include<DxLib.h>

PadInuput::PadInuput(int padNo) :padNo(padNo)
{
	inputTbl_ = {
	{	InputID::Up,PAD_INPUT_UP},{InputID::Down ,PAD_INPUT_DOWN},
	{InputID::Left,PAD_INPUT_LEFT},{InputID::Right,PAD_INPUT_RIGHT},
	{InputID::Btn1,PAD_INPUT_A},{InputID::Btn2,PAD_INPUT_Y},
	{InputID::Btn3,PAD_INPUT_X},{InputID::Btn4,PAD_INPUT_B}
	};//2ŒÂ‚ÅˆêŒÂ‚Ì‚Í{{}}‚É‚È‚é
}

PadInuput::~PadInuput()
{
}

void PadInuput::Update()
{
	//for (auto& cntdata : cntData_)
	//{
	//	cntdata.second[static_cast<size_t>(Tag::Old)] = cntdata.second[static_cast<size_t>(Tag::Now)];
	//}
	auto padData = GetJoypadInputState(padNo);
	auto tagNo = static_cast<size_t>(Tag::Now);
	auto tagOl = static_cast<size_t>(Tag::Old);
	//cntData_.at(InputID::Up)[tagNo] = padData & PAD_INPUT_UP;
	//cntData_.at(InputID::Down)[tagNo] = padData & PAD_INPUT_DOWN;
	//cntData_.at(InputID::Left)[tagNo] = padData & PAD_INPUT_LEFT;
	//cntData_.at(InputID::Right)[tagNo] = padData & PAD_INPUT_RIGHT;
	//cntData_.at(InputID::Btn1)[tagNo] = padData & PAD_INPUT_A;
	//cntData_.at(InputID::Btn2)[tagNo] = padData & PAD_INPUT_Y;
	//cntData_.at(InputID::Btn3)[tagNo] = padData & PAD_INPUT_X;
	//cntData_.at(InputID::Btn4)[tagNo] = padData & PAD_INPUT_B;
	for (auto inputID : InputID())
	{
		cntData_.at(inputID)[tagOl] = cntData_.at(inputID)[tagNo];
		cntData_.at(inputID)[tagNo] = ((padData & inputTbl_.at(inputID)) > 0);//’l‚ªboolŒ^‚¶‚á‚È‚¢‚Ì‹C‚¿ˆ«‚­‚Ë
	}
}
