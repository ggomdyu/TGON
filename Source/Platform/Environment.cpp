#include "PrecompiledHeader.h"

#include <thread>
#include <array>

#include "IO/Directory.h"

#include "Environment.h"

namespace tg
{

std::optional<std::u8string> Environment::GetEnvironmentVariable(const char8_t* name)
{
    std::array<char8_t, 8192> str{};
    auto strLen = GetEnvironmentVariable(name, str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return std::u8string(str.data(), static_cast<size_t>(*strLen));
}

std::u8string Environment::GetCurrentDirectory()
{
    return Directory::GetCurrentDirectory();
}

std::optional<int32_t> Environment::GetCurrentDirectory(char8_t* destStr, int32_t destStrBufferLen)
{
    return Directory::GetCurrentDirectory(destStr, destStrBufferLen);
}

std::optional<int32_t> Environment::GetCurrentDirectory(const std::span<char8_t>& destStr)
{
    return GetCurrentDirectory(destStr.data(), static_cast<int32_t>(destStr.size()));
}

std::u8string Environment::GetFolderPath(SpecialFolder folder)
{
    std::array<char8_t, 2048> str{};
    auto strLen = GetFolderPath(folder, str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

void Environment::Exit(int32_t exitCode)
{
    std::exit(exitCode);
}

int32_t Environment::GetProcessorCount()
{
    return static_cast<int32_t>(std::thread::hardware_concurrency());
}

std::u8string Environment::GetUserName()
{
    std::array<char8_t, 2048> str{};
    auto strLen = GetUserName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

std::u8string Environment::GetMachineName()
{
    std::array<char8_t, 2048> str{};
    auto strLen = GetMachineName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

std::u8string Environment::GetUserDomainName()
{
    std::array<char8_t, 2048> str{};
    auto strLen = GetUserDomainName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

std::u8string Environment::GetStackTrace()
{
    std::array<char8_t, 8192> str{};
    const auto strLen = GetStackTrace(str.data(), static_cast<int32_t>(str.size()));

    return {str.data(), static_cast<size_t>(strLen)};
}

std::u8string Environment::GetSystemDirectory()
{
    return GetFolderPath(SpecialFolder::System);
}

std::vector<std::u8string> Environment::GetLogicalDrives()
{
    return Directory::GetLogicalDrives();
}

}
