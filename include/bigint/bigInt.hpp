#ifndef DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP
#define DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP

#include "cmath"
#include "string"

class BigInt{
public:
	explicit BigInt();
	explicit BigInt(const BigInt&);
	explicit BigInt(const int&);
	explicit BigInt(const std::string&);
};



#endif //DIDS_AUTHENTICATION_FRAMEWORK_BIGINT_HPP
