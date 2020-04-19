#pragma once

#include "Core/NonCopyable.h"

typedef struct tagMSG MSG;

namespace tg
{

class WindowsApplication :
    private NonCopyable
{
/**@section Type */
public:
    using MessageHandler = void(*)(const MSG&, void*);

/**@section Constructor */
protected:
    WindowsApplication();

/**@section Method */
public:
    static void SetMessageHandler(MessageHandler messageHandler, void* messageHandlerParam);

private:
    static bool RegisterDefaultWindowClass();

/**@section Variable */
protected:
    inline static MessageHandler m_messageHandler;
    inline static void* m_messageHandlerParam;
};

using PlatformApplication = WindowsApplication;

}                               
