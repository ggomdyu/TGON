#include "PrecompiledHeader.h"

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "Directory.h"

namespace tgon
{

bool Directory::Exists(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISDIR(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

int32_t Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    if (getcwd(destStr, destStrBufferLen) == nullptr)
    {
        return -1;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

} /* namespace tgon */
