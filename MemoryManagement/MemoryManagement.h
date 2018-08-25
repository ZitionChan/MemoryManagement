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
	PhysicalMemory memory;//ģ����ʵ�ڴ�
	int currPid;
	ofstream* logFile;
	ofstream* visitFile;
	vector<Rate> rates; //��¼���ʳɹ���������

	PhysicalAddress getPhysicalAddr(VirtualAddress addr);
	int getFromPageTable(VirtualAddress addr); //����FrameNumber�� -1 ��Page miss
	void updatePageTable(VirtualAddress addr,int FrameNum); //����PageTable
	void updateTLB(VirtualAddress, unsigned int FrameNum); //����TLB
	void modifiedProcessPageTable(int pid, unsigned int frameNum);//ɾ��ĳ���̵�pagetable��ҳ����Ϣ
	void savePageTable();
	void pageTableDisplay(PageTable<PageTable<PageItem>> table);
public:
	MemoryManagement();
	void access(VirtualAddress addr);//���ʵ�ַ
	void switchProcess(int pid);
	void loadPageTable(int pid);
	void pageTableDisplay();
	void showRates();

};