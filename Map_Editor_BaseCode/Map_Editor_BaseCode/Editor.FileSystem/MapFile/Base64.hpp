#pragma once

#include "../INIFile/INISection.hpp"

class Base64 {
public:
	static size_t decode(byte* inout, size_t len);
	static size_t decode(byte const*, byte*, size_t);
	static byte* decode(INISection&, size_t&);

protected:
	Base64();
	~Base64();
	static byte alphabet[64];
	static byte lookup[256];

	static unsigned int decode64Chunk(byte const*, byte*);
	static void initialiseTable();
};

