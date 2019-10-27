#include "PrecompiledHeader.h"

#include <array>

#include "Directory.h"

namespace tgon
{

extern thread_local std::array<char, 16384> g_tempUtf8Buffer;

DirectoryInfo Directory::CreateDirectory(const std::string_view& path)
{
    return DirectoryInfo(path);
}

DirectoryInfo Directory::GetParent(const std::string_view& path)
{
    return DirectoryInfo("../");
}

std::string Directory::GetCurrentDirectory()
{
    auto strLen = GetCurrentDirectory(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return std::string();
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

} /* namespace tgon */
