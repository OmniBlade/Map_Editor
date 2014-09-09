#include "stdafx.h"
#include "TextReader.h"

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
	textBytes.resize(size + 1);
	// Read the entire fucking file!
	textReader->readBlock(&textBytes[0], textBytes.size());
}

std::string TextReader::readTextLine()
{
	if (checkEOF())
	{
		index = textBytes.size();
		return std::string();
	}

	auto begin = &this->textBytes[this->index];
	if (auto end = strpbrk(begin, "\n\r")) 
	{
		auto length = end - begin;
		this->index += length;
		while (this->textBytes[this->index] == '\r' || this->textBytes[this->index] == '\n')
		{
			++this->index;
		}
		return std::string(begin, end);
	}

	index = textBytes.size();
	return std::string();
}