cmake_minimum_required(VERSION 3.24)
project(DIDs_Authentication_Framework)

set(CMAKE_CXX_STANDARD 17)

add_executable(DIDs_Authentication_Framework src/main.cpp include/crypto/ecc.hpp src/crypto/ecc.cpp include/utils/utils.hpp include/bigint/bigInt.hpp src/bigint/bigInt.cpp)