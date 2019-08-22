﻿#include "PrecompiledHeader.h"

#include <array>
#include <thread>

#include "Environment.h"

namespace tgon
{

extern std::array<char, 16384> g_tempUtf8Buffer;

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
    return int32_t();
}

std::string Environment::GetMachineName()
{
    return std::string();
}

} /* namespace tgon */