#include "PrecompiledHeader.h"

#include <filesystem>
#include <sys/stat.h>

#include "Time/DateTime.h"

#include "File.h"

namespace tgon
{

bool File::Copy(const std::string_view& srcFileName, const std::string_view& destFileName) noexcept
{
    return Copy(srcFileName, destFileName, false);
}

bool File::Copy(const std::string_view& srcFileName, const std::string_view& destFileName, bool overwrite) noexcept
{
    try
    {
        std::filesystem::copy_file(srcFileName, destFileName, overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none);
        return true;
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        return false;
    }
}

bool File::Delete(const std::string_view& path)
{
    return std::filesystem::remove(path);
}

bool File::Exists(const std::string_view& path)
{
    struct stat s;
    return stat(path.data(), &s) != 0;
}

bool File::Move(const std::string_view& srcFileName, const std::string_view& destFileName)
{
    try
    {
        std::filesystem::rename(srcFileName, destFileName);
        return true;
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        return false;
    }
}

std::optional<DateTime> File::GetCreationTime(const std::string_view& path)
{
    auto lastWriteTime = std::filesystem::last_write_time(path);
    auto b = std::chrono::duration_cast<std::chrono::milliseconds>(lastWriteTime.time_since_epoch());

    return std::optional<DateTime>();
}

} /* namespace tgon */
