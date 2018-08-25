
#include<iostream>
#include"PageTable.h"


ostream& operator<<(ostream& output, PageItem& pt) {
	output.write(reinterpret_cast<const char*>(&pt.isNull), sizeof(pt.isNull));
	if (!pt.isNull) {
		output.write(reinterpret_cast<const char*>(&pt.frameNum), sizeof(pt.frameNum));
	}
	return output;
}


istream& operator>>(istream& input, PageItem& pt) {
	input.read(reinterpret_cast<char*>(&pt.isNull), sizeof(pt.isNull));
	if (!pt.isNull) {
		input.read(reinterpret_cast<char*>(&pt.frameNum), sizeof(pt.frameNum));
	}
	return input;
}
