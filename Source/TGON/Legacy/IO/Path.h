/**
 * @filename    Path.h
 * @author      ggomdyu
 * @since       04/07/2017
 */

#pragma once
#include <string>

namespace tgon
{

class Path
{
/**
 * @section Ctor/Dtor
 */
public:
    Path() = delete;
    ~Path() = delete;

public:
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
    static int GetExtension(const char* src, char* dest);
    static std::string GetExtension(const char* src);

    /**
     * @param   src     The path of file
     * @param   dest    The destination of file name
     * @return          The Length of file name
     */
    static std::size_t GetFileName(const char* src, char* dest);

    /**
     * @param   src     The path of file
     * @return          The string of file name
     */
    static std::string GetFileName(const char* src);

    /**
     * @param   src     The path of file
     * @param   dest    The destination of file name
     * @return          The Length of file name
     */
    static std::size_t GetFileNameWithoutExtension(const char* src, char* dest);
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