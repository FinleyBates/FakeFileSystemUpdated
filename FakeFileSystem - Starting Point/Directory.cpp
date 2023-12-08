#include "Directory.h"


Directory::Directory(const filesystem::directory_entry& entry) : FfsObject(entry){}

Directory::~Directory() {}

Directory::Directory(const filesystem::directory_entry& entry, const filesystem::path& directoryPath) :  FfsObject(entry), directoryPath(getPath())
{

}

//Directory::~Directory()
//{
//	for (FfsObject* object : contents) //delete all objects in the vector
//	{
//		delete object;
//	}
//}

vector<FfsObject*>& Directory::getContents()
{
	return contents;
}

