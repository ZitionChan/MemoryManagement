#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include"Config.h"
#include"TLB.h"
#include"PageTable.h"
#include"VirtualAddress.h"
#include"PhysicalAddress.h"
#include"PhysicalMemory.h"

template<typename T>
string toStr(T str) {
	stringstream ss;
	ss << str;
	return ss.str();
}

struct Rate {
	bool isNull;
	int total;
	int TLBHit;
	int pageHit;
	Rate() {
		isNull = true;
		total = TLBHit = pageHit = 0;
	}
};

class MemoryManagement {
	TLB tlb;
	PageTable<PageTable<PageItem>> firstPageTable;
	PhysicalMemory memory;//模拟真实内存
	int currPid;
	ofstream* logFile;
	ofstream* visitFile;
	vector<Rate> rates; //记录访问成功与否的数据

	PhysicalAddress getPhysicalAddr(VirtualAddress addr);
	int getFromPageTable(VirtualAddress addr); //返回FrameNumber， -1 则Page miss
	void updatePageTable(VirtualAddress addr,int FrameNum); //更新PageTable
	void updateTLB(VirtualAddress, unsigned int FrameNum); //更新TLB
	void modifiedProcessPageTable(int pid, unsigned int frameNum);//删除某进程的pagetable中页框信息
	void savePageTable();
	void pageTableDisplay(PageTable<PageTable<PageItem>> table);
public:
	MemoryManagement();
	void access(VirtualAddress addr);//访问地址
	void switchProcess(int pid);
	void loadPageTable(int pid);
	void pageTableDisplay();
	void showRates();

};