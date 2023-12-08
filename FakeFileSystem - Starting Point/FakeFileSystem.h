#pragma once
#include <iostream>
#include "Directory.h"
#include "File.h"
#include <filesystem>

class FakeFileSystem
{
public:
    FakeFileSystem(const filesystem::path& rootPath);
    //FakeFileSystem();
    ~FakeFileSystem();
    void dir(Directory* currentDir) const;
    void sortsize();
    void sortname();
    void cd(const std::string& directoryName);
    void mkdir(const std::string& directoryName);
    void mkfile(const std::string& fileName);
    void del(const std::string& name);
    void exit();

    void loadData();
    void populate(Directory* currentDir, const filesystem::path& currentPath);
    void printCreationTime(const tm& creationTime) const;
    void displayPrompt() const;
    void cleanup(Directory* currentDir);

private:

    std::unique_ptr<Directory> root; //using a unique_ptr to deal with memory issues
    Directory* currentDir;
};

