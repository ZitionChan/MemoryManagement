#pragma once
#include"Frame.h"

#define VirtualAddrSize 32 //bit �����ַλ��
#define FirstPageBits 9 //bitһ��ҳ��λ��
#define SecondPageBits 10 //bit����ҳ��λ��

#define PhysicalAddrSize 3// 25 //bit �����ַλ��
#define FrameNumberBits 12//bit ҳ����λ��

#define TLBSize 16 //TLBĬ�ϰ���������

#define FrameSize 2//13 //bit ҳ���С

//virtual Page = frame
typedef Frame<unsigned int> Page;
typedef Page Frame_t; 