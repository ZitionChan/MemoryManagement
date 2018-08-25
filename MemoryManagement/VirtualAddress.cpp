#include"VirtualAddress.h"


unsigned int VirtualAddress::getFirstPageNumber() {
	int offset = (VirtualAddrSize - FirstPageBits);
	unsigned int firstNumber = rawValue >> offset;


	return firstNumber;
}
unsigned int VirtualAddress::getSecondPageNumber() {
	int offset = (VirtualAddrSize - FirstPageBits-SecondPageBits);
	unsigned int rawNumber = rawValue >> offset;
	unsigned int firstNumber = getFirstPageNumber();
	firstNumber <<= SecondPageBits;
	unsigned int secondNumber = rawNumber - firstNumber;
	
	return secondNumber;
}
unsigned int VirtualAddress::getOffset() {
	int offBit = (VirtualAddrSize - FirstPageBits - SecondPageBits);
	unsigned int rawNumber = rawValue >> offBit;
	rawNumber <<= offBit;
	unsigned int offset = rawValue - rawNumber;

	return offset;
}