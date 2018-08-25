#pragma once
#include"Frame.h"

#define VirtualAddrSize 32 //bit 虚拟地址位数
#define FirstPageBits 9 //bit一级页表位数
#define SecondPageBits 10 //bit二级页表位数

#define PhysicalAddrSize 3// 25 //bit 物理地址位数
#define FrameNumberBits 12//bit 页框数位数

#define TLBSize 16 //TLB默认包含的项数

#define FrameSize 2//13 //bit 页框大小

//virtual Page = frame
typedef Frame<unsigned int> Page;
typedef Page Frame_t; 