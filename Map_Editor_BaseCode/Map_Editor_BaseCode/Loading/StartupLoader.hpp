#pragma once

#include <string>
#include <vector>
#include "../Handlers/MixFileHandler.hpp"

class StartupLoader
{
public:
	StartupLoader(MixFileHandler* _mixHandler);
//---- MIX LOADING
	/* Function to call when initiating MIXes, scoops through the directory for .mix files */
	void initiateMIX();
	/* Finds all default game mixes in the directory that should be present (like ra2(md).mix) */
	void findRootGameMIX(const std::string missionDisk);
	/* Finds all default game mixes in the directory or in other mixes (like generic.mix, mix files normally inside ra2(md).mix) */
	void findSubGameMIX(const std::string missionDisk);
	/* Finds all expand mixes in the directory */
	void findExpandMIX(const std::string& expand, const std::string& missionDisk);
	/* Finds all ecache* and elocal* mixes in the directory */
	void findEcacheMIX(const std::string& elocal, const std::string& ecache);
	/* Testcode - Checks whether the file exists in the root */
	bool checkFileInRoot(const std::string& fileName);
	/* Testcode - Checks whether a file exists in any mix */
	bool findFileInMix(const std::string& fileName);

	/* Trivial */
	std::vector<std::string>* getExpandFiles();
	std::vector<std::string>* getEcacheFiles();
	std::vector<std::string>* getGameFiles();
	std::vector<std::string>  getMixNames(bool missionDisk = false);
//---- INI LOADING
	/* Function to call when initiating initial INI files. This excludes map mods (duh) */
	void initiateINI();

private:
	std::vector<std::string> modFileNames;
	std::vector<std::string> expandFileNames;
	std::vector<std::string> ecacheFileNames;
	std::vector<std::string> gameFileNames;
	std::vector<std::string> filenames;
	MixFileHandler* mixHandler;
};

