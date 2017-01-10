#pragma once
#include <stdio.h>
#include <string.h>
#include "FileSystem.h"
#include <iostream>
#include <fstream>

//__CYGWIN__ is linux environment on windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
void FileSystem::MountDirectory(const std::string & directory, Item * curDir)
{
	Item* tempD;
	if (curDir->GetName() == directory) //Check if root
	{
		tempD = curDir;
	}
	else
	{
		tempD = new Directory(directory, curDir);
		static_cast<Directory*>(curDir)->m_Files.push_back(tempD); //add dir to parent (old root)
	}

	//curDir = tempD; //make new root

	WIN32_FIND_DATAA find_data;
	std::string path = (curDir->GetName() == directory) ? "" : (curDir->GetFullPath() + "/");//check if root, if no add full path
	auto handle = FindFirstFileA((path + directory + "/*").c_str(), &find_data); //get first file "."(is directory itself) to check if directory actually exists
	if (handle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Unmountable path: " << directory.c_str() << std::endl;
		return;
	}

	if (directory == "") std::cout << "Root is ready!" << std::endl;
	else std::cout << directory.c_str() << " is mounted!" << std::endl;
	//if directory is mountable, loop through items and stuff
	do
	{
		if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//bitwise flag checker(like enum)(elements example in class)
		{
			if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0)
			{
				continue; //if you don't do this it'll get stuck on these folders (it's only 2 files)
			}
			MountDirectory(find_data.cFileName, tempD); //only send filename because we want to level it in 1 root
		}
		else
		{
			static_cast<Directory*>(tempD)->m_Files.push_back(new File(find_data.cFileName, tempD));

		}
	} while (FindNextFileA(handle, &find_data) != 0);
}
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void FileSystem::MountDirectory(const std::string & directory, Item * curDir)
{
	Item* tempD;
	if (curDir->GetName() == directory) //Check if root
	{
		tempD = curDir;
	}
	else
	{
		tempD = new Directory(directory, curDir);
		static_cast<Directory*>(curDir)->m_Files.push_back(tempD); //add dir to parent (old root)
	}

	DIR *dPtr; //Directory pointer
	struct dirent * find_data;

	std::string path = (curDir->GetName() == directory) ? "" : (curDir->GetFullPath() + "/");//check if root, if no add full path
	dPtr = opendir((path + directory + "/*").c_str());
	if (dPtr == NULL)
	{
		std::cerr << "Unmountable path: " << directory.c_str() << std::endl;
		return;
	}

	if (directory == "") std::cout << "Root is ready!" << std::endl;
	else std::cout << directory.c_str() << " is mounted!" << std::endl;
	//if directory is mountable, loop through items and stuff
	do
	{
		struct stat statBuffer;
		stat((path + directory + "/" + find_data->d_name).c_str(), &statBuffer);
		if (S_ISDIR(statBuffer.st_mode) == 0)//error gives -1 with errno (but skip for now)
		{
			if (strcmp(find_data->d_name, ".") == 0 || strcmp(find_data->d_name, "..") == 0)
			{
				continue; //if you don't do this it'll get stuck on these folders (it's only 2 files)
			}
			MountDirectory(find_data->d_name, tempD); //only send filename because we want to level it in 1 root
		}
		else
		{
			static_cast<Directory*>(tempD)->m_Files.push_back(new File(find_data->d_name, tempD));

		}
	} while ((find_data = readdir(dPtr)) != NULL);
}
#endif


FileSystem::FileSystem()
{
}


FileSystem::~FileSystem()
{
}

void FileSystem::MountDirectory(const std::string & directory)//Avoiding making new variable for current dir
{
	m_Root = new Directory(directory, nullptr);
	MountDirectory(directory, m_Root);
}



void FileSystem::ListContent()//Feedback for testing
{
	ListContent(m_Root);
}

void FileSystem::ListContent(Item * folder)//Feedback for testing
{
	Directory * targetFolder = dynamic_cast<Directory*>(folder);
	if (targetFolder == nullptr) return;
	for (Item* item : targetFolder->m_Files)
	{
		Directory * temp = dynamic_cast<Directory*>(item);
		if (temp == nullptr)
			std::cout << item->GetFullPath() << std::endl;
		else
			ListContent(temp);
	}
	
}

