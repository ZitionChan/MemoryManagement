# 虚拟内存管理器

## 运行环境
本程序可以使用visual studio 2017编译运行,需支持c++11。

## 运行说明
注：若运行报错，请删除当前项目目录下`*.pgtb`文件

`*.pgtb`为运行时产生的页表文件，用于储存页表内容


```
Stimulator stimulator;
stimulator.run();

```
即可启动运行，参见main.cpp

## 运行结果

实验结果保存在results目录内

实验结果打开为ios::app模式，因此会多次运行会将结果追加到文件，必要时可删除文件后重新运行。

输出文件：
* `addr_seq_i.txt`保存进程i的所有随机访问的虚拟地址序列。
* `visit_seq_i.txt` 保存进程i每次的访问信息，一行对应一次访问，对应信息如下：

```**FirstPageNumber  SecondPageNumber  TLB hit/no hit  PT hit/no hit**```
* `page_table_i.txt` 保存进程i最后一次运行结束后的page table。
输出格式如下：
```
first page number:
	second page number:  frame number
```
关于实验的参数全部位于`Config.h`内