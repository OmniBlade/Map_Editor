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

	/*
		Returns the entire list of processed MIX files
		@return The list of MIX files
	*/
	std::vector<MixFile*>* getMixFiles();
	/*
		Converts the given file name to an ID so it can be looked up in a MIX file
		Part of XCC code
		@param fileName The name of the file to convert to an ID
		@return The converted filename as ID
	*/
	int convertNameToID(std::string fileName);

	/*
		Gets a MIX by its name and returns the pointer to it
		@param _mixName The name of the MIX file
		@return The pointer to the MIX
	*/
	MixFile* getMixByName(const std::string& _mixName);
	/*
		Checks whether a file exists inside the MIX files
		@param fileName The name of the file to check
	*/
	bool checkFileInMixes(const std::string& fileName);
	/*
		Returns the name of the MIX where the file was found in
		@param fileName The file to look for inside the MIX files
		@return The name of the first MIX that has the file in it
	*/
	std::string getMixNameOfFile(const std::string& fileName);

	/*
		Testcode - Extracts a file from the first MIX it is in
		@param fileName The file to extract
	*/
	void extractFileFromMix(const std::string& fileName);
	/*
		Returns the BinaryReader instance from the MIX where the file is in
		@param fileName The name of the file to look for
	*/
	BinaryReader* getReaderFromMIX(const std::string& fileName);
	void dumpMIXNames();

private:
//	BinaryReader* mixReader;
	std::string currentMixPath;
	std::string currentMixName;
	MixFile* currentMix;
	std::vector<MixFile*> mixFiles;
};

#endif /* MIXFILEHANDLER_HPP_ */
