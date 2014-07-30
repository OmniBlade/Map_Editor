#include "stdafx.h"
#include "ConfigFile.hpp"


ConfigFile::ConfigFile(const std::string& name, const std::string& path, const std::string& installDir, bool enc)
	:Name(name), Path(path), InstallDir(installDir), IsEncTypeConfig(enc)
{

}


