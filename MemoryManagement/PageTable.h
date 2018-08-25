#pragma once
#include<exception>
#include<vector>
#include<ostream>
#include<istream>

using namespace std;

struct PageItem {
	bool isNull;
	unsigned int frameNum;
	PageItem() {
		isNull = true;
	}

	PageItem(unsigned int framen) {
		isNull = false;
		frameNum = framen;

	}
};

template <class T>
class PageTable {
protected:
	int maxSize;
	vector<T>table;
public:
	bool isNull;
	PageTable():isNull(true),maxSize(-1){}
	PageTable(int size) :maxSize(pow(2,size)),table(maxSize),isNull(false) {

	}
	
	~PageTable() {
	
	}

	virtual void init(T value) {
		for (int i = 0; i < maxSize; i++) {
			table[i] = value;
		}
	}

	void append(T item,unsigned int index) {
		table[index] = item;
	}

	T getItem(unsigned int pageNumber) {
		if (pageNumber < maxSize) {
			return table[pageNumber];
		}
		
		throw out_of_range("pageNumber out of range");
	}

	void clear() {
		table = vector<T>(maxSize);
	}

	vector<T>& getTable() { return table; }

	ostream& save(ostream& output) {
		output.write(reinterpret_cast<const char*>(&isNull), sizeof(isNull));
		if (!isNull) {
			output.write(reinterpret_cast<const char*>(&maxSize), sizeof(maxSize));
			for (auto it : table) {
				output << it;
			}
		}
		return output;
	}

	istream& load(istream& input) {
		input.read(reinterpret_cast<char*>(&isNull), sizeof(isNull));
		if (!isNull) {
			input.read(reinterpret_cast<char*>(&maxSize), sizeof(maxSize));
			table = vector<T>(maxSize);
			for (int i = 0; i < maxSize; i++) {
				input >> table[i];
			}
		}
		return input;
	}


};

template<class T>
ostream& operator<<(ostream& output, PageTable<T>& pt) {
	return pt.save(output);
}

template<class T>
istream& operator>>(istream& input, PageTable<T>& pt) {
	return pt.load(input);
}


ostream& operator<<(ostream& output, PageItem& pt); 


istream& operator>>(istream& input, PageItem& pt);