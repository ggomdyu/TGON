/**
 * @file    Path.h
 * @author  ggomdyu
 * @since   04/07/2017
 */

#pragma once
#include <cstdint>
#include <string>

#include "Platform/Config.h"
#include "Core/Span.h"

namespace tgon
{

class TGON_API Path
{
/**@section Constructor */
public:
    Path() = delete;
    
/**@section Method */
public:
    static std::string Combine(const std::string_view& path1, const std::string_view& path2);
    static int32_t Combine(const std::string_view& path1, const std::string_view& path2, char* destStr, int32_t destStrBufferSize);
    static bool IsPathRooted(const std::string_view& path);
    static std::string_view GetExtension(const std::string_view& path);
    static std::string GetFileName(const std::string_view& path);
    static int32_t GetFileName(const std::string_view& path, char* destStr, int32_t destStrBufferSize);
    static std::string GetFileNameWithoutExtension(const std::string_view& path);
    static int32_t GetFileNameWithoutExtension(const std::string_view& path, char* destStr, int32_t destStrBufferSize);
    static std::string GetDirectoryName(const std::string_view& path);
    static int32_t GetDirectoryName(const std::string_view& path, char* destStr, int32_t destStrBufferSize);
    static bool HasExtension(const std::string_view& path);
    static std::string ChangeExtension(const std::string_view& path, const std::string_view& extension);
    static int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr);
    static std::string GetFullPath(const std::string_view& path);
    static int32_t GetFullPath(const std::string_view& path, char* destStr, int32_t destStrBufferSize);
    static int32_t GetFullPath(const std::string_view& path, const Span<char>& destStr);
//    static std::string GetFullPath(const std::string_view& path, const std::string_view& basePath);
//    static std::string GetPathRoot(const std::string_view& path);
//    static std::string GetRandomFileName();
//    static std::string GetTempPath();
//    static const std::vector<char>& GetInvalidFileNameChars();
//    static const std::vector<char>& GetInvalidPathChars();

private:
    static bool IsValidDriveChar(char ch) noexcept;
    static bool IsDirectorySeparator(char ch) noexcept;

/**@section Variable */
public:
    static constexpr char AltDirectorySeparatorChar = '/';
    static constexpr char DirectorySeparatorChar = '\\';
    static constexpr char PathSeparator = ';';
    static constexpr char VolumeSeparatorChar = ':';
};

} /* namespace tgon */
