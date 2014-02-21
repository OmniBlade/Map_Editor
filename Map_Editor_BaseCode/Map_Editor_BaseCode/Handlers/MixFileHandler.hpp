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
#include <vector>
#include <fstream>
#include "../Reading/BinaryReader.hpp"
#include "../FileSystem/MixFile/MixFile.hpp"

class MixFileHandler {
public:
	MixFileHandler();

	/*
	 * Creates a MixFile instance
	 * @param pathToMix The path to the mix file
	 */
	void createVirtualMix(const std::string& _mixName, const std::string& parentMixName = "");

	std::vector<MixFile*>* getMixFiles();
	int convertNameToID(std::string fileName);
	MixFile* getMixByName(const std::string& _mixName);
	bool checkFileInMixes(const std::string& fileName);
	std::string getMixNameOfFile(const std::string& fileName);
	void extractFileFromMix(const std::string fileName);
	void dumpMIXNames();

private:
//	BinaryReader* mixReader;
	std::string currentMixPath;
	std::string currentMixName;
	MixFile* currentMix;
	std::vector<MixFile*> mixFiles;
};

#endif /* MIXFILEHANDLER_HPP_ */
