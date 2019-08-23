#include "PrecompiledHeader.h"

#include <array>
#include <thread>

#include "Environment.h"

namespace tgon
{

thread_local std::array<char, 16384> g_tempUtf8Buffer;

int32_t Environment::GetEnvironmentVariable(const std::string_view& name, const Span<char>& destStr)
{
    return GetEnvironmentVariable(name, &destStr[0], destStr.Length());
}

std::string Environment::GetEnvironmentVariable(const std::string_view& name)
{
    auto strLen = GetEnvironmentVariable(name, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetCurrentDirectory()
{
    auto strLen = GetCurrentDirectory(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Environment::GetCurrentDirectory(const Span<char>& destStr)
{
    return GetCurrentDirectory(&destStr[0], destStr.Length());
}

std::string Environment::GetFolderPath(SpecialFolder folder)
{
    auto strLen = GetFolderPath(folder, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Environment::GetFolderPath(SpecialFolder folder, const Span<char>& destStr)
{
    return GetFolderPath(folder, &destStr[0], destStr.Length());
}

void Environment::Exit(int32_t exitCode)
{
    std::exit(exitCode);
}

int32_t Environment::GetProcessorCount()
{
    return static_cast<int32_t>(std::thread::hardware_concurrency());
}

int32_t Environment::GetUserName(const Span<char>& destStr)
{
    return GetUserName(&destStr[0], destStr.Length());
}

std::string Environment::GetUserName()
{
    auto strLen = GetUserName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Environment::GetMachineName(const Span<char>& destStr)
{
    return GetMachineName(&destStr[0], destStr.Length());
}

std::string Environment::GetMachineName()
{
    auto strLen = GetMachineName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Environment::GetUserDomainName(const Span<char>& destStr)
{
    return GetUserDomainName(&destStr[0], destStr.Length());
}

std::string Environment::GetUserDomainName()
{
    auto strLen = GetUserDomainName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

} /* namespace tgon */