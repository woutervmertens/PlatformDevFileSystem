#include <iostream>
#include "FileSystem.h"
#include <fstream>


int main()
{
	FileSystem fs = FileSystem();
	std::vector<File*> vec, vec2;
	std::cout << "Mount" << std::endl;
	fs.MountDirectory("C:/Users/woodz/Source/Repos/PlatDev/PlatformDevFileSystem/Debug/test");
	std::cout << "List" << std::endl;
	fs.ListContent();
	std::cout << "Find Files" << std::endl;
	std::cout << "File found: " <<  fs.GetPhysicalFilePath("jup.txt") << std::endl;
	std::cout << "File found: " << fs.GetPhysicalFilePath("eyyyy.txt") << std::endl;
	std::cout << "File found: " << fs.GetPhysicalFilePath("doubletest.txt") << std::endl;
	std::cout << "Get files in directory taste" << std::endl;
	fs.GetFilesInDirectory(vec,"taste");
	for (File* item : vec) { std::cout << item->GetName() << std::endl; }
	std::cout << "Get files with extension .txt" << std::endl;
	fs.GetFilesWithExtension(vec2, ".txt");
	std::cout << "Open file" << std::endl;
	std::fstream JupFile = fs.OpenFile("jup.txt",FileMode::Read);
	std::string line;
	if(JupFile.is_open())
	{
		while(std::getline(JupFile, line))
		{
			std::cout << line << std::endl;
		}
		JupFile.close();
	}
	return 0;
}
