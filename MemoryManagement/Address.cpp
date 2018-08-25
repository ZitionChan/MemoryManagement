#include"Address.h"

ostream& operator<<(ostream& os,Address& addr) {
	os << hex << addr.rawValue<<dec;
	return os;
}