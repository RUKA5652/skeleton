#include "KeyInput.h"
#include<DxLib.h>
#include"../../_debug/_DebugConOut.h"


KeyInput::KeyInput()
{
	inputTbl_ = { 
		//{InputID::Up,KEY_INPUT_W	},{InputID::Down ,KEY_INPUT_S},
		//{InputID::Left,KEY_INPUT_A},{InputID::Right,KEY_INPUT_D},
				{InputID::Up,KEY_INPUT_UP	},{InputID::Down ,KEY_INPUT_DOWN},
		{InputID::Left,KEY_INPUT_LEFT},{InputID::Right,KEY_INPUT_RIGHT},
		{InputID::Btn1,KEY_INPUT_Z},{InputID::Btn2,KEY_INPUT_X}, 
		{InputID::Btn3,KEY_INPUT_C},{InputID::Btn4,KEY_INPUT_V}
	};//2ŒÂ‚ÅˆêŒÂ‚ÌŽž‚Í{{}}‚É‚È‚é
	ringBuf_ = ringBuf_->MaikRingBuf(10);

}

KeyInput::~KeyInput()
{
	ringBuf_->DestroyRingBuf(ringBuf_);
}

void KeyInput::Update()
{
	//for (auto& cntdata : cntData_)
	//{
	//	cntdata.second[static_cast<size_t>(Tag::Old)] = cntdata.second[static_cast<size_t>(Tag::Now)];
	//}

	GetHitKeyStateAll(keystate_.data());
	auto tagNo = static_cast<size_t>(Tag::Now);
	auto tagOl = static_cast<size_t>(Tag::Old);
	//cntData_.at(InputID::Up)[tagNo] = keystate_[KEY_INPUT_UP];
	//cntData_.at(InputID::Down)[tagNo] = keystate_[KEY_INPUT_DOWN];
	//cntData_.at(InputID::Left)[tagNo] = keystate_[KEY_INPUT_LEFT];
	//cntData_.at(InputID::Right)[tagNo] = keystate_[KEY_INPUT_RIGHT];
	//cntData_.at(InputID::Btn1)[tagNo] = keystate_[KEY_INPUT_Z];
	//cntData_.at(InputID::Btn2)[tagNo] = keystate_[KEY_INPUT_X];
	//cntData_.at(InputID::Btn3)[tagNo] = keystate_[KEY_INPUT_C];
	//cntData_.at(InputID::Btn4)[tagNo] = keystate_[KEY_INPUT_V];
	//for (int cnt = 0; cnt < static_cast<int>(InputID::MAX); cnt++)
	//{
	//	auto inputID = static_cast<InputID>(cnt);
	//	cntData_.at(inputID)[tagNo] = keystate_[inputTbl_.at(inputID)];
	//}
	ringBuf_->id = 0;
	for (auto inputID : InputID())
	{
		cntData_.at(inputID)[tagOl] = cntData_.at(inputID)[tagNo];
		cntData_.at(inputID)[tagNo] = keystate_[inputTbl_[inputID]];
		ringBuf_->id += keystate_[inputTbl_[inputID]] << static_cast<InputBit>(inputID);
	}
	ringBuf_ = ringBuf_->next;

	//auto* ringBufS = ringBuf_->before;
	//while (ringBufS != ringBuf_)
	//{
	//	TRACE("id%d", ringBuf_->id);
	//	ringBuf_ = ringBuf_->next;
	//}
	//TRACE("id%d\n", ringBuf_->id);
	//ringBuf_ = ringBuf_->next;

}
