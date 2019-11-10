#include "PrecompiledHeader.h"

#include "Path.h"
#include "DirectoryInfo.h"
#include "Directory.h"

namespace tgon
{

DirectoryInfo::DirectoryInfo(const std::string_view& path) :
    m_fullPath(Path::GetFullPath(path))
{
}

DirectoryInfo::DirectoryInfo(const std::string_view& path, FullPathTag) :
    m_fullPath(path)
{
}

bool DirectoryInfo::IsExists() const
{
    return Directory::Exists(m_fullPath.data());
}

std::string_view DirectoryInfo::GetName() const noexcept
{
    return Path::GetDirectoryName(m_fullPath);
}

DirectoryInfo DirectoryInfo::GetParent() const
{
    return Directory::GetParent(m_fullPath);
}

DirectoryInfo DirectoryInfo::GetRoot() const
{
    return DirectoryInfo(Directory::GetDirectoryRoot(m_fullPath), FullPathTag{});
}

std::vector<std::string> DirectoryInfo::GetDirectories(const char* searchPattern, SearchOption searchOption)
{
    return Directory::GetDirectories(m_fullPath.c_str(), searchPattern, searchOption);
}

std::vector<std::string> DirectoryInfo::GetFiles(const char* searchPattern, SearchOption searchOption)
{
    return Directory::GetFiles(m_fullPath.c_str(), searchPattern, searchOption);
}

std::vector<std::string> DirectoryInfo::GetFileSystemEntries(const char* searchPattern, SearchOption searchOption)
{
    return Directory::GetFileSystemEntries(m_fullPath.c_str(), searchPattern, searchOption);
}

void DirectoryInfo::Create() const
{
    Directory::CreateDirectory(m_fullPath.c_str());
}

DirectoryInfo DirectoryInfo::CreateSubdirectory(const std::string_view& path) const
{
    auto combinedPath = Path::Combine(m_fullPath, path);
    return Directory::CreateDirectory(combinedPath.c_str());
}

bool DirectoryInfo::MoveTo(const char* destDirName) const
{
    return Directory::Move(m_fullPath.c_str(), destDirName);
}

bool DirectoryInfo::Delete(bool recursive) const
{
    return Directory::Delete(m_fullPath.data(), recursive);
}

const std::string& DirectoryInfo::ToString() const noexcept
{
    return m_fullPath;
}

} /* namespace tgon */
