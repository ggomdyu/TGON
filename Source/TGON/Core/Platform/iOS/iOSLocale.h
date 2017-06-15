/**
 * @filename    iOSLocale.h
 * @author      ggomdyu
 * @since       06/14/2017
 * @brief
 */

#import <cstddef>

namespace tgon
{
namespace platform
{
namespace ios
{
    
/**
 * @brief                       Get the current language of OS.
 * @param [out] destBuffer      The destination of the string to be written.
 * @param [in] bufferLength     The length of buffer
 */
void GetLanguage(char* destBuffer, std::size_t bufferLength);
    
} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */
