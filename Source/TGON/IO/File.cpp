#include "PrecompiledHeader.h"

#include <cstdio>
#include <array>
#include <sys/stat.h>
#include <fstream>

#include "Time/TimeZoneInfo.h"

#include "File.h"

namespace tgon
{

std::optional<DateTime> File::GetCreationTime(const char* path)
{
    auto ret = GetCreationTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}

std::optional<DateTime> File::GetLastAccessTime(const char* path)
{
    auto ret = GetLastAccessTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}

std::optional<DateTime> File::GetLastWriteTime(const char* path)
{
    auto ret = GetLastWriteTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }

    return ret;
}

bool File::SetCreationTime(const char* path, const DateTime& creationTime)
{
    return SetCreationTimeUtc(path, creationTime);
}

bool File::SetLastAccessTime(const char* path, const DateTime& lastAccessTime)
{
    return SetLastAccessTimeUtc(path, lastAccessTime);
}

bool File::SetLastWriteTime(const char* path, const DateTime& lastWriteTime)
{
    return SetLastWriteTimeUtc(path, lastWriteTime);
}

std::unique_ptr<std::byte[]> File::ReadAllBytes(const char* path, ReturnSmartPointerTag)
{
#ifdef _MSC_VER
    FILE* fp = nullptr;
    fopen_s(&fp, path, "rb");
#else
    FILE* fp = fopen(path, "rb");
#endif
    if (fp == nullptr)
    {
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    auto fileSize = static_cast<size_t>(ftell(fp));
    fseek(fp, 0, SEEK_SET);

    auto fileData = std::make_unique<std::byte[]>(static_cast<size_t>(fileSize));
#ifdef _MSC_VER
    fread_s(&fileData[0], fileSize, 1, fileSize, fp);
#else
    fread(&fileData[0], 1, fileSize, fp);
#endif

    fclose(fp);
    return fileData;
}

std::optional<std::vector<std::byte>> File::ReadAllBytes(const char* path, ReturnVectorTag)
{
#ifdef _MSC_VER
    FILE* fp = nullptr;
    fopen_s(&fp, path, "rb");
#else
    FILE* fp = fopen(path, "rb");
#endif
    if (fp == nullptr)
    {
        return {};
    }

    fseek(fp, 0, SEEK_END);
    auto fileSize = static_cast<size_t>(ftell(fp));
    fseek(fp, 0, SEEK_SET);

    std::vector<std::byte> fileData(fileSize);
#ifdef _MSC_VER
    fread_s(&fileData[0], fileSize, 1, fileSize, fp);
#else
    fread(&fileData[0], 1, fileSize, fp);
#endif

    fclose(fp);
    return fileData;
}

std::optional<std::string> File::ReadAllText(const char* path)
{
#ifdef _MSC_VER
    FILE* fp = nullptr;
    fopen_s(&fp, path, "r");
#else
    FILE* fp = fopen(path, "r");
#endif
    if (fp == nullptr)
    {
        return {};
    }

    fseek(fp, 0, SEEK_END);
    auto fileSize = static_cast<size_t>(ftell(fp));
    fseek(fp, 0, SEEK_SET);

    std::string fileData(fileSize, '\0');
#ifdef _MSC_VER
    fread_s(&fileData[0], fileSize, 1, fileSize, fp);
#else
    fread(&fileData[0], 1, fileSize, fp);
#endif

    fclose(fp);
    return fileData;
}

std::optional<std::vector<std::string>> File::ReadAllLines(const char* path)
{
    std::ifstream fs;
    fs.open(path);
    
    if (!fs)
    {
        return {};
    }
    
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(fs, line))
    {
        if (line.empty())
        {
            continue;
        }
        
        ret.push_back(std::move(line));
    }
    
    return ret;
}

FileStream File::Create(const char* path)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Create(const char* path, int32_t bufferSize)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize);
}

FileStream File::Create(const char* path, int32_t bufferSize, FileOptions options)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize, options);
}

FileStream File::Open(const char* path, FileMode mode)
{
    return Open(path, mode, mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Open(const char* path, FileMode mode, FileAccess access)
{
    return Open(path, mode, access, FileShare::None);
}

FileStream File::Open(const char* path, FileMode mode, FileAccess access, FileShare share)
{
    return FileStream(path, mode, access, share);
}

} /* namespace tgon */
