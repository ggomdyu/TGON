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
namespace file
{

/**
 * @param [in]  srcStr  
 * @param [out] destStr 
 * @return  
 */
TGON_API std::size_t GetExtension(const char* srcStr, char* destStr);

/**
 * @param [in]  srcStr  
 * @return  
 */
TGON_API std::string GetExtension(const char* srcStr);

/**
 * @param [in]  srcStr  
 * @param [out] destStr 
 * @return  
 */
TGON_API std::size_t GetFileName(const char* srcStr, char* destStr);

/**
 * @param [in]  srcStr  
 * @return  
 */
TGON_API std::string GetFileName(const char* srcStr);

/**
 * @param [in]  srcStr  
 * @param [out] destStr 
 * @return  
 */
TGON_API std::size_t GetFileNameWithoutExtension(const char* srcStr, char* destStr);

/**
 * @param [in]  srcStr  
 * @return  
 */
TGON_API std::string GetFileNameWithoutExtension(const char* srcStr);

//public static readonly char AltDirectorySeparatorChar;
//public static readonly char DirectorySeparatorChar;
//[Obsolete("see GetInvalidPathChars and GetInvalidFileNameChars methods.")]
//public static readonly char[] InvalidPathChars;
//public static readonly char PathSeparator;
//public static readonly char VolumeSeparatorChar;
//
//public static string ChangeExtension(string path, string extension);
//public static string Combine(params string[] paths);
//public static string Combine(string path1, string path2);
//public static string Combine(string path1, string path2, string path3);
//public static string Combine(string path1, string path2, string path3, string path4);
//public static string GetDirectoryName(string path);
//public static string GetFullPath(string path);
//public static char[] GetInvalidFileNameChars();
//public static char[] GetInvalidPathChars();
//public static string GetPathRoot(string path);
//public static string GetRandomFileName();
//public static string GetTempFileName();
//public static string GetTempPath();
//public static bool HasExtension(string path);
//public static bool IsPathRooted(string path);

};

} /* namespace tgon */