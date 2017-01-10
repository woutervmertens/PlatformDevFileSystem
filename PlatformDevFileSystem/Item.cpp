#include "Item.h"

Item::Item(const std::string & s, Item * parent)
{
	m_Name = s;
	m_Parent = parent;
}

Item::~Item()
{
}

std::string Item::GetName()
{
	return m_Name;
}

std::string Item::GetFullPath()
{
	if(m_Parent == nullptr)
	{
		return m_Name;
	}
	return m_Parent->GetFullPath() + "/" + m_Name;
}

Directory::Directory(const std::string & s, Item * parent) : Item(s, parent)
{
}

Directory::~Directory()
{
}

File::File(const std::string & s, Item * parent) : Item(s, parent)
{
}

File::~File()
{
}

