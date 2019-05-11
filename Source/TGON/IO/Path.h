/**
 * @file    Path.h
 * @author  ggomdyu
 * @since   04/07/2017
 */

#pragma once
#include <cstdint>
#include <string>

#include "Platform/Config.h"

#ifdef GetCurrentDirectory
#   undef GetCurrentDirectory
#endif

namespace tgon
{

constexpr const char AltDirectorySeparatorChar = '/';
constexpr const char DirectorySeparatorChar = '\\';

TGON_API std::string GetExtension(const std::string_view& path);
TGON_API int32_t GetExtension(const std::string_view& path, char* destStr);
TGON_API std::string GetFileName(const std::string_view& path);
TGON_API int32_t GetFileName(const std::string_view& path, char* destStr);
TGON_API std::string GetFileNameWithoutExtension(const std::string_view& path);
TGON_API int32_t GetFileNameWithoutExtension(const std::string_view& path, char* destStr);
TGON_API std::string GetDirectoryName(const std::string_view& path);
TGON_API int32_t GetDirectoryName(const std::string_view& path, char* destStr);
TGON_API bool HasExtension(const std::string_view& path);
TGON_API std::string ChangeExtension(const std::string_view& path, const std::string_view& extension);
TGON_API int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr);
TGON_API std::string GetCurrentDirectory();
TGON_API int32_t GetCurrentDirectory(char* destStr);
TGON_API std::string GetUserDirectory();
TGON_API int32_t GetUserDirectory(char* destStr);
TGON_API std::string GetDesktopDirectory();
TGON_API int32_t GetDesktopDirectory(char* destStr);
TGON_API std::string GetFontsDirectory();
TGON_API int32_t GetFontsDirectory(char* destStr);

} /* namespace tgon */
