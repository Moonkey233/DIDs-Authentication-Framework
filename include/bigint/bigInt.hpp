#ifndef DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP
#define DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP

#include "cmath"
#include "string"

class BigInt{
public:
	explicit BigInt();
	explicit BigInt(const BigInt &n);
	explicit BigInt(const int &n);
	explicit BigInt(const std::string &n);
};



#endif //DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP
