#pragma once
#include "Item.h"

#include <memory>
#include <iostream>


class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	Item * m_Root = new Directory("", nullptr);

	void MountDirectory(const std::string & directory);
	void MountDirectory(const std::string & directory, Item* curDir);
	void ListContent();
	void ListContent(Item * folder);
	File* GetFile(const std::string & filename) const;
	File* GetFile(const std::string & filename,Item * folder) const;
	Directory* GetDirectory(const std::string & filename) const;
	Directory* GetDirectory(const std::string & filename, Item* folder) const;
	void GetFilesVec(std::vector<File*>& file_table) const;
	void GetFilesVec(std::vector<File *>& file_table, const std::string & extension) const;
	void GetFilesVec(std::vector<File*>& file_table, Item* folder) const;
	void GetFilesVec(std::vector<File*>& file_table, Item* folder, const std::string & extension) const;
	std::string GetPhysicalFilePath(const std::string & filename) const;
	void GetFilesInDirectory(std::vector<File*> & file_table, const std::string & directory) const;
	void GetFilesWithExtension(std::vector<File*> & file_table, const std::string & extension) const;
	std::fstream OpenFile(const std::string & filename, FileMode mode);
};

