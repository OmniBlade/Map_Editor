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
	/* Finds all expand mixes in the directory */
	void findExpandMIX(std::vector<std::string>& filesVector);
	/* Finds all ecache* and elocal* mixes in the directory */
	void findEcacheMIX(std::vector<std::string>& filesVector);
	/* Testcode - Checks whether the file exists in the root */
	bool checkMixFileInRoot(const std::string& fileName);
	/* Returns a list of all sub game mixes (like local.mix) */
	std::vector<std::string> getMainMixes();
	std::vector<std::string> getSubMixes();
	std::vector<std::string> getExpandMixes();
	std::vector<std::string> getEcacheMixes();

//---- INI LOADING
	/* Function to call when initiating initial INI files. This excludes map mods (duh) */
	void initiateINI();
	/* Returns a list of all Yuri's Revenge INI files */
	std::vector<std::string> getIniNames();

	bool checkIniInRoot(const std::string& fileName);

//---- CSF LOADING
	/* Function to call when initiating CSF files */
	void initiateCSF();
	/* Looks for all CSF files listed and tries to locate them in the root or MIX files */
	void findCSFFiles(std::vector<std::string>& list);

	bool checkCsfInRoot(const std::string& fileName);

private:
	std::vector<std::string> toProcessINIFileNames;
	std::vector<std::string> iniFilenames;
	std::vector<std::string> toProcessMixFileNames;
	std::vector<std::string> mixFilenames;
	std::vector<std::string> csfFilenames;
};

