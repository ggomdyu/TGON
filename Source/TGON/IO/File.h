/**
 * @file    File.h
 * @author  ggomdyu
 * @since   07/14/2019
 */

#pragma once
#include <string_view>
#include <optional>

#include "Time/DateTime.h"

namespace tgon
{
 
enum class FileAttributes
{
    Archive = 0x20,
    Compressed = 0x800,
    Device = 0x40,
    Directory = 0x10,
    Encrypted = 0x4000,
    Hidden = 0x2,
    IntegrityStream = 0x8000,
    Normal = 0x80,
    NoScrubData = 0x20000,
    NotContentIndexed = 0x2000,
    Offline = 0x1000,
    ReadOnly = 0x1,
    ReparsePoint = 0x400,
    SparseFile = 0x200,
    System = 0x4,
    Temporary = 0x100
};

class File
{
/**@section Constructor */
private:
    File() = delete;
    ~File() = delete;

/**@section Method */
public:
    static bool Copy(const std::string_view& srcFileName, const std::string_view& destFileName) noexcept;
    static bool Copy(const std::string_view& srcFileName, const std::string_view& destFileName, bool overwrite) noexcept;
    static bool Delete(const std::string_view& path);
    static bool Exists(const std::string_view& path);
    static bool Move(const std::string_view& srcFileName, const std::string_view& destFileName);
    //static void SetCreationTime(const std::string_view& path, DateTime creationTime);
    //static void SetCreationTimeUtc(const std::string_view& path, DateTime creationTimeUtc);
    //static void SetLastAccessTime(const std::string_view& path, DateTime lastAccessTime);
    //static void SetLastAccessTimeUtc(const std::string_view& path, DateTime lastAccessTimeUtc);
    static void SetLastWriteTime(const std::string_view& path, const DateTime& lastWriteTime);
    static bool SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc);
    //static void SetAttributes(const std::string_view& path, FileAttributes fileAttributes);
    static std::optional<DateTime> GetCreationTime(const std::string_view& path);
    static std::optional<DateTime> GetCreationTimeUtc(const std::string_view& path);
    static std::optional<DateTime> GetLastAccessTime(const std::string_view& path);
    static std::optional<DateTime> GetLastAccessTimeUtc(const std::string_view& path);
    static std::optional<DateTime> GetLastWriteTime(const std::string_view& path);
    static std::optional<DateTime> GetLastWriteTimeUtc(const std::string_view& path);
    static FileAttributes GetAttributes(const std::string_view& path);
    //static void AppendAllLines(const std::string_view& path, IEnumerable<string> contents);
    //static void AppendAllLines(const std::string_view& path, IEnumerable<string> contents, Encoding encoding);
    //static Task AppendAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task AppendAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static void AppendAllText(const std::string_view& path, string contents);
    //static void AppendAllText(const std::string_view& path, string contents, Encoding encoding);
    //static Task AppendAllTextAsync(const std::string_view& path, string contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task AppendAllTextAsync(const std::string_view& path, string contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static StreamWriter AppendText(const std::string_view& path);
    //static FileStream Create(const std::string_view& path);
    //static FileStream Create(const std::string_view& path, int bufferSize);
    //static FileStream Create(const std::string_view& path, int bufferSize, FileOptions options);
    //static StreamWriter CreateText(const std::string_view& path);
    //static void Decrypt(const std::string_view& path);
    //static void Encrypt(const std::string_view& path);
    //static FileStream Open(const std::string_view& path, FileMode mode);
    //static FileStream Open(const std::string_view& path, FileMode mode, FileAccess access);
    //static FileStream Open(const std::string_view& path, FileMode mode, FileAccess access, FileShare share);
    //static FileStream OpenRead(const std::string_view& path);
    //static StreamReader OpenText(const std::string_view& path);
    //static FileStream OpenWrite(const std::string_view& path);
    //static byte[] ReadAllBytes(const std::string_view& path);
    //static Task<byte[]> ReadAllBytesAsync(const std::string_view& path, CancellationToken cancellationToken = default(CancellationToken));
    //static string[] ReadAllLines(const std::string_view& path);
    //static string[] ReadAllLines(const std::string_view& path, Encoding encoding);
    //static Task<string[]> ReadAllLinesAsync(const std::string_view& path, CancellationToken cancellationToken = default(CancellationToken));
    //static Task<string[]> ReadAllLinesAsync(const std::string_view& path, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static string ReadAllText(const std::string_view& path);
    //static string ReadAllText(const std::string_view& path, Encoding encoding);
    //static Task<string> ReadAllTextAsync(const std::string_view& path, CancellationToken cancellationToken = default(CancellationToken));
    //static Task<string> ReadAllTextAsync(const std::string_view& path, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static IEnumerable<string> ReadLines(const std::string_view& path);
    //static IEnumerable<string> ReadLines(const std::string_view& path, Encoding encoding);
    //static void Replace(const std::string_view& sourceFileName, string destinationFileName, string destinationBackupFileName);
    //static void Replace(const std::string_view& sourceFileName, string destinationFileName, string destinationBackupFileName, bool ignoreMetadataErrors);
    //static void WriteAllBytes(const std::string_view& path, byte[] bytes);
    //static Task WriteAllBytesAsync(const std::string_view& path, byte[] bytes, CancellationToken cancellationToken = default(CancellationToken));
    //static void WriteAllLines(const std::string_view& path, string[] contents);
    //static void WriteAllLines(const std::string_view& path, IEnumerable<string> contents);
    //static void WriteAllLines(const std::string_view& path, string[] contents, Encoding encoding);
    //static void WriteAllLines(const std::string_view& path, IEnumerable<string> contents, Encoding encoding);
    //static Task WriteAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task WriteAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static void WriteAllText(const std::string_view& path, string contents);
    //static void WriteAllText(const std::string_view& path, string contents, Encoding encoding);
    //static Task WriteAllTextAsync(const std::string_view& path, string contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task WriteAllTextAsync(const std::string_view& path, string contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
};

} /* namespace tgon */
