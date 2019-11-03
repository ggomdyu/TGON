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
    return Directory::Exists(m_fullPath.data());
}

std::string_view DirectoryInfo::GetName() const
{
    return Path::GetDirectoryName(m_fullPath);
}

DirectoryInfo DirectoryInfo::GetParent() const
{
    return DirectoryInfo("../");
}

bool DirectoryInfo::Delete(bool recursive)
{
    return Directory::Delete(m_fullPath.data(), recursive);
}

} /* namespace tgon */
