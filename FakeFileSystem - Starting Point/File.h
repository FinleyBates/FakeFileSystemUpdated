#pragma once
#include "FfsObject.h"
#include <iostream>

using namespace std;


class File : public FfsObject
{
public:
    File(const filesystem::directory_entry& entry, const __int64& size);
    File(const filesystem::directory_entry& entry, const __int64& size, const filesystem::path& filePath);
    virtual ~File();
    __int64 getSize() const;
    filesystem::path getPath() const override {
        return filePath;
    }
private:
    __int64 size;
    filesystem::path filePath;

};

inline __int64 File::getSize() const
{
    return size;
}