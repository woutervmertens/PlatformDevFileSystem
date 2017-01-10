#pragma once
#include <string>
#include <vector>//om alle file te bewaren
#include "FileMode.h"

class Item
{
public:
	Item(const std::string & s, Item * parent);
	virtual ~Item();
	std::string GetName();
	std::string GetFullPath();

protected:
	std::string m_Name;
	Item* m_Parent;
};

class Directory : public Item
{
public:
	Directory(const std::string & s, Item * parent);//Pointers cuz dirs in dirs possible
	~Directory();

	std::vector<Item*> m_Files;
};


class File : public Item
{
public:
	File(const std::string & s, Item * parent);
	~File();
};
