#pragma once
#include <string>
#include "gtest/gtest.h"
#include <fstream>


class ParsingInstrument 
{
public:	

	ParsingInstrument(std::string instrumentPath)
	{
		m_instrumentPath = instrumentPath;
		PrasingFile();
	}

	char** Instruments() 
	{
		return (char**)instruments;
	}

	int Size() 
	{
		return m_insLen;
	}

private:
	void PrasingFile()
	{
		if (m_instrumentPath == "\0")
			return;
		
		std::ifstream in;
		in.open(m_instrumentPath);
		char line[8] = {0};		
		while (in.getline(line, sizeof(line)))
		{
			instruments[m_insLen] = new char[8]();
			strcpy_s(instruments[m_insLen], 8, line);
			m_insLen++;
		}


	}
private:	
	// ��Լ����
	int m_insLen = 0;
	// ��Լ����
	char* instruments[680] = {};
	// ��Լ·��
	std::string m_instrumentPath = "";

	
};