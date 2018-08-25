#pragma once
#include<vector>
#include"Config.h"

struct TLBItem {
	unsigned int pageNumber;
	unsigned int frameNumber;
};

class TLB {
	int maxSize;
	std::vector<TLBItem> table;
public:
	TLB(int m=TLBSize):maxSize(m){}
	unsigned int getFrameNumber(unsigned int firstPageNumber,unsigned int secondPageNumber);
	void append(TLBItem it);
	void clear();
	void display();
};