#pragma once
#include"Address.h"

class PhysicalAddress :public Address {
	int frameNumberBits;
public:
	PhysicalAddress(long value, int frame = FrameNumberBits, int bits = PhysicalAddrSize) :Address(bits, value),frameNumberBits(frame) {

	}

	PhysicalAddress(int frameN, int offset, int frame = FrameNumberBits, int bits = PhysicalAddrSize) :Address(bits), frameNumberBits(frame) {
		int offsetBit = bits - frame;
		int frameNum = frameN << offsetBit;
		rawValue = frameNum + offset;
	}

	unsigned int getFrameNumber();
	unsigned int getOffset();
};