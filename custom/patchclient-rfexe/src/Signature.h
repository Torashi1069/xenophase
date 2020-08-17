#pragma once
#include <vector>


class Signature
{
public:
	static bool Sign(const char* pem_privkey, const std::vector<char>& data, std::vector<char>& out_signature);
	static bool Verify(const char* pem_pubkey, const std::vector<char>& data, const std::vector<char>& signature);
};
