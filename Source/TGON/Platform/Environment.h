/**
 * @file    Environment.h
 * @author  ggomdyu
 * @since   08/18/2019
 */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <gsl/span>

#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsEnvironment.h"
#endif

namespace tgon
{

enum class EnvironmentVariableTarget
{
    Process = 0,
    User = 1,
    Machine = 2,
};

class TGON_API Environment final
{
/**@section Constructor */
public:
    Environment() = delete;

/**@section Enum */
public:
    enum class SpecialFolder
    {
        Desktop = 0,
        Programs = 2,
        MyDocuments = 5,
        Personal = 5,
        Favorites = 6,
        Startup = 7,
        Recent = 8,
        SendTo = 9,
        StartMenu = 11,
        MyMusic = 13,
        MyVideos = 14,
        DesktopDirectory = 16,
        MyComputer = 17,
        NetworkShortcuts = 19,
        Fonts = 20,
        Templates = 21,
        CommonStartMenu = 22,
        CommonPrograms = 23,
        CommonStartup = 24,
        CommonDesktopDirectory = 25,
        ApplicationData = 26,
        PrinterShortcuts = 27,
        LocalApplicationData = 28,
        InternetCache = 32,
        Cookies = 33,
        History = 34,
        CommonApplicationData = 35,
        Windows = 36,
        System = 37,
        ProgramFiles = 38,
        MyPictures = 39,
        UserProfile = 40,
        SystemX86 = 41,
        ProgramFilesX86 = 42,
        CommonProgramFiles = 43,
        CommonProgramFilesX86 = 44,
        CommonTemplates = 45,
        CommonDocuments = 46,
        CommonAdminTools = 47,
        AdminTools = 48,
        CommonMusic = 53,
        CommonPictures = 54,
        CommonVideos = 55,
        Resources = 56,
        LocalizedResources = 57,
        CommonOemLinks = 58,
        CDBurning = 59,
    };

/**@section Method */
public:
    static bool SetEnvironmentVariable(const std::string_view& name, const std::string_view& value);
    static int32_t GetEnvironmentVariable(const std::string_view& name, char* destStr, int32_t destStrBufferLen);
    static int32_t GetEnvironmentVariable(const std::string_view& name, const gsl::span<char>& destStr);
    static std::optional<std::string> GetEnvironmentVariable(const std::string_view& name);
    static std::optional<std::string> GetEnvironmentVariable(const std::string_view& name, EnvironmentVariableTarget target);
    static std::string GetCurrentDirectory();
    static int32_t GetCurrentDirectory(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetCurrentDirectory(const gsl::span<char, Length>& destStr);
    static std::string GetFolderPath(SpecialFolder folder);
    static int32_t GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferLen);
    static int32_t GetFolderPath(SpecialFolder folder, const gsl::span<char>& destStr);
    static std::string_view GetNewLine();
    static int32_t GetSystemPageSize();
    static int32_t GetCurrentManagedThreadId();
    static std::string GetUserName();
    static int32_t GetUserName(char* destStr, int32_t destStrBufferLen);
    static int32_t GetUserName(const gsl::span<char>& destStr);
    static std::string GetMachineName();
    static int32_t GetMachineName(char* destStr, int32_t destStrBufferLen);
    static int32_t GetMachineName(const gsl::span<char>& destStr);
    static std::string GetUserDomainName();
    static int32_t GetUserDomainName(char* destStr, int32_t destStrBufferLen);
    static int32_t GetUserDomainName(const gsl::span<char>& destStr);
    static const std::string& GetCommandLine();
    static const std::vector<std::string>& GetCommandLineArgs();
    [[noreturn]] static void Exit(int32_t exitCode);
    static int64_t GetTickCount();
    static int32_t GetProcessorCount();
    static bool Is64BitProcess();
    static bool Is64BitOperatingSystem();
    [[noreturn]] static void FailFast(const std::string_view& message);
    [[noreturn]] static void FailFast(const std::string_view& message, const std::exception& exception);
    static int32_t GetStackTrace(char* destStr, int32_t destStrBufferLen);
    static std::string GetStackTrace();
    static std::string GetSystemDirectory();
        /*
    public static IDictionary GetEnvironmentVariables();
    public static IDictionary GetEnvironmentVariables(EnvironmentVariableTarget target);
    public static void SetEnvironmentVariable(
        string variable,
        string value,
        EnvironmentVariableTarget target);
    
    public static string ExpandEnvironmentVariables(string name);
    
    public static strPath(
        Environment.SpecialFolder folder,
        Environment.SpecialFolderOption option);
    public static bool HasShutdownSting GetFolderarted{ get; }
    public static OperatingSystem OSVersion{ get; }
    public static bool UserInteractive{ get; }
    public static long WorkingSet{ get; }
    public static string[] GetLogicalDrives();
    public static int ExitCode{ get; set; }*/
};

template <int32_t Length>
inline int32_t Environment::GetCurrentDirectory(const gsl::span<char, Length>& destStr)
{
    return GetCurrentDirectory(destStr.data(), Length);
}

} /* namespace tgon */
