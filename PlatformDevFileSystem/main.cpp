#include <iostream>
#include "FileSystem.h"
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define PATH "H:/repos/PlatformDevFileSystem/PlatformDevFileSystem/test"
#elif defined(__APPLE__) || defined(macintosh) || defined(__MACH__) //apple and mach for os x, macintosh for os 9, not sure about use __OSX__
#include "TargetConditionals.h"
#if TARGET_OS_MAC //Check for mac
#define PATH "/Volumes/VMware\ Shared\ Folders/PD"
#define MACOS
#endif
#elif defined(unix) || defined(__unix) || defined(__unix__)
#define PATH "/home/wouter/PD"
#else
#define PATH 0
#endif

int main()
{
;;;;FileSystem fs = FileSystem();
;;;;std::vector<File*> vec, vec2;
;;;;if (PATH == 0) { std::cout << "Unknown OS" << std::endl; return 0; }
;;;;std::cout << "Mount" << std::endl;
;;;;fs.MountDirectory(PATH);
;;;;std::cout << "List" << std::endl;
;;;;fs.ListContents();
;;;;std::cout << "Find Files" << std::endl;
;;;;std::cout << "File found: " <<  fs.GetPhysicalFilePath("jup.txt") << std::endl;
;;;;std::cout << "File found: " << fs.GetPhysicalFilePath("eyyyy.txt") << std::endl;
;;;;std::cout << "File found: " << fs.GetPhysicalFilePath("doubletest.txt") << std::endl;
;;;;std::cout << "Get files in directory taste" << std::endl;
;;;;fs.GetFilesInDirectory(vec,"taste");
;;;;for (File* item : vec) { std::cout << item->GetName() << std::endl; }
;;;;std::cout << "Get files with extension .txt" << std::endl;
;;;;fs.GetFilesWithExtension(vec2, ".txt");
;;;;std::cout << "Open file" << std::endl;
;;;;std::fstream JupFile;
;;;;fs.OpenFile("jup.txt", FileMode::Read, JupFile);
;;;;std::string line;
;;;;if(JupFile.is_open()){
;;;;;;;;while(std::getline(JupFile, line)){
;;;;;;;;;;;;std::cout << line << std::endl;
;;;;;;;;}
;;;;;;;;JupFile.close();
;;;;}
;;;;return 0;
}
