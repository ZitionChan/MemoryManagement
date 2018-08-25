#include"PhysicalAddress.h"


unsigned int PhysicalAddress::getFrameNumber() {
	int offset = (PhysicalAddrSize - FrameNumberBits);
	unsigned int frameNumber = rawValue >> offset;
	
		return frameNumber;
}

unsigned int PhysicalAddress::getOffset() {
	unsigned int frameNumber = getFrameNumber();
	frameNumber <<= (PhysicalAddrSize - FrameNumberBits);
	unsigned int offset = rawValue - frameNumber;

	return offset;
}