#include<iostream>

#include"MemoryManagement.h"

using namespace std;

int main() {
	
	MemoryManagement mm;
	//mm.loadPageTable(0);
	mm.pageTableDisplay();

	mm.access(VirtualAddress(8*1024));
	mm.access(VirtualAddress(0));
	mm.pageTableDisplay();
	mm.access(VirtualAddress(8*1024+1));
	mm.access(VirtualAddress(2 * 8 * 1024+1));
	mm.access(VirtualAddress(8*1024));
	mm.pageTableDisplay();

	mm.switchProcess(1);

	mm.access(VirtualAddress(3 * 8 * 1024 + 1));
	mm.pageTableDisplay();
	mm.access(VirtualAddress(4* 8*1024));
	mm.pageTableDisplay();

	mm.switchProcess(0);
	mm.pageTableDisplay();
	mm.access(VirtualAddress(8*1024));
	mm.access(VirtualAddress(16 * 1024));
	mm.switchProcess(2);
	system("pause");
	return 0;
}
