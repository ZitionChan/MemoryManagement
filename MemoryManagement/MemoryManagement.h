#pragma once
#include<fstream>
#include"Config.h"
#include"TLB.h"
#include"PageTable.h"
#include"VirtualAddress.h"
#include"PhysicalAddress.h"
#include"PhysicalMemory.h"



class MemoryManagement {
	TLB tlb;
	PageTable<PageTable<PageItem>> firstPageTable;
	PhysicalMemory memory;//模拟真实内存
	int currPid;

	PhysicalAddress getPhysicalAddr(VirtualAddress addr);
	int getFromPageTable(VirtualAddress addr); // return frame number, return -1 if page fault
	void updatePageTable(VirtualAddress addr,int FrameNum);
	void updateTLB(VirtualAddress, unsigned int FrameNum);

	void savePageTable();

public:
	MemoryManagement();
	void access(VirtualAddress addr);
	void switchProcess(int pid);
	void tlbDisplay() { tlb.display(); }
	void tlbClear() { tlb.clear(); }
	void loadPageTable(int pid);
	void pageTableDisplay();
	void pageTableDisplay(PageTable<PageTable<PageItem>> table);

	void modifiedProcessPageTable(int pid,unsigned int frameNum);//删除某进程的pagetable中页框信息
};