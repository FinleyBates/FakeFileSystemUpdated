#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <crtdbg.h>
#include <stdlib.h>

using namespace std;

class FfsObject
{
public:
	//FfsObject(const string& name);
	//FfsObject();
	FfsObject(const filesystem::directory_entry& entry);
	/*FfsObject(const string& name);*/
	virtual ~FfsObject();
	const string& getName() const;
	inline const tm getCreationTime();

	//void display();
		// we need to do a little conversion between what the filesystem returns for time stamps and something usable
		// 
	// just use this function and don't worry about how it works

	inline const tm convertTime(const filesystem::file_time_type& timestamp); 
	virtual filesystem::path getPath() const = 0;

private:
	string name;
	tm creationTime;
	filesystem::path path;

protected:
	/*filesystem::path getPath() const {
		return path;
	}*/
};

inline const string& FfsObject::getName() const
{
	return name; 
}

inline const tm FfsObject::getCreationTime()
{
	return convertTime(filesystem::last_write_time(path));
}

inline const tm FfsObject::convertTime(const filesystem::file_time_type& timestamp)
{
	using namespace chrono;  // just for this function, use chrono to save us prefixing chrono:: everywhere
	system_clock::time_point delta = time_point_cast<system_clock::duration>(timestamp - filesystem::file_time_type::clock::now() + system_clock::now());
	time_t conversion = system_clock::to_time_t(delta);

	tm creationTime;
	localtime_s(&creationTime, &conversion); 
	return creationTime; 
}