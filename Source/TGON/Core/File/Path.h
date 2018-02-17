/**
 * @filename    Path.h
 * @author      ggomdyu
 * @since       04/07/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstdint>
#include <string>

namespace tgon
{
namespace core
{

constexpr const char AltDirectorySeparatorChar = '/';
constexpr const char DirectorySeparatorChar = '\\';

/**
 * @brief                   Gets the extension name from specified path.
 * @param [in] srcStr       The path from which to get the extension.
 * @param [in] srcStrLen    The length of srcStr.
 * @param [out] destStr     The destination of extension name.
 * @return                  Returns the extension name if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcStr, int32_t srcStrLen, const char** destStr);

/**
 * @brief                   Gets the extension name from specified path.
 * @param [in] srcStr       The path from which to get the extension.
 * @param [out] destStr     The destination of extension name.
 * @return                  Returns the extension name if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcStr, const char** destStr);

/**
 * @brief                   Gets the extension name from specified path.
 * @param [in] srcStr       The path from which to get the extension.
 * @param [in] srcStrLen    The length of srcStr.
 * @param [out] destStr     The destination of extension name.
 * @return                  Returns the length of destStr if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcStr, int32_t srcStrLen, char* destStr);

/**
 * @brief                   Gets the extension name from specified path.
 * @param [in] srcStr       The path from which to get the extension.
 * @param [out] destStr     The destination of extension name.
 * @return                  Returns the length of destStr if successful, -1 otherwise.
 */
TGON_API int32_t GetExtension(const char* srcStr, char* destStr);

/**
 * @brief                   Gets the file name with extension from specified path.
 * @param [in] srcStr       The path from which to get file name with extension.
 * @param [in] srcStrLen    The length of srcStr.
 * @param [out] destStr     The destination of file name.
 * @return                  Returns the length of destStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileName(const char* srcStr, int32_t srcStrLen, char* destStr);

/**
 * @brief                   Gets the file name with extension from specified path.
 * @param [in]  srcStr      The path from which to get file name with extension.
 * @param [out] destStr     The destination of file name.
 * @return                  Returns the length of destStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileName(const char* srcStr, char* destStr);

/**
 * @brief                   Gets the file name without extension from specified path.
 * @param [in] srcStr       The path from which to get file name without extension.
 * @param [out] destStr     The destination of file name.
 * @return                  Returns the length of destStr if successful, -1 otherwise.
 */
TGON_API int32_t GetFileNameWithoutExtension(const char* srcStr, char* destStr);

/**
 * @brief                   Checks whether the specified string has extension.
 * @param [in] srcStr       The string to check for the existence of the extension.
 * @param [in] srcStrLen    The length of srcStr.
 * @return                  Returns true if the string has extension, false otherwise.
 */
TGON_API bool HasExtension(const char* srcStr, int32_t srcStrLen);

/**
 * @brief                   Checks whether the specified string has extension.
 * @param [in] srcStr       The string to check for the existence of the extension.
 * @return                  Returns true if the string has extension, false otherwise.
 */
TGON_API bool HasExtension(const char* srcStr);

/**
 * @brief                   Changes the extension name to given another extension name.
 * @param [in] srcStr       The string to check for the existence of the extension.
 * @return                  Returns true if the string has extension, false otherwise.
 */
TGON_API int32_t ChangeExtension(char* srcStr, const char* extensionName);

TGON_API int32_t GetCurrentDirectory(char* destStr);

//public static string Combine(params string[] paths);
//public static string Combine(string path1, string path2);
//public static string Combine(string path1, string path2, string path3);
//public static string Combine(string path1, string path2, string path3, string path4);
//public static string GetDirectoryName(string path);
//public static string GetFullPath(string path);
//public static string GetPathRoot(string path);
//public static string GetTempFileName();
//public static string GetTempPath();

} /* namespace core */
} /* namespace tgon */
