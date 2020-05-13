#include <math.h>
#include <iostream>
//#include <char *.h>
using namespace std;

char * rev(char * s, int i){
	char temp;
	for(i;i<32;++i) s[i]='0';
	s[32]='\0';
	cout<<s<<endl;
	for(int i=0;i<32;++i){
		temp=s[i];
		s[i]=s[31-i];
		s[31-i]=temp;
	}
	cout<<s<<endl;
	return s;
}

char * bin(char * s, int d, int i=0){
	if (!d) return rev(s, i);
	s[i]=((char)(d%2+(int)'0'));
	return bin(s, d/2, i+1);
}

int decimal(char * binary, int i = 0){
	int tot = 0, l=sizeof(binary)-1;
	if (i < l){
		if (binary[l-1-i] == '1')
			tot = pow(2, i);
		return tot + decimal(binary, ++i);
	}
	return tot;
}
char * subarr(char * s, int start, int len){
	char * res=new char[len+1];
	for(int i=start;i<32 && i<start+len;++i) res[i-start]=s[i];
	res[len]='\0';
	return res;
}

class address{
public:
	int tag, index, /*blockoffset,*/ byteoffset;

	address():tag(0), index(0), /*blockoffset(0),*/ byteoffset(0){}
	
	void setter(const int & addr, const int & setbits, const int & tagbits, /*const int & blockoffbits,*/ const int & byteoffbits, const int & addressbits){
		
		char * s=new char[33];
		bin(s, addr);
		char * s1=subarr(s, 0, tagbits);
		char * s2=subarr(s, tagbits, setbits);
		char * s3=subarr(s, tagbits+setbits, byteoffbits/*+blockoffbits*/);
		cout<<s1<<' '<<s2<<' '<<s3<<'\n';
		tag=decimal(subarr(s, 0,tagbits));
		index=decimal(s2);
		//blockoffset=decimal(subarr(s, tagbits+setbits, blockoffbits));
		byteoffset=decimal(s3);
		cout<<tag<<' '<<index<<' '<<byteoffset<<endl;
		delete [] s3;
		delete [] s2;
		delete [] s1;
		delete [] s;
	}

	~address(){}
};
