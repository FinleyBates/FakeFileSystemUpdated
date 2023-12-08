#include "FfsObject.h"

//FfsObject::FfsObject(const string& name) : name(name), creationTime(convertTime(filesystem::last_write_time(name))) {}
FfsObject::FfsObject(const filesystem::directory_entry& entry) : name(entry.path().filename().string()), creationTime(convertTime(entry.last_write_time())), path(entry.path())
{

}

//FfsObject::FfsObject() {}
//FfsObject::FfsObject(const string& name) : name(name) {}


FfsObject::~FfsObject() {}

