#pragma once
#include <string>
#include <vector>

class INISection;

std::vector<byte> base64_decodeSection(INISection* section);
std::string base64_encode(unsigned char const*, unsigned int len);
std::vector<byte> base64_decode(std::string const& s);
