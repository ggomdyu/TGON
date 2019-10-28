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

bool DirectoryInfo::IsExists()
{
    return Directory::Exists(m_fullPath);
}

bool DirectoryInfo::Delete(bool recursive)
{
    return Directory::Delete(m_fullPath, recursive);
}

} /* namespace tgon */
