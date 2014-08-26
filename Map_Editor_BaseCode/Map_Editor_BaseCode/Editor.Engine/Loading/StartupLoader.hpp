#pragma once

#include <string>
#include <vector>

class StartupLoader
{
public:
	StartupLoader();
//---- GENERIC
	std::vector<std::string> getFilesWithExtension(const std::string& ext);
	bool inRoot(const std::string& fileName, const std::vector<std::string>& filenames);

//---- MIX LOADING
	/* Function to call when initiating MIXes, scoops through the directory for .mix files */
	void initiateMIX();
	/* Finds all expand mixes in the directory */
	void findExpandMIX(std::vector<std::string>& filesVector);
	/* Finds all ecache* and elocal* mixes in the directory */
	void findEcacheMIX(std::vector<std::string>& filesVector);
	/* Returns a list of all sub game mixes (like local.mix) */
	std::vector<std::string> getMainMixes();
	std::vector<std::string> getSubMixes();
	std::vector<std::string> getExpandMixes(const std::vector<std::string>& mixFilenames);
	std::vector<std::string> getEcacheMixes();

//---- INI LOADING
	/* Function to call when initiating initial INI files. This excludes map mods (duh) */
	void initiateINI();
	/* Returns a list of all Yuri's Revenge INI files */
	std::vector<std::string> getIniNames();

//---- CSF LOADING
	/* Function to call when initiating CSF files */
	void initiateCSF();
	/* Looks for all CSF files listed and tries to locate them in the root or MIX files */
	void findCSFFiles(std::vector<std::string>& list, const std::vector<std::string>& csfFilenames);

private:
	std::vector<std::string> toProcessINIFileNames;
	std::vector<std::string> iniFilenames;
	std::vector<std::string> toProcessMixFileNames;
	std::vector<std::string> mixFilenames;
	std::vector<std::string> csfFilenames;
};

