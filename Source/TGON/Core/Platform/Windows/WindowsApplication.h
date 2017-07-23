/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include "../Generic/GenericApplication.h"
#include "WindowsApplicationType.h"

namespace tgon
{
namespace platform
{
namespace windows
{

class TGON_API WindowsApplication :
    public GenericApplication
{
public:
    TGON_CREATE_OBJECT_INTERFACE(tgon::platform::windows::WindowsApplication)


protected:
    WindowsApplication() = default;
    explicit WindowsApplication(HINSTANCE instanceHandle);
public:
    virtual ~WindowsApplication() = default;


public:
    using GenericApplication::GetLanguage;


public:
    void Initialize(HINSTANCE instanceHandle);
    
    bool RegisterWindowClass();

public:
    /** @brief  Get the pointer of singleton instance. */
    static WindowsApplication* Get();

    /** @brief  Return unique handle of this process. */
    HINSTANCE GetInstanceHandle() const noexcept;

    virtual void GetLanguage(char* destBuffer, std::size_t bufferLength) override;

/**
 * @section Private method
 */
private:
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

/**
 * @section Private variable
 */
private:
    HINSTANCE m_instanceHandle;
};

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */