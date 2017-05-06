/**
 * @filename    GenericNativeConsole.h
 * @author      ggomdyu
 * @since       03/23/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {
namespace platform {

class TGON_API GenericNativeConsole
{
/*
 * @section Ctor/Dtor
 */
protected:
    GenericNativeConsole() = default;
    ~GenericNativeConsole() = default;

/** 
 * @section Public method
 */ 
public:
    /* @brief   Writes text to console. */
    virtual void Write(const char* format, ...) = 0;
    
    /* @brief   Writes text to console. */
    virtual void WriteLine(const char* format, ...) = 0;
};

} /* namespace platform */
} /* namespace tgon */