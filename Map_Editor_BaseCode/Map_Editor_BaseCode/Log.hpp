#pragma once

#include <vector>
#include <string>
#include <chrono>

class Log
{
public:
	static enum LogType
	{
		DEBUG = 0,		// Information line for debug, prefix "[HH:MM:SS] - "
		INFO = 1,		// Information line, prefix "INFO - "
		WARNING = 2,	// Warning line, prefix "WARNING - "
		ERRORS = 3,		// ERRORS line, prefix "ERRORS - "
		CRITICAL = 4,	// Critical line, prefix "CRITICAL - "
		UNKNOWN = 5,	// Default/unknown line, prefix "UNKNOWN - "
		EMPTY = 6,		// Empty line, no prefix, used for spacing
		D_EMPTY = 7,	// Empty line for in debug, no prefix, used for spacing
	};
	Log::LogType types;

	/*
		Simply ships the line given to line() to console out
		@param line The line to put in the console
	*/
	static void cout(const std::string& line);

	/*
		Logs a line with the given type
		@param line The line to log
		@param type The type of log message (default UNKNOWN, see LogType enum)
	*/
	static void line(const std::string& line, LogType type = UNKNOWN);

	/*
		Converts the passed argument to a string and returns it
		@param value The value to convert to a string
	*/
	static std::string toString(int value);
	static std::string toString(float value);

	/*
		Get the date and time in a formal way like YYYY-mm-dd - HH:MM:SS 
		@return The current time and date as a string
	*/
	static std::string getFormalDateTime();

	/*
		Get the time in a formal way like HH:MM:SS
		@return The current time as a string
	*/
	static std::string getFormalTime();
	
	/*
		Get the time that's passed since the start of the program
		@return The time passed as a string
	*/
	static std::string getSessionTime();

	/*
		Allows you to measure the length of an operation, to start call timerStart,
		it initiates timer to the current time. Call getTimerValue any time to get the time passed
		since timer was initiated

		@return The time passed since timer was set to current time 
	*/
	static void timerStart();
	static std::string getTimerValue();
	
	/*
		Specific time format used to rename the log files for, format; YYYYmmdd-HHMMSS
		
		@return The time as a string
	*/
	static std::string getDateTimeForFile();

	/*
		Opens the output streamc of the log files, creates a file if it doesn't exist
	*/
	static void open();

	/*
		Writes all the current cached log lines to their respective files
		Replaces content if the log file isn't newly created by open() (which is quite a small chance because it's timed at seconds
	*/
	static void write();

	/*
		Closes the output streams of the log files
	*/
	static void close();

	static bool dumpInConsole;
	static int atLogLine;
	static int atDebugLine;

	static std::chrono::time_point<std::chrono::system_clock> startTime;
	static std::chrono::time_point<std::chrono::system_clock> timer;
	static std::string outputName;
	static std::string debugName;
	static std::string logFolder;

	static std::ofstream logFile, debugFile;
	static std::vector<std::string> debugLines;
	static std::vector<std::string> logLines;
};

