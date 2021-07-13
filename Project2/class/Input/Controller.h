#pragma once
#include <map>
#include <array>
#include"InputID.h"

enum class Tag
{
	Now,
	Old,
	MAX
};


enum class CntType
{
	Key,
	Pad,
	MAX
};




using TrgBool = std::array<bool, static_cast<size_t>(Tag::MAX)>;//ŒÅ’è’·”z—ñ
using CntData = std::map<InputID, TrgBool>;



class Controller
{
public:
		struct RingBuf
		{
				InputBit id;
				RingBuf* before = nullptr;
				RingBuf* next = nullptr;
				static RingBuf* MaikRingBuf(size_t size);
				static bool DestroyRingBuf(RingBuf* startBuf);
		};


	Controller();
	virtual ~Controller() {};

	virtual void Update() =0;
	const CntData& GetCntData(void) const {return cntData_;};
	const RingBuf* GetRingBuf(void) const { return  ringBuf_;};
	const InputBit& GetBufData(void) const { return  ringBuf_->id; };
	virtual  CntType GetCntType(void) = 0;
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> inputTbl_;
	RingBuf* ringBuf_;
};
using RingBuf = Controller::RingBuf;


