#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>

#include "../Path.h"

namespace tgon
{
    
gsl::span<const char> Path::GetInvalidFileNameChars() noexcept
{
    constexpr char invalidFileNameChars[] = {'\0', 'a'};
    return gsl::span(invalidFileNameChars, std::extent_v<decltype(invalidFileNameChars)> - 1);
}
    
gsl::span<const char> Path::GetInvalidPathChars() noexcept
{
    constexpr char invalidPathChars[] = {'\0'};
    return gsl::span(invalidPathChars, std::extent_v<decltype(invalidPathChars)> - 1);
}

} /* namespace tgon */
