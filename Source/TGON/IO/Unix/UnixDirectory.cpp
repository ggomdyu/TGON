#include "PrecompiledHeader.h"

#include <sys/stat.h>

#include "../Path.h"
#include "../Directory.h"

namespace tgon
{

DirectoryInfo Directory::CreateDirectory(const char* path)
{
    mkdir(path, 0777);
    return DirectoryInfo(path);
}

bool Directory::Delete(const char* path, bool recursive)
{
    return false;
}

bool Directory::Exists(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0 || S_ISDIR(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool Directory::Move(const char* srcPath, const char* destPath)
{
    struct stat s;
    if (stat(srcPath, &s) != 0 || S_ISDIR(s.st_mode) == false)
    {
        return false;
    }
    
    return rename(srcPath, destPath) == 0;
}

int32_t Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    if (getcwd(destStr, destStrBufferLen) == nullptr)
    {
        return -1;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

std::vector<std::string> Directory::GetDirectories(const char* path, const char* searchPattern, SearchOption searchOption)
{
    std::vector<std::string> ret;
    
    EnumerateDirectories(path, searchPattern, searchOption, [&](std::string&& str)
    {
        ret.push_back(std::move(str));
    });
    return ret;
}

std::vector<std::string> Directory::GetFiles(const char* path, const char* searchPattern, SearchOption searchOption)
{
    std::vector<std::string> ret;
    
    EnumerateFiles(path, searchPattern, searchOption, [&](std::string&& str)
    {
        ret.push_back(std::move(str));
    });
    return ret;
}

} /* namespace tgon */
