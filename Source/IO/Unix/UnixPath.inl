#pragma once

namespace tg
{

constexpr std::string_view Path::GetPathRoot(const std::string_view& path) noexcept
{
    return IsDirectorySeparator(path[0]) ? DirectorySeparatorStr : std::string_view();
}

constexpr int32_t Path::GetRootLength(const std::string_view& path) noexcept
{
    return path.length() > 0 && Path::IsDirectorySeparator(path[0]) ? 1 : 0;
}

}
