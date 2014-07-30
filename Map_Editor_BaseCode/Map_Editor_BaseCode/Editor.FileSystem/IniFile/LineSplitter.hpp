/*
 * LineSplitter.hpp
 *
 *  Created on: 3 dec. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef LINESPLITTER_HPP_
#define LINESPLITTER_HPP_

#include <vector>

class LineSplitter {
public:
	LineSplitter(const std::string& _line);
	void discard();
	bool pop(std::string& out);
	const std::string& pop_string();
	const std::string& peek_string();
	const std::string& peekFromIndex_string(unsigned int index);
	bool pop(int& out);
	int pop_int();
	int peek_int();
	int peekFromIndex_int(unsigned int index);
	bool pop(bool& out);
	bool pop_bool();
	bool peek_bool();
	bool peekFromIndex_bool(unsigned int index);
	bool pop(double out);
	double pop_double();
	double peek_double();
	double peekFromIndex_double(unsigned int index);

	unsigned int size() const;
	bool empty() const;
	std::vector<std::string> getParamVector() const;
	void dumpContent();
	bool exists(const std::string& item);

private:
	unsigned int index;
	std::vector<std::string> paramVector;	// paramVector = the vector of all parameters splitted
};

#endif /* LINESPLITTER_HPP_ */
