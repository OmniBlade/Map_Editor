#pragma once

#include <string>
#include <vector>

class StartupLoader
{
public:
	StartupLoader();
//---- MIX LOADING
	/* Function to call when initiating MIXes, scoops through the directory for .mix files */
	void initiateMIX();
	/* Finds all default game mixes in the directory that should be present (like ra2(md).mix) */
	void findRootGameMIX(std::vector<std::string>& filesVector);
	/* Finds all default game mixes in the directory or in other mixes (like generic.mix, mix files normally inside ra2(md).mix) */
	void findSubGameMIX();
	/* Finds all expand mixes in the directory */
	void findExpandMIX(std::vector<std::string>& filesVector);
	/* Finds all ecache* and elocal* mixes in the directory */
	void findEcacheMIX(std::vector<std::string>& filesVector);
	/* Testcode - Checks whether the file exists in the root */
	bool checkMixFileInRoot(const std::string& fileName);
	/* Testcode - Checks whether a file exists in any mix */
	bool findFileInMix(const std::string& fileName);
	/* Returns a list of all sub game mixes (like local.mix) */
	std::vector<std::string> getMainMixes();
	std::vector<std::string> getSubMixes(bool missionDisk = false);
	std::vector<std::string> getExpandMixes();
	std::vector<std::string> getEcacheMixes();

//---- INI LOADING
	/* Function to call when initiating initial INI files. This excludes map mods (duh) */
	void initiateINI();
	/* Looks for all INI files listed and tries to locate them in the root or MIX files */
	void findINIFiles();
	/* Returns a list of all Yuri's Revenge INI files */
	std::vector<std::string> getIniNames();

	bool checkIniInRoot(const std::string& fileName);

private:
	std::vector<std::string> toProcessINIFileNames;
	std::vector<std::string> iniFilenames;
	std::vector<std::string> toProcessMixFileNames;
	std::vector<std::string> mixFilenames;
};

