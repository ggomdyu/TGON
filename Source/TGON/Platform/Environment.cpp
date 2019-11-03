#include "PrecompiledHeader.h"

#include <thread>
#include <array>
#include <sstream>

#include "IO/Directory.h"

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

std::optional<std::string> Environment::GetEnvironmentVariable(const std::string_view& name, EnvironmentVariableTarget target)
{
    if (target == EnvironmentVariableTarget::Process)
    {
        return GetEnvironmentVariable(name);
    }

    if (target == EnvironmentVariableTarget::Machine)
    {
    
        /*using (RegistryKey environmentKey =
            Registry.LocalMachine.OpenSubKey(@"System\CurrentControlSet\Control\Session Manager\Environment", false)) {

                Contract.Assert(environmentKey != null, @"HKLM\System\CurrentControlSet\Control\Session Manager\Environment is missing!");
                    if (environmentKey == null) {
                        return null;
                    }

        string value = environmentKey.GetValue(variable) as string;
        return value;*/
    }
    
    if (target == EnvironmentVariableTarget::User)
    {
        /*using (RegistryKey environmentKey =
        Registry.CurrentUser.OpenSubKey("Environment", false)) {

        Contract.Assert(environmentKey != null, @"HKCU\Environment is missing!");
            if (environmentKey == null) {
                return null;
            }

        string value = environmentKey.GetValue(variable) as string;
        return value;*/
    }

    return {};
}

std::string Environment::GetCurrentDirectory()
{
    return Directory::GetCurrentDirectory();
}

int32_t Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    return Directory::GetCurrentDirectory(destStr, destStrBufferLen);
}

std::string Environment::GetFolderPath(SpecialFolder folder)
{
    auto strLen = GetFolderPath(folder, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
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
    
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetMachineName()
{
    auto strLen = GetMachineName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetUserDomainName()
{
    auto strLen = GetUserDomainName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }
    
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetStackTrace()
{
    auto strLen = GetStackTrace(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }

    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Environment::GetSystemDirectory()
{
    return GetFolderPath(SpecialFolder::System);
}
    
} /* namespace tgon */