File* FileSystem::GetFile(const std::string & filename) const
{
	return GetFile(filename,m_Root);
}

File* FileSystem::GetFile(const std::string & filename,Item* folder) const
{
	Directory * targetFolder = dynamic_cast<Directory*>(folder);
	if (targetFolder == nullptr) return nullptr;
	for (Item* item : targetFolder->m_Files)
	{
		if(item->GetName() == filename)
		{
			return static_cast<File*>(item);
		}
		else
		{
			Directory * temp = dynamic_cast<Directory*>(item);
			if (temp != nullptr)
			{
				File* f = GetFile(filename, temp);
				if (f != nullptr) return f;
			}
		}
	}
	return nullptr;
}

Directory* FileSystem::GetDirectory(const std::string & dname) const
{
	return GetDirectory(dname, m_Root);
}

Directory* FileSystem::GetDirectory(const std::string & dname, Item* folder) const
{
	Directory * targetFolder = dynamic_cast<Directory*>(folder);
	if (targetFolder == nullptr) return nullptr;
	for (Item* item : targetFolder->m_Files)
	{
		if (item->GetName() == dname)
		{
			return static_cast<Directory*>(item);
		}
		else
		{
			Directory * temp = dynamic_cast<Directory*>(item);
			if (temp != nullptr)
			{
				Directory* f = GetDirectory(dname, temp);
				if (f != nullptr) return f;
			}
		}
	}
	return nullptr;
}
void FileSystem::GetFilesVec(std::vector<File*>& file_table) const
{
	GetFilesVec(file_table, m_Root);
}

void FileSystem::GetFilesVec(std::vector<File*>& file_table, const std::string& extension) const
{
	GetFilesVec(file_table, m_Root, extension);
}

void FileSystem::GetFilesVec(std::vector<File*>& file_table, Item* folder) const
{
	GetFilesVec(file_table, folder, "");
}

void FileSystem::GetFilesVec(std::vector<File*>& file_table, Item* folder, const std::string& extension) const
{
	Directory* targetFolder = dynamic_cast<Directory*>(folder);
	if (targetFolder == nullptr) return;
	for (Item* item : targetFolder->m_Files)
	{
		Directory* temp = dynamic_cast<Directory*>(item);
		if (temp == nullptr)//weed out folders
		{
			if (extension != "")//for find all with extension
			{
				size_t pos = item->GetName().find_last_of(".");
				std::string sub = item->GetName().substr(pos);
				if (item->GetName().substr(pos) == extension) {
					file_table.push_back(static_cast<File*>(item));
					std::cout << item->GetName() << std::endl;
				}
			}
			else//just add, #NoFilter
			{
				file_table.push_back(static_cast<File*>(item));
				std::cout << item->GetName() << std::endl;
			}
		}
		else//go into folders
			GetFilesVec(file_table, temp, extension);
	}
}

std::string FileSystem::GetPhysicalFilePath(const std::string& filename) const
{
	File * targetFile = GetFile(filename);
	if (targetFile == nullptr) return ("Unable to find " + filename);
	return targetFile->GetFullPath();
}

void FileSystem::GetFilesInDirectory(std::vector<File*>& file_table, const std::string& directory) const
{
	Directory * targetDirectory = GetDirectory(directory);
	//if (targetDirectory == nullptr) return;
	for(Item* item : targetDirectory->m_Files)
	{
		File* temp = dynamic_cast<File*>(item);
		if(temp != nullptr)
		{
			file_table.push_back(temp);
		}
	}
}
void FileSystem::GetFilesWithExtension(std::vector<File*>& file_table, const std::string& extension) const
{
	GetFilesVec(file_table, extension);
}



std::fstream FileSystem::OpenFile(const std::string& filename, FileMode mode)
{
	File* targetFile = GetFile(filename);
	std::fstream fileStream;
	switch (mode)
	{
	case FileMode::Read:
		fileStream.open(targetFile->GetFullPath().c_str(), std::fstream::in);
		break;
	case FileMode::Write:
		fileStream.open(targetFile->GetFullPath().c_str(), std::fstream::out);;
		break;
	case FileMode::ReadWrite:
		fileStream.open(targetFile->GetFullPath().c_str(), std::fstream::in | std::fstream::out);
		break;
	default:
		throw "Unknown mode";
	}
	return fileStream;
}
