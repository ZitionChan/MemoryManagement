#pragma once
#include"Address.h"

class VirtualAddress :public Address {
	int firstPageBits;
	int secondPageBits;
public:
	VirtualAddress(long value, int first=FirstPageBits, int second=SecondPageBits, int bits = VirtualAddrSize) :Address(bits, value), firstPageBits(first), secondPageBits(second) {

	}

	unsigned int getFirstPageNumber();
	unsigned int getSecondPageNumber();
	unsigned int getOffset();
};