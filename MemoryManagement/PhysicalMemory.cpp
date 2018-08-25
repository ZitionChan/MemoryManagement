#include"PhysicalMemory.h"
#include"Config.h"

PhysicalMemory::PhysicalMemory(unsigned int size) :maxSize(pow(2, size-FrameSize)), frames(maxSize),frameOrders(maxSize) {
	//cout << "create physicalMemory, size:" << maxSize << endl;
}

FramesStruct PhysicalMemory::assign(unsigned int pid) {
	Frame_t* frame =new Frame_t(FrameSize);
	frame->pid = pid;
	frame->init(pid);

	int frameNum=-1,oldPid=-1;

	if (!frameOrders.isFull()) {
		for (int i = 0; i < frames.size();i++) {
			if (frames[i] == nullptr) {
				frames[i] = frame;
				frameOrders.push(i);
				frameNum = i;
				break;
			}
		}
	}
	else {
		int index = frameOrders.pop();

		oldPid = frames[index]->pid;

		delete frames[index];

		frames[index] = frame;

		frameNum = index;

		frameOrders.push(index);
	}

	return { frameNum,oldPid };
}

void PhysicalMemory::access(PhysicalAddress address) {
	unsigned int frameNumber = address.getFrameNumber();
	unsigned int offset = address.getOffset();

	if (frameNumber < maxSize) {
		//cout << "Access physicalAddress:" << address << " success and get content(pid):" << frames[frameNumber]->getItem(offset)<<endl;
	}
	else {
		throw out_of_range("frameNumber out of range");
	}
}