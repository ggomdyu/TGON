/**
 * @file    WindowsApplication.h
 * @author  ggomdyu
 * @since   02/13/2018
 */

#pragma once
#include "Core/NonCopyable.h"

typedef struct tagMSG MSG;

namespace tgon
{

class WindowsApplication :
    private NonCopyable
{
/**@section Type */
public:
    using MessageHandler = void(*)(const MSG&);

/**@section Constructor */
protected:
    WindowsApplication();

/**@section Method */
public:
    static void SetMessageHandler(MessageHandler messageHandler);

private:
    static bool RegisterDefaultWindowClass();

/**@section Variable */
protected:
    inline static MessageHandler m_messageHandler;
};

using PlatformApplication = WindowsApplication;

} /* namespace tgon */                               
