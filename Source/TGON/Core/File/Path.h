/**
 * @filename    Path.h
 * @author      ggomdyu
 * @since       04/07/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstdint>
#include <string>

#ifdef GetCurrentDirectory
#   undef GetCurrentDirectory
#endif

namespace tgon
{
namespace core
{

enum class SpecialDirectoryType
{
    MyMusics,
    MyVideos,
    Personal,
    Desktop,
    Fonts,

};

constexpr const char AltDirectorySeparatorChar = '/';
constexpr const char DirectorySeparatorChar = '\\';

/**
 * @brief                       Gets the extension name from specified path.
 * @param [in] srcPathStr       The path from which to get the extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @return                      Returns the extension name.
 */
TGON_API std::string GetExtension(const char* srcPathStr, int32_t srcPathStrLen);

/**
 * @brief                   Gets the extension name from specified path.
 * @param [in] srcPathStr   The path from which to get the extension.
 * @return                  Returns the extension name.
 */
TGON_API std::string GetExtension(const char* srcPathStr);

/**
 * @brief                       Gets the extension name from specified path.
 * @param [in] srcPathStr       The path from which to get the extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @param [out] destPathStr     The destination of extension name.
 * @return                      Returns the extension name if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcPathStr, int32_t srcPathStrLen, const char** destPathStr);

/**
 * @brief                       Gets the extension name from specified path.
 * @param [in] srcPathStr       The path from which to get the extension.
 * @param [out] destPathStr     The destination of extension name.
 * @return                      Returns the extension name if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcPathStr, const char** destPathStr);

/**
 * @brief                       Gets the extension name from specified path.
 * @param [in] srcPathStr       The path from which to get the extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @param [out] destPathStr     The destination of extension name.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr);

/**
 * @brief                       Gets the extension name from specified path.
 * @param [in] srcPathStr       The path from which to get the extension.
 * @param [out] destPathStr     The destination of extension name.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcPathStr, char* destPathStr);

/**
 * @brief                       Gets the file name with extension from specified path.
 * @param [in] srcPathStr       The path from which to get file name with extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @return                      Returns the file name with extension.
 */
TGON_API std::string GetFileName(const char* srcPathStr, int32_t srcPathStrLen);

/**
 * @brief                   Gets the file name with extension from specified path.
 * @param [in] srcPathStr   The path from which to get file name with extension.
 * @return                  Returns the file name with extension.
 */
TGON_API std::string GetFileName(const char* srcPathStr);

/**
 * @brief                       Gets the file name with extension from specified path.
 * @param [in] srcPathStr       The path from which to get file name with extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @param [out] destPathStr     The destination of file name.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileName(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr);

/**
 * @brief                       Gets the file name with extension from specified path.
 * @param [in]  srcPathStr      The path from which to get file name with extension.
 * @param [out] destPathStr     The destination of file name.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileName(const char* srcPathStr, char* destPathStr);

/**
 * @brief                       Gets the file name without extension from specified path.
 * @param [in] srcPathStr       The path from which to get file name without extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @return                      Returns the file name without extension.
 */
TGON_API std::string GetFileNameWithoutExtension(const char* srcPathStr, int32_t srcPathStrLen);

/**
 * @brief                   Gets the file name without extension from specified path.
 * @param [in] srcPathStr   The path from which to get file name without extension.
 * @return                  Returns the file name without extension.
 */
TGON_API std::string GetFileNameWithoutExtension(const char* srcPathStr);

/**
 * @brief                       Gets the file name without extension from specified path.
 * @param [in] srcPathStr       The path from which to get file name without extension.
 * @param [out] destPathStr     The destination of file name.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileNameWithoutExtension(const char* srcPathStr, char* destPathStr);

/**
 * @brief                       Gets the path of file.
 * @param [in] srcPathStr       The full file path from which to get path without file name.
 * @param [out] destPathStr     The destination of file path.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetDirectoryName(const char* srcPathStr, char* destPathStr);

/**
 * @brief                       Gets the path of file.
 * @param [in] srcPathStr       The full file path from which to get path without file name.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @param [out] destPathStr     The destination of file path.
 * @return                      Returns the length of destPathStr if successful, -1 otherwise.
 */
TGON_API int32_t GetDirectoryName(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr);

/**
 * @brief                       Checks whether the specified string has an extension.
 * @param [in] srcPathStr       The string to check for the existence of the extension.
 * @param [in] srcPathStrLen    The length of srcPathStr.
 * @return                      Returns true if the string has an extension, false otherwise.
 */
TGON_API bool HasExtension(const char* srcPathStr, int32_t srcPathStrLen);

/**
 * @brief                   Checks whether the specified string has an extension.
 * @param [in] srcPathStr   The string to check for the existence of the extension.
 * @return                  Returns true if the string has an extension, false otherwise.
 */
TGON_API bool HasExtension(const char* srcPathStr);

/**
 * @brief                   Changes the extension name to given another extension name.
 * @param [in] srcPathStr       The string to check for the existence of the extension.
 * @return                  Returns the length of extension that changed.
 */
TGON_API std::string ChangeExtension(const char* srcPathStr);

TGON_API int32_t ChangeExtension(char* srcPathStr, const char* srcExtensionStr);

TGON_API int32_t GetCurrentDirectory(char* destPathStr, int32_t destPathStrBufferSize);

template <std::size_t _DestPathStrBufferSize>
inline int32_t GetCurrentDirectory(char(&destPathStr)[_DestPathStrBufferSize])
{
    return GetCurrentDirectory(destPathStr, _DestPathStrBufferSize);
}

TGON_API std::string GetCurrentDirectory();

TGON_API int32_t GetUserDirectory(char* destPathStr, int32_t destPathStrBufferSize);

template <std::size_t _DestPathStrBufferSize>
inline int32_t GetUserDirectory(char(&destPathStr)[_DestPathStrBufferSize])
{
    return GetUserDirectory(destPathStr, _DestPathStrBufferSize);
}

TGON_API std::string GetUserDirectory();

TGON_API int32_t GetDesktopDirectory(char* destPathStr, int32_t destPathStrBufferSize);

template <std::size_t _DestPathStrBufferSize>
inline int32_t GetDesktopDirectory(char(&destPathStr)[_DestPathStrBufferSize])
{
    return GetDesktopDirectory(destPathStr, _DestPathStrBufferSize);
}

TGON_API std::string GetDesktopDirectory();

TGON_API std::string GetDirectory(SpecialDirectoryType specialDirectoryType);

//public static string Combine(params string[] paths);
//public static string Combine(string path1, string path2);
//public static string Combine(string path1, string path2, string path3);
//public static string Combine(string path1, string path2, string path3, string path4);
//public static string GetFullPath(string path);
//public static string GetPathRoot(string path);
//public static string GetTempFileName();
//public static string GetTempPath();

} /* namespace core */
} /* namespace tgon */
