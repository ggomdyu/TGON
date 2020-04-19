#include "PrecompiledHeader.h"

#include <thread>
#include <array>

#include "IO/Directory.h"

#include "Environment.h"

namespace tg
{

std::optional<std::string> Environment::GetEnvironmentVariable(const char* name)
{
    std::array<char, 8192> str;
    auto strLen = GetEnvironmentVariable(name, str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return std::string(str.data(), static_cast<size_t>(*strLen));
}

std::string Environment::GetCurrentDirectory()
{
    return Directory::GetCurrentDirectory();
}

std::optional<int32_t> Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    return Directory::GetCurrentDirectory(destStr, destStrBufferLen);
}

std::optional<int32_t> Environment::GetCurrentDirectory(const gsl::span<char>& destStr)
{
    return GetCurrentDirectory(destStr.data(), static_cast<int32_t>(destStr.size()));
}

std::string Environment::GetFolderPath(SpecialFolder folder)
{
    std::array<char, 8192> str;
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

std::string Environment::GetUserName()
{
    std::array<char, 4096> str;
    auto strLen = GetUserName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

std::string Environment::GetMachineName()
{
    std::array<char, 4096> str;
    auto strLen = GetMachineName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

std::string Environment::GetUserDomainName()
{
    std::array<char, 4096> str;
    auto strLen = GetUserDomainName(str.data(), static_cast<int32_t>(str.size()));
    if (strLen.has_value() == false)
    {
        return {};
    }

    return {str.data(), static_cast<size_t>(*strLen)};
}

void Environment::FailFast(const char* message)
{
    FailFast(message, {});
}

std::string Environment::GetStackTrace()
{
    std::array<char, 8192> str;
    auto strLen = GetStackTrace(str.data(), static_cast<int32_t>(str.size()));
    return {str.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetSystemDirectory()
{
    return GetFolderPath(SpecialFolder::System);
}

std::vector<std::string> Environment::GetLogicalDrives()
{
    return Directory::GetLogicalDrives();
}

}
