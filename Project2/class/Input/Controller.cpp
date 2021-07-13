#include "Controller.h"

Controller::Controller()
{
	//for (int cnt = 0; cnt < static_cast<int>(InputID::MAX); cnt++)
	//{
	//	cntData_.try_emplace(static_cast<InputID>(cnt));
	//}

	for (auto inputID : InputID())
	{
		cntData_.try_emplace(inputID, TrgBool{0,0});
		//cntData_.at(inputID)[static_cast<int>(Tag::Now)] = false;
		//cntData_.at(inputID)[static_cast<int>(Tag::Old)] = false;
	}

}


RingBuf* RingBuf::MaikRingBuf(size_t size)
{
		int cnt = 0;
		RingBuf* fist;
		RingBuf* now = (new RingBuf{static_cast<unsigned int>(cnt),nullptr,nullptr });
		cnt++;
		RingBuf* beforBuf = now;
		RingBuf* nextBuf = now;
		fist = now;
		for (cnt; cnt < size; cnt++)
		{
				nextBuf = (new RingBuf{static_cast<unsigned int>(cnt),nullptr,nullptr });
				nextBuf->before = beforBuf;
				beforBuf->next = nextBuf;
				beforBuf = nextBuf;
		}
		nextBuf->next = fist;
		fist->before = nextBuf;
		return fist;
		//-----
	/*	int cnt = 0;
		RingBuf* fist;
		RingBuf* now = (new RingBuf{ InputID::MAX,nullptr,nullptr });
		cnt++;
		RingBuf* next = (new RingBuf{ InputID::MAX,nullptr,nullptr });
		cnt++;
		RingBuf* beforBuf = now;
		RingBuf* nextBuf = next;
		now->next = nextBuf;
		next->before = beforBuf;
		fist = now;
		beforBuf = next;
		for (cnt; cnt < size; cnt++)
		{
				next = (new RingBuf{ InputID::MAX,nullptr,nullptr });
				nextBuf = next;
				nextBuf->before = beforBuf;
				beforBuf->next = nextBuf;
				beforBuf = next;
		}
		next->next = fist;
		fist->before = next;
		return fist;*/

}

bool RingBuf::DestroyRingBuf(RingBuf* startBuf)
{
	if (startBuf->before == nullptr)
	{
		return false;
	}
	
	//startBuf->before->next = nullptr;
	//auto& buf = startBuf->next;
	//for (buf; buf->next != nullptr; buf = buf->next)
	//{
	//	auto* test = buf->before;
	//	delete	test;
	//}
	//delete buf;
	startBuf->before->next = nullptr;
	while (startBuf->next != nullptr)
	{
		startBuf = startBuf->next;
		delete startBuf->before;
	}
	delete startBuf;
	return true;
}
