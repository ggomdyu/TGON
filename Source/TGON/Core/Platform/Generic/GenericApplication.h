/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * since        03/20/2016
 */

#pragma once
#include "GenericApplicationType.h"
#include "Core/Object/TObject.h"

namespace tgon
{
namespace platform
{

class TGON_API GenericApplication :
    public object::TObject
{
public:
    TGON_CREATE_OBJECT_INTERFACE(tgon::platform::GenericApplication)

/**
 * @section Ctor/Dtor
 */
protected:
    GenericApplication() = default;
public:
    virtual ~GenericApplication() = default;

/**
 * @section Public method
 */
public:
    /**
     * @brief                       Get the current language of OS.
     * @param [out] destBuffer      The destination of the string to be written.
     * @param [in] bufferLength     The length of buffer
     */
    virtual void GetLanguage(char* destBuffer, std::size_t bufferLength) = 0;

    /**
     * @brief                       Get the current language of OS.
     * @tparam N                    The length of buffer
     * @param [out] destBuffer      The destination of the string to be written.
     */
    template <std::size_t N>
    void GetLanguage(char(&destBuffer)[N]);
};

template<std::size_t N>
inline void GenericApplication::GetLanguage(char(&destBuffer)[N])
{
    this->GetLanguage(destBuffer, bufferLength);
}

} /* namespace platform */
} /* namespace tgon */