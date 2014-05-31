/*
 * MixFileHandler.hpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef MIXFILEHANDLER_HPP_
#define MIXFILEHANDLER_HPP_

#include <string>
#include <map>
#include <memory>
//#include <fstream>
#include "../RawFileSystem.hpp"
#include "../../MixFile/MixFile.hpp"

class MIXManager {
public:
	static MIXManager* getManager();

	void assign(RawFileSystem* _rawSystem);

	void cache(const std::string& _mixName);

	int convertToID(std::string fileName);

	MixFile* get(const std::string& _mixName);

	bool inAMix(const std::string& fileName);

	std::string getName(const std::string& fileName);

	/*
		@param fileName The name of the file to extract
		@param mixName If given, the name of the mix to extract the file from
	*/
	bool extract(const std::string& fileName, const std::string& mixName = "");

//=====================================

	BinaryReader* getReader(const std::string& fileName);
	__int32 getOffsetForFile(const std::string& fileName);
	int getSizeForFile(const std::string& fileName);

private:
	static MIXManager* manager;
	MIXManager();

	RawFileSystem* rawSystem;
	//std::map<std::string, std::unique_ptr<MixFile>> mixFiles;
	std::vector<std::unique_ptr<MixFile>> mixFiles;
	
};

#endif /* MIXFILEHANDLER_HPP_ */
