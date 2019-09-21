#include "PrecompiledHeader.h"

#include <thread>
#include <array>

#include "Environment.h"

namespace tgon
{

thread_local std::array<char, 16384> g_tempUtf8Buffer;

std::optional<std::string> Environment::GetEnvironmentVariable(const std::string_view& name)
{
    auto strLen = GetEnvironmentVariable(name, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

std::string Environment::GetCurrentDirectory()
{
    auto strLen = GetCurrentDirectory(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

std::optional<std::string> Environment::GetFolderPath(SpecialFolder folder)
{
    auto strLen = GetFolderPath(folder, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

void Environment::Exit(int32_t exitCode)
{
    std::exit(exitCode);
}

int32_t Environment::GetProcessorCount()
{
    return static_cast<int32_t>(std::thread::hardware_concurrency());
}

std::string Environment::GetUserName()
{
    auto strLen = GetUserName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

std::string Environment::GetMachineName()
{
    auto strLen = GetMachineName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

std::string Environment::GetUserDomainName()
{
    auto strLen = GetUserDomainName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

} /* namespace tgon */
