#include"MemoryManagement.h"
#include<iomanip>
using namespace std;

MemoryManagement::MemoryManagement():firstPageTable(FirstPageBits),memory(PhysicalAddrSize),currPid(0),rates(10){

	string logFileName = "results/addr_seq_"+toStr(currPid)+".txt";
	string visitFileName = "results/visit_seq_" + toStr(currPid) + ".txt";

	logFile = new ofstream(logFileName,ios::app);
	visitFile = new ofstream(visitFileName,ios::app);

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

}

void MemoryManagement::access(VirtualAddress addr) {

	rates[currPid].isNull = false;
	rates[currPid].total++;

	*logFile << addr << endl;

	auto physicalAddr = getPhysicalAddr(addr);

	memory.access(physicalAddr);
}


PhysicalAddress MemoryManagement::getPhysicalAddr(VirtualAddress addr) {
	try {

		//1. try to get from tlb
		int frameNum = tlb.getFrameNumber(addr.getFirstPageNumber(),addr.getSecondPageNumber());

		*visitFile <<setw(13)<< addr.getFirstPageNumber() << setw(13) << addr.getSecondPageNumber() << setw(13) << frameNum <<setw(13)<< "TLB hit"<<setw(13)<<"-" << endl;
		rates[currPid].TLBHit++;
		//cout << "access " << addr << " TLB hit!" << endl;
		return PhysicalAddress(frameNum, addr.getOffset());
	}
	catch (invalid_argument err) {
		//cout << "access " << addr << " TLB miss!" << endl;

		//2. try to get from page table
		int frameNumber = getFromPageTable(addr);
		if (frameNumber>=0) {
			updateTLB(addr, frameNumber);

			*visitFile << setw(13) << addr.getFirstPageNumber() << setw(13) << addr.getSecondPageNumber() << setw(13) << frameNumber <<setw(13)<< "TLB no hit"<<setw(13)<<"PT hit" << endl;
			rates[currPid].pageHit++;

			return PhysicalAddress(frameNumber, addr.getOffset());
		}
		else {
			//3. assign from memory
			auto framestruct = memory.assign(currPid);

			frameNumber = framestruct.newFrameNumber;

			updatePageTable(addr, frameNumber);
			updateTLB(addr, frameNumber);

			*visitFile << setw(13) << addr.getFirstPageNumber() << setw(13) << addr.getSecondPageNumber() << setw(13) << frameNumber << setw(13)<<"TLB no hit" << setw(13)<<"PT no hit" << endl;

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
		auto PageItem = secondPageTable.getItem(secondPageNumber);
		if (!PageItem.isNull) {
			//cout << "access " << addr << " Page hit!" << endl;
			return PageItem.frameNum;
		}
	}
	//cout <<"access "<<addr<< " Page fault!" << endl;
	return -1;
}


void MemoryManagement::switchProcess(int pid) {

	cout << "Switch to Process " << pid << endl;
	savePageTable();
	currPid = pid;
	firstPageTable.clear();
	loadPageTable(pid);
	tlb.clear();

	delete logFile;
	delete visitFile;
	string fileName = "results/addr_seq_" + toStr(currPid) + ".txt";
	string visitName = "results/visit_seq_" + toStr(currPid) + ".txt";

	logFile =new ofstream(fileName,ios::app);
	visitFile = new ofstream(visitName, ios::app);

	*logFile	<< "========New Turn========" << endl;
	*visitFile	<< "========New Turn========" << endl;

}

void MemoryManagement::savePageTable() {

	string fileName =toStr(currPid)+".pgtb";

	ofstream output(fileName);

	if(output)	output << firstPageTable;
	else throw "saveFail";

}

void MemoryManagement::loadPageTable(int pid) {

	string fileName =toStr(pid)+".pgtb";

	ifstream input(fileName);
	
	if(input) input >> firstPageTable;

}

void MemoryManagement::modifiedProcessPageTable(int pid, unsigned int frameNum) {
	PageTable<PageTable<PageItem>> inputPageTable;
	PageTable<PageTable<PageItem>>& tempPageTable = (pid==currPid)? firstPageTable:inputPageTable;

	string fileName = toStr(pid)+".pgtb";

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

}

void MemoryManagement::pageTableDisplay() {
	pageTableDisplay(firstPageTable);
}

void MemoryManagement::pageTableDisplay(PageTable<PageTable<PageItem>> pageTable) {
	ofstream output("results/page_table_" + toStr(currPid) + ".txt");
	auto table = pageTable.getTable();
	
	for (int i = 0; i < table.size(); i++) {
		if (!table[i].isNull) {
			output << i <<":"<< endl;
			auto secondtable = table[i].getTable();

			for (int j = 0; j < secondtable.size(); j++) {
				if (!secondtable[j].isNull) {
					output << "    " <<j<<":   "<< secondtable[j].frameNum  << endl;
				}
			}
		}
	}
	
}

void MemoryManagement::showRates() {
	cout << "===========Run Result==========" << endl;
	for (int i = 0; i < 10;i++) {
		if (!rates[i].isNull) {
			cout << "Process " << i << " Page fault rate:" << (1- double(rates[i].pageHit+rates[i].TLBHit) / rates[i].total)*100 <<"%"<< endl;
		}
	}
}