#include "stdafx.h"
#include "TextReader.h"
#include <iostream>
#include "FileSystem.hpp"
#include "BinaryReader.hpp"

TextReader::TextReader(const FileProperties& props)
:textReader(props.reader)
{
	textReader->setOffset(props.offset);
	textReader->setSize(props.size);
	
	readEntireFile(props.size);
}

TextReader::TextReader(const std::vector<char>& bytes)
:textBytes(bytes)
{

}

void TextReader::readEntireFile(int size)
{
	// Allocating text buffer! + 1 byte for \0
	textBytes.resize((size + 1));
	// Read the entire fucking file!
	textReader->readBlock(&textBytes[0], size);
}

std::string TextReader::readTextLine()
{
	/*
	auto delim = data.find('\n', pos);
    std::string ret(data.substr(pos, delim))
    pos = (delim == std::string::npos) ? data.size() : delim + 1;
    if(!ret.empty() && (ret.back() == '\r')){
      ret.pop_back();
    }
    return std::move(ret);
  }
	*/

	if (checkEOF())
	{
		//std::cout << "EOF-1!" << std::endl;
		index = textBytes.size();
		return std::string();
	}

	auto begin = &this->textBytes[this->index];
	if (auto end = strpbrk(begin, "\n\r")) 
	{
		auto length = end - begin;

		this->index += length;

		if (checkEOF())
		{
			//std::cout << "EOF-1!" << std::endl;
			index = textBytes.size();
			return std::string();
		}

		while (this->textBytes.at(this->index) == '\r' || this->textBytes.at(this->index) == '\n')
		{
			++this->index;
		}

		return std::string(begin, end);
	}

	//std::cout << "EOF-2!" << std::endl;
	index = textBytes.size();
	return std::string();
}
