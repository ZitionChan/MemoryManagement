#pragma once
#include<iostream>
#include<iomanip>
#include"Config.h"
using namespace std;

class Address {
protected:
	int allBits;
	unsigned int rawValue;
public:
	Address(int ab = 0,unsigned int value=0):rawValue(value),allBits(ab) {

	}

	friend ostream& operator<<(ostream& os, Address& addr);
};
