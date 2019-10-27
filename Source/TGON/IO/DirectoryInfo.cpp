#include "PrecompiledHeader.h"

#include "Path.h"
#include "DirectoryInfo.h"

namespace tgon
{

DirectoryInfo::DirectoryInfo(const std::string_view& path) :
    m_fullPath(Path::GetFullPath(path))
{
}

} /* namespace tgon */
