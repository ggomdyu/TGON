#include "PrecompiledHeader.h"

#include <array>
#include <unistd.h>
#include <sys/stat.h>

#include "../Path.h"
#include "../DirectoryInfo.h"
#include "../Directory.h"

namespace tgon
{
namespace
{

bool InternalRecursiveDelete(const std::string& path)
{
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr)
    {
        return false;
    }
    
    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr)
    {
        // Ignore the . and ..
        if ((ent->d_namlen == 1 && ent->d_name[0] == '.') || (ent->d_namlen == 2 && !strcmp(ent->d_name, "..")))
        {
            continue;
        }
        
        auto combinedPath = Path::Combine(path, {ent->d_name, ent->d_namlen});
        if (ent->d_type & DT_DIR)
        {
            InternalRecursiveDelete(combinedPath);
        }
        else
        {
            unlink(combinedPath.c_str());
        }
    }
    closedir(dir);

    return rmdir(path.c_str()) == 0;
}

} /* namespace */

bool Directory::Exists(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0 || S_ISDIR(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool Directory::Delete(const char* path, bool recursive)
{
    if (recursive)
    {
        return InternalRecursiveDelete(path);
    }
    
    return rmdir(path) == 0;
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

bool Directory::SetCurrentDirectory(const char* path)
{
    return chdir(path) == 0;
}

std::optional<int32_t> Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    if (getcwd(destStr, destStrBufferLen) == nullptr)
    {
        return {};
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

std::vector<std::string> Directory::GetLogicalDrives()
{
    // TODO: Implement
    return {};
}

bool Directory::InternalCreateDirectory(const char* path)
{
    return mkdir(path, 0777) == 0;
}

} /* namespace tgon */

