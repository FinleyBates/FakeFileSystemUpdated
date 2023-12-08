#pragma once
#include <iostream>
#include <vector>
#include "FfsObject.h"

using namespace std;

class Directory : public FfsObject
{
public:
    //rectory(const string& name);
    //Directory();
    Directory(const filesystem::directory_entry& entry); 
    Directory(const filesystem::directory_entry& entry, const filesystem::path& directoryPath);
    virtual ~Directory();
    vector<FfsObject*>& getContents();
    filesystem::path getPath() const override {
        return directoryPath;
    }


private:
    vector<FfsObject*> contents;
    filesystem::path directoryPath;
};
