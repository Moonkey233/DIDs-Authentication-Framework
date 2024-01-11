//工具类

#ifndef DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP
#define DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP

#include "string"
#include "cmath"

class UTILS{
public:
	static bool isInteger(const std::string &s); //判断字符串为整数可带+-
	static bool isPrime(const long long &n); //快速大素数判断
};

inline bool UTILS::isInteger(const std::string &s) {
	char sign = s[0];
	unsigned long long i, len = s.length();
	if (sign < '0' || sign > '9') if(sign != '+' && sign != '-') return false;
	for(i = 1; i < len; ++i) if (s[i] < '0' || s[i] > '9') return false;
	return true;
}

inline bool UTILS::isPrime(const long long &n) {
	if (n < 2) return false;
	if (n == 2 || n == 3) return true;
	long long t = n % 6;
	if (t != 1 && t != 5) return false;
	long long sqrtN = std::floor(std::sqrt(n));
	for(int i = 5; i < sqrtN; i += 6)
		if (n % i == 0 || n % (i + 2) == 0) return false;
	return true;
}

#endif //DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP
