#include"TLB.h"
#include<exception>
#include<iostream>

unsigned int TLB::getFrameNumber(unsigned int firstPageNumber,unsigned int secondPageNumber) {
	unsigned int pageNumber = (firstPageNumber << SecondPageBits) + secondPageNumber;
	
	for (int i = 0; i < table.size(); i++) {
		if (pageNumber == table[i].pageNumber) {
			return table[i].frameNumber;
		}
	}
	throw std::invalid_argument("TLB's item not found");
}

void TLB::append(TLBItem it) {

	for (int i = 0; i < table.size(); i++) {
		if (it.pageNumber == table[i].pageNumber) {
			table.erase(table.begin() + i);
			break;
		}
	}

	if (table.size() == maxSize) {
		table.erase(table.begin());
	}

	table.push_back(it);
}

void TLB::clear() {
	table.clear();
}

void TLB::display() {
	std::cout << "TLB:";
	for (int i = 0; i < table.size(); i++) {
		std::cout << "("<<table[i].pageNumber<<","<<table[i].frameNumber << ") ";
	}
	cout << endl;
}