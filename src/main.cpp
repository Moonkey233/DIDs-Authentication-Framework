#include "../include/crypto/ecc.hpp"
#include "../include/utils/utils.hpp"

int main() {
	std::string text = "Hello, World!";
	std::string pattern = "Worrld";

	unsigned long long result = UTILS::sundaySearch(text, pattern);

	if (result != -1) {
		std::cout << "Pattern found at position: " << result << std::endl;
	} else {
		std::cout << "Pattern not found in the text." << std::endl;
	}
	return 0;
}
