#pragma once
#include"../Input/InputID.h"
#include <list>

class RingBuffer
{
public:
		struct RingBuf
		{
				InputID id;
				RingBuffer* before = nullptr;
				RingBuffer* next = nullptr;
		};
		RingBuffer(size_t size);
		~RingBuffer();
		RingBuf* fastBuf;
private:
		static RingBuf* MaikRingBuf(size_t size);
		static bool DestroyRingBuf(RingBuf* startBuf);
};

using  RingBuf = RingBuffer::RingBuf;