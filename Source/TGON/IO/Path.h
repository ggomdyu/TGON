/**
 * @file    Path.h
 * @author  ggomdyu
 * @since   04/07/2017
 */

#pragma once
#include <cstdint>
#include <string>

#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   undef GetCurrentDirectory
#endif

namespace tgon
{

class TGON_API Path
{
/**@section Method */
public:
    static std::string GetExtension(const std::string_view& path);
    static int32_t GetExtension(const std::string_view& path, char* destStr);
    static std::string GetFileName(const std::string_view& path);
    static int32_t GetFileName(const std::string_view& path, char* destStr);
    static std::string GetFileNameWithoutExtension(const std::string_view& path);
    static int32_t GetFileNameWithoutExtension(const std::string_view& path, char* destStr);
    static std::string GetDirectoryName(const std::string_view& path);
    static int32_t GetDirectoryName(const std::string_view& path, char* destStr);
    static bool HasExtension(const std::string_view& path);
    static std::string ChangeExtension(const std::string_view& path, const std::string_view& extension);
    static int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr);
    static std::string GetCurrentDirectory();
    static int32_t GetCurrentDirectory(char* destStr);
    static std::string GetUserDirectory();
    static int32_t GetUserDirectory(char* destStr);
    static std::string GetDesktopDirectory();
    static int32_t GetDesktopDirectory(char* destStr);
    static std::string GetFontsDirectory();
    static int32_t GetFontsDirectory(char* destStr);
    static std::string GetMusicDirectory();
    static int32_t GetMusicDirectory(char* destStr);
    static std::string GetPicturesDirectory();
    static int32_t GetPicturesDirectory(char* destStr);
    static std::string GetVideosDirectory();
    static int32_t GetVideosDirectory(char* destStr);
    static std::string GetDocumentsDirectory();
    static int32_t GetDocumentsDirectory(char* destStr);

/**@section Variable */
public:
    static constexpr const char AltDirectorySeparatorChar = '/';
    static constexpr const char DirectorySeparatorChar = '\\';
};

} /* namespace tgon */