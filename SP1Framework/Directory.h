#pragma once
#include <windows.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

class Directory
{
private:
	std::vector<std::wstring> FileList;
	const std::wstring filepath;
	const std::wstring filetype;
	std::wstring searchpath;
public:
	Directory(const wchar_t* filepath, const wchar_t* searchpattern);
	~Directory();
	int size() const;
	bool update();
	std::wstring path() const;
	std::wstring operator[](int index);
};