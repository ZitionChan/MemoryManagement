#pragma once

#include"MemoryManagement.h"

class Stimulator {
	MemoryManagement mm;
	void runProcess(unsigned int randAddr);
	void runP1();
	void runP2();
	void runP3();
	void runP4();
	void runP5();
public:
	Stimulator(){}
	void run();

};

inline unsigned int K(int num) {
	return num * 1024;
}

inline unsigned int M(int num) {
	return num * 1024 * 1024;
}

inline unsigned int G(int num) {
	return num * 1024 * 1024 * 1024;
}