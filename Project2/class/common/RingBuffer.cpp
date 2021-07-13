#include "RingBuffer.h"

RingBuffer::RingBuffer(size_t size)
{

}

RingBuffer::~RingBuffer()
{

}

RingBuf* RingBuffer::MaikRingBuf(size_t size)
{
		int cnt = 0;
		RingBuf* fist;
		RingBuf* now = (new RingBuf{ InputID::MAX,nullptr,nullptr });
		cnt++;
		RingBuf* beforBuf = now;
		RingBuf* nextBuf = now;
		fist = now;
		for (cnt; cnt < size; cnt++)
		{
				nextBuf = (new RingBuf{ InputID::MAX ,nullptr,nullptr });
				nextBuf->before = beforBuf;
				beforBuf->next = nextBuf;
				beforBuf = nextBuf;
		}
		nextBuf->next = fist;
		fist->before = nextBuf;
		return fist;
}

bool RingBuffer::DestroyRingBuf(RingBuf* startBuf)
{
		return false;
}

