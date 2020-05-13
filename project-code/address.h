#include <math.h>
#include <iostream>
#include <string>
using namespace std;

string & reverse(string & s, int len=32){
	int l=s.length();
	char temp;
	for(int i=l;i<len;++i) s.push_back('0');
	//cout<<s<<endl;
	for(int i=0;i<len/2;++i){
		temp=s[i];
		s[i]=s[len-1-i];
		s[len-1-i]=temp;
	}
	//cout<<s<<endl;
	return s;
}

string & bin(string & s, int d, int len=32){
	if (!d) return reverse(s, len);
	s.push_back((char)(d%2+(int)'0'));
	return bin(s, d/2, len);
}

int decimal(string binary, int i = 0){
	int tot = 0, l=binary.length();
	if (i < l){
		if (binary[l-1-i] == '1')
			tot = pow(2, i);
		return tot + decimal(binary, ++i);
	}
	return tot;
}

class address{
public:
	int tag, index, /*blockoffset,*/ byteoffset;

	address():tag(0), index(0), /*blockoffset(0),*/ byteoffset(0){}
	
	void setter(const int & addr, const int & setbits, const int & tagbits, /*const int & blockoffbits,*/ const int & byteoffbits, const int & addressbits){
		
		string s="";
		bin(s, addr);

		tag=decimal(s.substr(0,tagbits));
		index=decimal(s.substr(tagbits, setbits));
		//blockoffset=decimal(s.substr(tagbits+setbits, blockoffbits));
		byteoffset=decimal(s.substr(tagbits+setbits/*+blockoffbits*/));
	}

	~address(){}
};
