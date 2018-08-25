#include"MemoryManagement.h"
#include<sstream>
#include<fstream>

MemoryManagement::MemoryManagement():firstPageTable(FirstPageBits),memory(PhysicalAddrSize),currPid(0){

}

void MemoryManagement::updateTLB(VirtualAddress addr, unsigned int frameNum) {
	auto firstPageNumber = addr.getFirstPageNumber();
	auto secondPageNumeber = addr.getSecondPageNumber();
	auto pageNumber = (firstPageNumber << SecondPageBits) + secondPageNumeber;

	tlb.append({ pageNumber,frameNum });
}

void MemoryManagement::updatePageTable(VirtualAddress addr,int frameNum) {
	auto firstPageNumber = addr.getFirstPageNumber();
	auto secondPageNumeber = addr.getSecondPageNumber();

	auto secondPageTable = firstPageTable.getItem(firstPageNumber);

	if (secondPageTable.isNull) {
		secondPageTable =  PageTable<PageItem>(SecondPageBits);

		secondPageTable.append(PageItem(frameNum), secondPageNumeber);
		firstPageTable.append(secondPageTable, firstPageNumber);
	}
	else {
		secondPageTable.append(PageItem(frameNum), secondPageNumeber);
		firstPageTable.append(secondPageTable, firstPageNumber);
	}
	cout << "update PageTable: frame number:" <<frameNum<< endl;
	
}

void MemoryManagement::access(VirtualAddress addr) {
	auto physicalAddr = getPhysicalAddr(addr);
	memory.access(physicalAddr);
}


PhysicalAddress MemoryManagement::getPhysicalAddr(VirtualAddress addr) {
	try {

		//1. try to get from tlb
		int frameNum = tlb.getFrameNumber(addr.getFirstPageNumber(),addr.getSecondPageNumber());
		cout << "access " << addr << " TLB hit!" << endl;
		return PhysicalAddress(frameNum, addr.getOffset());
	}
	catch (invalid_argument err) {
		cout << "access " << addr << " TLB miss!" << endl;

		//2. try to get from page table
		int frameNumber = getFromPageTable(addr);
		if (frameNumber>=0) {
			updateTLB(addr, frameNumber);
			return PhysicalAddress(frameNumber, addr.getOffset());
		}
		else {
			//3. assign from memory
			auto framestruct = memory.assign(currPid);

			frameNumber = framestruct.newFrameNumber;

			updatePageTable(addr, frameNumber);
			updateTLB(addr, frameNumber);

			auto oldpid = framestruct.oldPid;
			modifiedProcessPageTable(oldpid, frameNumber);

			return PhysicalAddress(frameNumber, addr.getOffset());
		}

	}
	

}

int MemoryManagement::getFromPageTable(VirtualAddress addr) {
	unsigned int firstPageNumber = addr.getFirstPageNumber();
	unsigned int secondPageNumber = addr.getSecondPageNumber();
	unsigned int pageOffset = addr.getOffset();

	auto secondPageTable = firstPageTable.getItem(firstPageNumber);

	if (!secondPageTable.isNull) {
		cout << "first pageTable hit!" << endl;
		auto PageItem = secondPageTable.getItem(secondPageNumber);
		if (!PageItem.isNull) {
			cout << "access " << addr << " Page hit!" << endl;
			return PageItem.frameNum;
		}
	}
	cout <<"access "<<addr<< " Page fault!" << endl;
	return -1;
}


void MemoryManagement::switchProcess(int pid) {
	cout << "Switch to Process " << pid << endl;
	savePageTable();
	currPid = pid;
	firstPageTable.clear();
	loadPageTable(pid);
	tlb.clear();
}

void MemoryManagement::savePageTable() {
	stringstream ss; 
	ss<< currPid<<".pgtb";
	string fileName = ss.str();

	ofstream output(fileName);

	if(output)
	output << firstPageTable;
	else throw "saveFail";
}

void MemoryManagement::loadPageTable(int pid) {
	stringstream ss;
	ss << pid << ".pgtb";
	string fileName = ss.str();

	ifstream input(fileName);
	
	if(input)
		input >> firstPageTable;

}

void MemoryManagement::modifiedProcessPageTable(int pid, unsigned int frameNum) {
	PageTable<PageTable<PageItem>> inputPageTable;
	PageTable<PageTable<PageItem>>& tempPageTable = (pid==currPid)? firstPageTable:inputPageTable;

	stringstream ss;
	ss << pid << ".pgtb";
	string fileName = ss.str();

	if (pid!=currPid) {
		ifstream input(fileName);
		if(input) input >> inputPageTable;
	}
		auto& tables = tempPageTable.getTable();
		for (int i = 0; i < tables.size();i++) {
			if (!tables[i].isNull) {
				auto& secondTable = tables[i].getTable();
				for (int j = 0; j < secondTable.size();j++) {
					if (!secondTable[j].isNull&&secondTable[j].frameNum == frameNum) {
						cout << "Delete pid:"<<pid<<"'s page table about frameNum:" << frameNum << endl;
						secondTable[j].isNull = true;
						break;
					}
				}
				break;
			}
		}

		if (pid != currPid) {
			ofstream output(fileName);
			if (output) output << tempPageTable;
		}

		cout << "after modified:" << endl;
		pageTableDisplay(tempPageTable);
	


}

void MemoryManagement::pageTableDisplay() {
	pageTableDisplay(firstPageTable);
}

void MemoryManagement::pageTableDisplay(PageTable<PageTable<PageItem>> pageTable) {
	auto table = pageTable.getTable();
	cout << "=============pageTable============" << endl;
	for (int i = 0; i < table.size(); i++) {
		if (!table[i].isNull) {
			cout << i <<":"<< endl;
			auto secondtable = table[i].getTable();

			for (int j = 0; j < secondtable.size(); j++) {
				if (!secondtable[j].isNull) {
					cout << "   ги" <<j<<","<< secondtable[j].frameNum << ") " << endl;
				}
			}
		}
	}
	cout << "==================================" << endl;
}