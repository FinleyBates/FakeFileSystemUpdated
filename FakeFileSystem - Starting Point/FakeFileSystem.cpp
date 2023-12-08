#include "FakeFileSystem.h"
#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

FakeFileSystem::FakeFileSystem(const filesystem::path& rootPath)
{    
    filesystem::directory_entry rootEntry(rootPath);
    root = make_unique<Directory>(rootEntry);
    currentDir = root.get();
}

FakeFileSystem::~FakeFileSystem() 
{
    cleanup(root.get());
}
//    delete root.get();
//}

void FakeFileSystem::loadData() {
    try {
        const char* path = "D:\\FFS\\FakeFileSystem - Starting Point\\Test";
        // Create root
        filesystem::directory_entry rootEntry(path); 
        root = make_unique<Directory>(rootEntry); 
        //cout << "rootEntry path: " << rootEntry.path() << "\n";
        populate(root.get(), rootEntry.path());  // Use rootEntry.path() to get the path 
        //cout << "rootEntry path: " << rootEntry.path() << "\n";
    }
    catch (const filesystem::filesystem_error& ex) {
        cerr << "Filesystem error: " << ex.what() << "\n";
    }
}

void FakeFileSystem::populate(Directory* currentDir, const filesystem::path& currentPath) {

    for (const filesystem::directory_entry& item : filesystem::directory_iterator(currentPath)) {
        //cout << "rootEntry path: " << filesystem::current_path() << "\n";
        if (filesystem::is_directory(item)) {
            // If directory, populate recursively by creating a directory and calling the function again
            //cout << "Creating Directory with path: " << rootEntry.path() << "\n";
            Directory* subDir = new Directory(item, item.path());
            currentDir->getContents().push_back(subDir); // Add subdir
            populate(subDir, item.path());
        }
        else {

            File* file = new File(item, item.file_size(), item.path());//creates file in case of not directory
            currentDir->getContents().push_back(file); // Add file to currentdir contents
        }
    }
    
    this->dir(currentDir);
}


void FakeFileSystem::displayPrompt() const
{
    if (currentDir != nullptr) {
        //cout << currentDir->getName() << " -> ";
        cout << "Current Path: " << filesystem::current_path() << " -> " << currentDir->getName() << " -> ";
    }
}

void FakeFileSystem::dir(Directory* currentDir) const
{
    if (currentDir != nullptr)
    {
        //cout << "Current Path: " << filesystem::current_path() << "\n";
        const vector <FfsObject*>& contents = currentDir->getContents();
        for (FfsObject* FFsObjectPtr : contents)
        {
            if (FFsObjectPtr != nullptr) {
                //filesystem::is_directory(FFsObjectPtr->getPath()); //use when clarifying if directory
                cout << FFsObjectPtr->getName() << "\n";
                const tm& thisCreationTime = FFsObjectPtr->getCreationTime();
                cout << "Year: " << (thisCreationTime.tm_year + 1900);
                cout << " Month: " << (thisCreationTime.tm_mon + 1); // tm_mon starts at 0 for January so add 1
                cout << " Day: " << thisCreationTime.tm_mday;
                cout << " Hour: " << thisCreationTime.tm_hour;
                cout << " Min: " << thisCreationTime.tm_min;
                cout << "\n";
            }
            else cout << "nullptr";
        }
    }
    else cout << "no currentDir";
}

void FakeFileSystem::cleanup(Directory* currentDir) {
    for (FfsObject* obj : currentDir->getContents()) {
        if (Directory* subDir = dynamic_cast<Directory*>(obj)) {
            cleanup(subDir);
        }
        delete obj;  // Release memory for both Directory and File objects
    }
    currentDir->getContents().clear();  // Clear the contents vector
}