#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class data{
public:
	bool valid;
	int tag;
	vector<int> block;
	bool dirty;
	data() : valid(0), tag(0), dirty(0){}
	data(const int & blocksize) : valid(0), tag(0), dirty(0){
		for(int i=0;i<blocksize;++i)
			block.push_back(0);
	}
	~data(){}
};
