#include "PrecompiledHeader.h"

#include "Core/String/Encoding.h"

#include "../Window.h"

#include "WindowsApplication.h"

namespace tgon
{

ApplicationImpl::ApplicationImpl()
{
    RegisterWindowClass();
}

void ApplicationImpl::ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const
{
    wchar_t utf16Message[1024] {};
    UTF8::Convert<UTF16LE>(message, std::strlen(message), reinterpret_cast<char*>(utf16Message), std::extent<decltype(utf16Message)>::value);

    wchar_t utf16Title[256] {};
    UTF8::Convert<UTF16LE>(title, std::strlen(title), reinterpret_cast<char*>(utf16Title), std::extent<decltype(utf16Title)>::value);

    ::MessageBoxW(nullptr, utf16Message, utf16Title, static_cast<UINT>(messageBoxIcon) | MB_OK);
}

LRESULT CALLBACK ApplicationImpl::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (window)
    {
        return window->OnHandleMessage(wndHandle, message, wParam, lParam);
    }

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

void ApplicationImpl::Terminate()
{
    ::PostQuitMessage(0);
}

bool ApplicationImpl::RegisterWindowClass()
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = sizeof(void*);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpfnWndProc = ApplicationImpl::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace tgon */