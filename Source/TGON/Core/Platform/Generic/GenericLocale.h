/**
 * @filename    GenericLocale.h
 * @author      ggomdyu
 * @since       06/14/2017
 */

#include <cstddef>

namespace tgon
{
namespace platform
{

/**
 * @brief                       Get the current language of OS.
 * @param [out] destBuffer      The destination of the string to be written.
 * @param [in] bufferLength     The length of buffer
 */
void GetLanguage(char* destBuffer, std::size_t bufferLength);

template <std::size_t N>
inline void GetLanguage(char(&destBuffer)[N])
{
    GetLanguage(destBuffer, N);
}

} /* namespace tgon */
} /* namespace tgon */
