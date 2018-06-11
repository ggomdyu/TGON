/**
 * @filename    GenericKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Object.h"

namespace tgon
{
    
class GenericKeyboard :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GenericKeyboard);
    
/* @section Public type */
public:
    enum class KeyCode;
    
/* @section Public destructor */
public:
    virtual ~GenericKeyboard() = 0;

};

} /* namespace tgon */
