#include "stdafx.h"
#include "Log.hpp"
#include "Config.hpp"
#include <iostream>
#include <fstream>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include <Windows.h>

#pragma warning(disable : 4996) // Disable time ERRORS

/* static */ std::vector<std::wstring> Log::debugLines;
/* static */ std::vector<std::wstring> Log::logLines;
/* static */ std::vector<std::wstring> Log::errorLines;
/* static */ std::vector<std::wstring> Log::warningLines;
/* static */ std::wofstream Log::logFile;
/* static */ std::wofstream Log::debugFile;
/* static */ std::wofstream Log::debugTimeFile;
/* static */ std::wofstream Log::logTimeFile;
/* static */ int Log::atLogLine = 0;
/* static */ int Log::atDebugLine = 0;
/* static */ int Log::lastError = 0;
/* static */ int Log::errorCount = 0;
/* static */ int Log::lastWarning = 0;
/* static */ int Log::warningCount = 0;
/* static */ bool Log::dumpInConsole = true;
/* static */ Log::LogType types = Log::LogType::EMPTY;
/* static */ Log::DebugType typesDebug = Log::DebugType::EMPTY_D;
/* static */ std::chrono::time_point<std::chrono::system_clock> Log::startTime;
/* static */ std::chrono::time_point<std::chrono::system_clock> Log::timer;
/* static */ std::string Log::logFolder = Config::backSlash + "Logging";

/* static */ void Log::cout(const std::wstring& line)
{
	std::wcout << line << std::endl;
}

/* static */ void Log::line(const std::wstring& line /* = "" */, LogType type /* = EMPTY */)
{
	switch (type)
	{
	case INFO:
		logLines.push_back(L"INFO     - " + line);
		break;
	case WARNING:
		logLines.push_back(L"WARNING  - " + line);
		warningCount++;
		break;
	case ERRORS:
		logLines.push_back(L"ERROR	 - " + line);
		break;
	case ERROR_BUFFER:
		errorLines.push_back(line);
		errorCount++;
		break;
	case WARNING_BUFFER:
		warningLines.push_back(line);
		warningCount++;
		break;
	case CRITICAL:
		logLines.push_back(L"CRITICAL - " + line);
		break;
	case UNKNOWN:
		logLines.push_back(L"UNKNOWN  - " + line);
		break;
	case EXTRAS:
		logLines.push_back(L"           " + line);
		break;
	case EMPTY:
		logLines.push_back(L"");
		break;
	}
}

/*static */ void Log::note(const std::wstring& line /* = "" */, DebugType type /* = EMPTY_D */)
{
	if (!Config::enableDebug) return; //GTFO out of my debug function

	switch (type)
	{
	case DEBUG:
		debugLines.push_back(L"[" + getFormalTime() + L"] - " + line);
		break;
	case EXTRA:
		debugLines.push_back(L"             " + line);
		break;
	default:
	case EMPTY_D:
		debugLines.push_back(L"");
		break;
	}
	if (dumpInConsole)
		cout(debugLines.back());
	write();
}

std::wstring Log::toWString(const std::string& line)
{
	std::wstring returnString;
	returnString.assign(line.begin(), line.end());
	
	return returnString;
}

void Log::finishErrorRound()
{
	if (errorCount == lastError)
	{
		Log::line(L"No errors were found.", Log::EXTRAS);
	}
	else if (errorCount > lastError)
	{
		Log::line(Log::toWString(errorCount - lastError) + L" errors were found.", Log::EXTRAS);
	}
	else if (errorCount < lastError)
	{
		Log::line(Log::toWString(errorCount - lastError) + L" errors were found?", Log::EXTRAS);
	}

	for (unsigned int i = lastError; i < errorLines.size(); ++i)
	{
		Log::line(errorLines[i], Log::ERRORS);
	}
	errorLines.empty();

	if (errorCount > lastError)
	{
		Log::line();
	}

	lastError = errorCount;
	write(); // Make sure shit ends up in the log file inb4 crash
}

void Log::finishWarningRound()
{
	if (warningCount == lastWarning)
	{
		Log::line("No warnings were found.", Log::EXTRAS);
	}
	else if (warningCount > lastWarning)
	{
		Log::line(Log::toWString(warningCount - lastWarning) + L" warnings were found.", Log::EXTRAS);
	}
	else if (warningCount < lastWarning)
	{
		Log::line(Log::toWString(warningCount - lastWarning) + L" warnings were found?", Log::EXTRAS);
	}

	for (unsigned int i = lastWarning; i < warningLines.size(); ++i)
	{
		Log::line(warningLines[i], Log::WARNING);
	}
	warningLines.empty();

	lastWarning = warningCount;
	write(); // Make sure shit ends up in the log file inb4 crash
}

/* static */ std::string Log::getFormalDateTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;

	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d - %H:%M:%S");

	return ss.str();
}

/* static */ std::wstring Log::getFormalTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;

	ss << std::put_time(std::localtime(&in_time_t), "%H:%M:%S");

	std::string& tempStr = ss.str();
	std::wstring wTempStr = std::wstring(tempStr.begin(), tempStr.end());

	return wTempStr;
}

