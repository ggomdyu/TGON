/**
 * @filename    WindowsNativeConsole.h
 * @author      ggomdyu
 * @since       01/24/2016
 */

#pragma once
#include "../Generic/GenericNativeConsole.h"

namespace tgon {
namespace platform {

class TGON_API WindowsNativeConsole final :
    public GenericNativeConsole
{
/**
 * @section Ctor/Dtor
 */
protected:
    WindowsNativeConsole() = default;
    virtual ~WindowsNativeConsole() = default;
    
/** 
 * @section Command method
 */
public:
    /* @brief   Writes text to console. */
    virtual void Write(const char* format, ...) override;
    void Write(const wchar_t* format, ...);

    /* @brief   Writes text to console. */
    virtual void WriteLine(const char* format, ...) override;
    void WriteLine(const wchar_t* format, ...);

/**
 * @section Get method
 */
public:
    static WindowsNativeConsole* Get() noexcept;
};

using TNativeConsole = WindowsNativeConsole;

} /* namespace platform */
} /* namespace tgon */