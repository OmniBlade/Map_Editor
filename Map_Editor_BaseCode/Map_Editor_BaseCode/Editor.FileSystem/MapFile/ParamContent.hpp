#pragma once
#include <vector>

class ParamContent
{
public:
	ParamContent();
	
	std::vector<std::string> get(int paramID, bool isForScript = false);
	void fillVector(std::vector<std::string>& paramVector, int paramID);

};