/* static */ std::string Log::getSessionTime()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed_seconds = now - startTime;
	int seconds_int = (int) elapsed_seconds.count();

	long hours = (seconds_int / 60 / 60) % 24;
	long minutes = (seconds_int / 60) % 60;
	long seconds = seconds_int % 60;

	std::stringstream ss;
	ss << hours << ':';

	if (minutes < 10) // Tidy formatting like 01:21:08 instead of 1:21:8
		ss << '0';
	ss << minutes << ':';

	if (seconds < 10)
		ss << '0';
	ss << seconds;
		
	return ss.str();
}

void Log::timerStart()
{
	timer = std::chrono::system_clock::now();
}

std::string Log::getTimerValue()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed_seconds = now - timer;
	
	int seconds_int = (int)elapsed_seconds.count();
	int milliseconds_int = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - timer).count();

	long hours = (seconds_int / 60 / 60) % 24;
	long minutes = (seconds_int / 60) % 60;
	long seconds = seconds_int % 60;
	long milliseconds = milliseconds_int % 1000;

	std::stringstream ss;
	ss << hours << ':';

	if (minutes < 10) // Tidy formatting like 01:21:08 instead of 1:21:8
		ss << '0';
	ss << minutes << ':';

	if (seconds < 10)
		ss << '0';
	ss << seconds << '.';

	if (milliseconds < 10)
		ss << '0';
	ss << milliseconds;

	return ss.str();
}

/* static */ std::string Log::getDateTimeForFile()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	
	ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d-%H%M%S"); //Ares style, fuckyea

	return ss.str();
}

/* static */ void Log::openDebug()
{
	/* Check if "Logging" folder exists */
	std::string dirName = Config::editorRoot + Config::backSlash + "Logging";
	std::wstring dirNameW(dirName.begin(), dirName.end());
	DWORD ftyp = GetFileAttributesA(dirName.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY == 0 || ftyp == INVALID_FILE_ATTRIBUTES)
	{
		std::cout << "Logging directory doesn't exist, creating now..." << std::endl;
		if (CreateDirectory(dirNameW.c_str(), NULL))
			note("Creating 'Logging' directory successful!", DEBUG);
		else
			std::cout << "Creating 'Logging' directory in editor root failed, are you running this as administrator?" << std::endl;
	}
	else
		std::cout << "'Logging' exists in the editor root!" << std::endl;

	startTime = std::chrono::system_clock::now();
	std::string& dateTime = getDateTimeForFile();

	if (!Config::enableDebug) return;

	std::string debugName = Config::editorRoot + logFolder + Config::backSlash + "debug.log";
	std::string debugNameNew = Config::editorRoot + logFolder + Config::backSlash + "debug." + dateTime + ".log";

	debugFile.open(debugName);
	debugTimeFile.open(debugNameNew);
}

/* static */ void Log::openOutput()
{
	std::string& dateTime = getDateTimeForFile();
	
	std::string outputName = Config::editorRoot + logFolder + Config::backSlash + "output.log";
	std::string outputNameNew = Config::editorRoot + logFolder + Config::backSlash + "output." + dateTime + '.' + Config::mapName + ".log";
	//std::string outputNameNew = Config::editorRoot + logFolder + Config::backSlash + "output." + dateTime + ".log";

	logFile.open(outputNameNew);
	logTimeFile.open(outputName);
}

/* static */ void Log::write()
{
	for (unsigned int i = atLogLine; i < logLines.size(); ++i)
	{
		logFile << logLines[i] << '\n';
		logTimeFile << logLines[i] << '\n';
	}

	for (unsigned int i = atDebugLine; i < debugLines.size(); ++i)
	{
		debugFile << debugLines[i] << '\n';
		debugTimeFile << debugLines[i] << '\n'; // I so want to get shot in the head by some person now that I'm doing this
	}

	logFile.flush();
	logTimeFile.flush();
	atLogLine = logLines.size();

	if (!Config::enableDebug) return;

	debugFile.flush();
	debugTimeFile.flush();
	atDebugLine = debugLines.size();
}

/* static */ void Log::closeDebug()
{
	if (!Config::enableDebug) return;
	debugFile.close();
	debugTimeFile.close();
}

/* static */ void Log::closeOutput()
{
	logFile.close();
	logTimeFile.close();
}

//Backup for the CopyFile stuff which is probably obsolete now
/*
std::wstring outputNameW(outputName.begin(), outputName.end());
std::wstring outputNameNewW(outputNameNew.begin(), outputNameNew.end());
if (CopyFile(outputNameW.c_str(), outputNameNewW.c_str(), true) == 0)
std::cout << "Copying failed, perhaps the file 'output.log' doesn't exist?" << std::endl;

std::wstring debugNameW(debugName.begin(), debugName.end());
std::wstring debugNameNewW(debugNameNew.begin(), debugNameNew.end());
if (CopyFile(debugNameW.c_str(), debugNameNewW.c_str(), true) == 0)
std::cout << "Copying failed, perhaps the file 'debug.log' doesn't exist?" << std::endl;
*/