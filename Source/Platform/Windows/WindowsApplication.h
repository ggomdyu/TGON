#pragma once

typedef struct tagMSG MSG;

namespace tg
{

class WindowsApplication
{
/**@section Type */
public:
    using MessageCallback = void(*)(const MSG&);

/**@section Constructor */
public:
    WindowsApplication();
    WindowsApplication(const WindowsApplication& rhs) = delete;
    WindowsApplication(WindowsApplication&& rhs) noexcept = default;

/**@section Destructor */
public:
    ~WindowsApplication() = default;

/**@section Operator */
public:
    WindowsApplication& operator=(const WindowsApplication& rhs) = delete;
    WindowsApplication& operator=(WindowsApplication&& rhs) noexcept = default;

/**@section Method */
public:
    static void SetCustomMessageCallback(MessageCallback callback);

/**@section Variable */
protected:
    inline static MessageCallback m_messageCallback;
};

using PlatformApplication = WindowsApplication;

}                               
