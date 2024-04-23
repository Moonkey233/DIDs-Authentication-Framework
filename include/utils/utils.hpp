//工具类

#ifndef DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP
#define DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP

#include "string"
#include "cmath"
#include "vector"

class UTILS {
public:
	static bool isInteger(const std::string &str); //判断字符串为整数可带+-
	static bool isPrime(const long long &number); //快速大素数判断 Miller Rabin Test
	static unsigned long long sundaySearch(const std::string &text, const std::string &pattern); //单模式串匹配Sunday算法
	static std::string &replace(std::string mainStr, const std::string &subStr, const std::string &replaceStr, const unsigned long long &num = -1); //快速字符串替换
	static void swapNumber(long long &a, long long &b); //快速位运算交换两数
	static long long abs(const long long &n); //快速位运算绝对值
	static bool isEven(const long long &n); //快速位运算判断偶数
	static long long gcd(long long a, long long b); //快速最大公因数
	static long long extendedGCD(const long long &a, const long long &b, long long &x, long long &y); //拓展欧几里得算法
	static long long lcm(const long long &a, const long long &b); //快速最小公倍数
	static long long modInverse(int a, int mod); //求乘法逆元

protected:
	static long long quickMultiply(long long a, long long b, const long long &mod); //快速乘
	static long long quickPower(long long a, long long n, const long long &mod); //快速幂

};

inline bool UTILS::isInteger(const std::string &str) {
	char sign = str[0];
	unsigned long long i, len = str.length();
	if (sign < '0' || sign > '9') if (sign != '+' && sign != '-') return false;
	for (i = 1; i < len; ++i) if (str[i] < '0' || str[i] > '9') return false;
	return true;
}

inline long long UTILS::quickMultiply(long long a, long long b, const long long &mod) {
	a %= mod;
	b %= mod;
	long long res = 0;
	while (b > 0) {
		if (b & 1) res = (res + a) % mod;
		a = (a * 2) % mod;
		b >>= 1;
	}
	return res;
}

inline long long UTILS::quickPower(long long a, long long n, const long long &mod) {
	long long res = 1;
	while (n) {
		if (n & 1) res = quickMultiply(res, a, mod);
		a = quickMultiply(a, a, mod);
		n >>= 1;
	}
	return res;
}

inline bool UTILS::isPrime(const long long &number) {
//	if (number <= 3 || number % 2 == 0) return number == 2 || number == 3;
//	long long t = number % 6;
//	if (t != 1 && t != 5) return false;
//	long long sqrtN = std::floor(std::sqrt(number));
//	for (long long i = 5; i <= sqrtN; i += 6)
//		if (number % i == 0 || number % (i + 2) == 0) return false;
//	return true;

	if (number < 3 || number % 2 == 0) return number == 2;
	long long u = number - 1, t = 0;
	while (u % 2 == 0) u /= 2, ++t;
	long long ud[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};	for (long long a: ud) {
		long long v = quickPower(a, u, number);
		if (v == 1 || v == number - 1 || v == 0) continue;
		for (long long j = 1; j <= t; j++) {
			v = quickMultiply(v, v, number);
			if (v == number - 1 && j != t) {
				v = 1;
				break;
			}
			if (v == 1) return false;
		}
		if (v != 1) return false;
	}
	return true;
}

inline unsigned long long UTILS::sundaySearch(const std::string &text, const std::string &pattern) {
//	unsigned long long textLength = text.length(), patternLength = pattern.length();
//	if (patternLength == 0) return 0;
//	std::vector<long long> nextval(patternLength, 0);
//	nextval[0] = -1;
//	long long k = -1;
//	for (unsigned long long j = 1; j < patternLength; j++) {
//		while (k >= 0 && pattern[j] != pattern[k + 1]) k = nextval[k];
//		if (pattern[j] == pattern[k + 1]) k++;
//		nextval[j] = k;
//	}
//	long long i = 0, j = -1;
//	while (i < textLength) {
//		while (j >= 0 && pattern[j + 1] != text[i]) j = nextval[j];
//		if (pattern[j + 1] == text[i]) j++;
//		if (j == patternLength - 1) return i - j;
//		i++;
//	}
//	return -1;

	unsigned long long textLength = text.length(), patternLength = pattern.length();
	if (patternLength == 0) return 0;
	std::vector<unsigned long long> shift(256, patternLength + 1);
	for (int i = 0; i < patternLength; ++i)
		shift[static_cast<unsigned char>(pattern[i])] = patternLength - i;
	unsigned long long i = 0;
	while (i <= textLength - patternLength) {
		long long j = 0;
		while (j < patternLength && text[i + j] == pattern[j]) ++j;
		if (j == patternLength) return i;
		else i += shift[static_cast<unsigned char>(text[i + patternLength])];
	}
	return -1;
}

inline std::string &UTILS::replace(std::string mainStr, const std::string &subStr, const std::string &replaceStr, const unsigned long long &num) {

}

inline void UTILS::swapNumber(long long &a, long long &b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

inline long long UTILS::abs(const long long &n) {
	return n < 0 ? ~n + 1 : n;
}

inline bool UTILS::isEven(const long long &n) {
	return (n & 1) == 0;
}

inline long long UTILS::gcd(long long a, long long b) {
	int aTimes = 0, bTimes = 0;
	while (a % 2 == 0) {
		a >>= 1;
		aTimes++;
	}
	while (b % 2 == 0) {
		b >>= 1;
		bTimes++;
	}
	for (;;) {
		while (a % 2 == 0)
			a >>= 1;
		while (b % 2 == 0)
			b >>= 1;
		if (a == b) break;
		if (a < b) swapNumber(a, b);
		a -= b;
	}
	return a << (aTimes < bTimes ? aTimes : bTimes);
}

inline long long UTILS::extendedGCD(const long long &a, const long long &b, long long &x, long long &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long d = extendedGCD(b, a % b, y, x);
	y -= (a / b) * x;
	return d;
}

inline long long UTILS::modInverse(int a, int m) {
	long long x, y;
	long long gcd = extendedGCD(a, m, x, y);
	return (x % m + m) % m;
}

inline long long UTILS::lcm(const long long &a, const long long &b) {
	return a / gcd(a, b) * b;
}

#endif //DIDS_AUTHENTICATION_FRAMEWORK_UTILS_HPP
