#include "../include/crypto/ecc.hpp"
#include "../include/utils/utils.hpp"
#include "string"
#include "ctime"

int main() {

//	std::string s = "121324354646";
//	char s[60] = "+123456373465434568765434568765436";
	long long n = 21;
	int i = 0;
	if(UTILS::isPrime(n)) std::cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	std::cout<<std::clock()<<endl;
	while (++i < 100000000){
		UTILS::isPrime(n);
//		if(UTILS::isPrime(n)) std::cout<<"YES"<<endl;
//		else cout<<"NO"<<endl;
	}
	std::cout<<std::clock()<<endl;

	return 0;
}
