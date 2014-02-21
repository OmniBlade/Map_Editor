/*
 * MixFile.hpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include <string>
#include <vector>
#include "../../Reading/BinaryReader.hpp"

#ifndef MIXFILE_HPP_
#define MIXFILE_HPP_

class MixFile {
public:
	struct t_mix_header
	{
		__int16 files = 0;
		__int32 size = 0;
	} header;

	struct t_mix_index_header
	{
		__int32 id;
		__int32 offset;
		__int32 size;
	};

	enum flags : unsigned int 
	{
		Checksum = 0x00010000,
		Encrypted = 0x00020000,
	};

	MixFile(MixFile* _parent, const std::string& _mixName, int fileID);
	MixFile(const std::string& _mixName, MixFile* _parent = nullptr, int fileID = 0);
	void handleHeader();
	bool checkFileExistance(__int32 fileID);
	int getAFileOffset(__int32 fileID);
	std::vector<byte> getFileByID(__int32 fileID);
	void determineMixReader();
	void dumpIndex();

	void readTDHeader(unsigned short fileCount);
	void readRAHeader();

	std::vector<t_mix_index_header> mixIndex;
	std::string mixName;
	/* if parent */
	BinaryReader mixReader;
	/* if child */
	BinaryReader* aMixReader;
	MixFile* parent = nullptr;
	int startingOffset = 0;
};

#endif /* MIXFILE_HPP_ */
