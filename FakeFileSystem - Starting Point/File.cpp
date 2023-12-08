#include "File.h"

File::File(const filesystem::directory_entry& entry, const __int64& size) : FfsObject(entry), size(size) {}

File::File(const filesystem::directory_entry& entry, const __int64& size, const filesystem::path& filePath) : FfsObject(entry), size(size), filePath(getPath()) {}

File::~File() {}

