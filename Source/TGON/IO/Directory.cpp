#include "PrecompiledHeader.h"

#include <array>

#include "Text/FixedString.h"

#include "Directory.h"
#include "DirectoryInfo.h"

namespace tgon
{

DirectoryInfo Directory::CreateDirectory(const std::string_view& path)
{
    std::string fullPath = Path::GetFullPath(path);
    if (fullPath.length() > 0 && Path::IsDirectorySeparator(fullPath.back()) == false)
    {
        fullPath += Path::DirectorySeparatorChar;
    }
    
    for (size_t i = Path::IsDirectorySeparator(fullPath.front()) ? 1 : 0; i < fullPath.length(); ++i)
    {
        auto c = fullPath[i];
        if (Path::IsDirectorySeparator(c))
        {
            fullPath[i] = 0;
            InternalCreateDirectory(fullPath.data());
            
            fullPath[i] = c;
        }
    }
    
    return DirectoryInfo(fullPath, FullPathTag{});
}

DirectoryInfo Directory::GetParent(const std::string_view& path)
{
    FixedString16384 str(path);
    if (path.length() > 0)
    {
        if (Path::IsDirectorySeparator(str[str.Length() - 1]) == false)
        {
            str += Path::DirectorySeparatorChar;
        }
    }
    else
    {
        return DirectoryInfo("", FullPathTag{});
    }
    
    str += "../";
    
    return DirectoryInfo(str);
}

std::string Directory::GetCurrentDirectory()
{
    std::array<char, 16384> str;
    auto strLen = GetCurrentDirectory(str.data(), static_cast<int32_t>(str.size()));
    return {str.data(), static_cast<size_t>(strLen)};
}

bool Directory::SetCreationTime(const char* path, const DateTime& creationTime)
{
    return File::SetCreationTime(path, creationTime);
}

bool Directory::SetCreationTimeUtc(const char* path, const DateTime& creationTimeUtc)
{
    return File::SetCreationTimeUtc(path, creationTimeUtc);
}

bool Directory::SetLastAccessTime(const char* path, const DateTime& lastAccessTime)
{
    return File::SetLastAccessTime(path, lastAccessTime);
}

bool Directory::SetLastAccessTimeUtc(const char* path, const DateTime& lastAccessTimeUtc)
{
    return File::SetLastAccessTimeUtc(path, lastAccessTimeUtc);
}

bool Directory::SetLastWriteTime(const char* path, const DateTime& lastWriteTime)
{
    return File::SetLastWriteTime(path, lastWriteTime);
}

bool Directory::SetLastWriteTimeUtc(const char* path, const DateTime& lastWriteTimeUtc)
{
    return File::SetLastWriteTimeUtc(path, lastWriteTimeUtc);
}

std::optional<DateTime> Directory::GetCreationTime(const char* path)
{
    return File::GetCreationTime(path);
}

std::optional<DateTime> Directory::GetCreationTimeUtc(const char* path)
{
    return File::GetCreationTimeUtc(path);
}

std::optional<DateTime> Directory::GetLastAccessTime(const char* path)
{
    return File::GetLastAccessTime(path);
}

std::optional<DateTime> Directory::GetLastAccessTimeUtc(const char* path)
{
    return File::GetLastAccessTimeUtc(path);
}

std::optional<DateTime> Directory::GetLastWriteTime(const char* path)
{
    return File::GetLastWriteTime(path);
}

std::optional<DateTime> Directory::GetLastWriteTimeUtc(const char* path)
{
    return File::GetLastWriteTimeUtc(path);
}

std::string Directory::GetDirectoryRoot(const std::string_view& path)
{
    if (path.length() <= 0)
    {
        return {};
    }
    
    auto fullPath = Path::GetFullPath(path);
    return fullPath.substr(0, Path::GetRootLength(fullPath));
}

std::vector<std::string> Directory::GetDirectories(const char* path, const char* searchPattern, SearchOption searchOption)
{
    std::vector<std::string> ret;
    
    EnumerateDirectories(path, searchPattern, searchOption, [&](const std::string_view& str)
    {
        ret.emplace_back(str);
    });
    return ret;
}

std::vector<std::string> Directory::GetFiles(const char* path, const char* searchPattern, SearchOption searchOption)
{
    std::vector<std::string> ret;
    
    EnumerateFiles(path, searchPattern, searchOption, [&](const std::string_view& str)
    {
        ret.emplace_back(str);
    });
    return ret;
}

std::vector<std::string> Directory::GetFileSystemEntries(const char* path, const char* searchPattern, SearchOption searchOption)
{
    std::vector<std::string> ret;
    
    EnumerateFileSystemEntries(path, searchPattern, searchOption, [&](const std::string_view& str)
    {
        ret.emplace_back(str);
    });
    return ret;
}

} /* namespace tgon */
