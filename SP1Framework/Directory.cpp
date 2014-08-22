#include "Directory.h"

Directory::Directory(const wchar_t* filepath, const wchar_t* searchpattern)
	:
filepath(filepath),
filetype(searchpattern)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	searchpath.append(filepath);
	searchpath.append(searchpattern);
	hFind = FindFirstFile((searchpath.c_str()), &FindData);
	int index;
	do
	{
		std::wstring buffer = FindData.cFileName;
		FileList.push_back(buffer);
	}while (FindNextFile(hFind, &FindData) > 0);
}

Directory::~Directory()
{
}

int Directory::size() const
{
	return FileList.size();
}

bool Directory::update()
{
	FileList.clear();

	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	hFind = FindFirstFile((searchpath.c_str()), &FindData);
	int index;
	do
	{
		std::wstring buffer = FindData.cFileName;
		FileList.push_back(buffer);
	}while (FindNextFile(hFind, &FindData) > 0);
	return true;
}

std::wstring Directory::path() const
{
	return filepath;
}

std::wstring Directory::operator[](int index)
{
	return FileList[index];
}