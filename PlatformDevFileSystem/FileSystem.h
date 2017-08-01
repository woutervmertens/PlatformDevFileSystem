#pragma once
#include "Item.h"

#include <memory>
#include <iostream>


class FileSystem
{
public:
	FileSystem(){}
	~FileSystem() {}

	Item * m_Root = new Directory("", nullptr);

	void MountDirectory(const std::string & directory){ m_Root = new Directory(directory, nullptr); MountDirectory(directory, m_Root);}//Avoiding making new variable for current dir
	void MountDirectory(const std::string & directory, Item* curDir);
	void ListContents() { ListContents(m_Root); }//Feedback for testing
	void ListContents(Item * folder);
	File* GetFile(const std::string & filename) const { return GetFile(filename, m_Root); }
	File* GetFile(const std::string & filename,Item * folder) const;
	Directory* GetDirectory(const std::string & filename) const{ return GetDirectory (filename, m_Root); }
	Directory* GetDirectory(const std::string & filename, Item* folder) const;
	void GetFilesVec(std::vector<File*>& file_table) const { GetFilesVec(file_table, m_Root); }
	void GetFilesVec(std::vector<File *>& file_table, const std::string & extension) const { GetFilesVec(file_table, m_Root, extension); }
	void GetFilesVec(std::vector<File*>& file_table, Item* folder) const { GetFilesVec(file_table, folder, ""); }
	void GetFilesVec(std::vector<File*>& file_table, Item* folder, const std::string & extension) const;
	std::string GetPhysicalFilePath(const std::string & filename) const;
	void GetFilesInDirectory(std::vector<File*> & file_table, const std::string & directory) const;
	void GetFilesWithExtension(std::vector<File*> & file_table, const std::string & extension) const { GetFilesVec(file_table, extension); }
	void OpenFile(const std::string & filename, FileMode mode, std::fstream &in);//fstream is limitation, won't work for network files
};

