#include"Stimulator.h"
#include<cstdlib>
#include<ctime>

void Stimulator::run() {
	for (int i = 0; i < 3; i++) {
		runP1(); if (i == 2) mm.pageTableDisplay();
		runP2(); if (i == 2) mm.pageTableDisplay();
		runP3(); if (i == 2) mm.pageTableDisplay();
		runP4(); if (i == 2) mm.pageTableDisplay();
		runP5(); if (i == 2) mm.pageTableDisplay();
	}

	cout << "Run finished!" << endl;

	mm.showRates();
}

void Stimulator::runProcess(unsigned int randAddr) {
	unsigned int randNum = randAddr;

		for (int j = 0; j < 10; j++) {
			mm.access(VirtualAddress(randNum++));
		}

}


void Stimulator::runP1() {
	mm.switchProcess(0);

	srand(time(0));
	unsigned int randNum;
	
	//低位随机
	for (int i = 0; i < 25; i++) {
		 randNum = rand() / double(RAND_MAX) * K(512);
		 runProcess(randNum);
	}

	//高位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * K(512)+ G(4) -K(512);
		runProcess(randNum);
	}
}

void Stimulator::runP2() {
	mm.switchProcess(1);

	srand(time(0));
	unsigned int randNum;

	//低位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(16) + M(1);
		runProcess(randNum);
	}

	//高位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(16) + G(4)-M(17);
		runProcess(randNum);
	}
}

void Stimulator::runP3() {
	mm.switchProcess(2);

	srand(time(0));
	unsigned int randNum;

	//低位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(32) + M(17);
		runProcess(randNum);
	}

	//高位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(32) + G(4) - M(49);
		runProcess(randNum);
	}
}


void Stimulator::runP4() {
	mm.switchProcess(3);

	srand(time(0));
	unsigned int randNum;

	//低位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(64) + M(49);
		runProcess(randNum);
	}

	//高位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(64) + G(4) - M(113);
		runProcess(randNum);
	}
}

void Stimulator::runP5() {
	mm.switchProcess(4);

	srand(time(0));
	unsigned int randNum;

	//低位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(128) + M(113);
		runProcess(randNum);
	}

	//高位随机
	for (int i = 0; i < 25; i++) {
		randNum = rand() / double(RAND_MAX) * M(128) + G(4) - M(241);
		runProcess(randNum);
	}
}