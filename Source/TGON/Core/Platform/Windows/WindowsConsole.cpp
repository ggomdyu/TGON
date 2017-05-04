#include "PrecompiledHeader.h"
#include "WindowsConsole.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

namespace tgon {
namespace {

class WindowsConsoleHelper final
{
/**
 * @section Ctor/Dtor
 */
private:
    WindowsConsoleHelper();
    ~WindowsConsoleHelper();

public:
    static WindowsConsoleHelper* Get();

/**
 * @section Get method
 */
private:    
    HANDLE GetConsoleHandle() const;

/**
 * @section Private variables
 */
private:
	HANDLE m_outputHandle;
};

WindowsConsoleHelper::WindowsConsoleHelper( )
{
#ifdef TGON_ENABLE_CONSOLE
    bool consoleAlreadyCreated = ::GetConsoleWindow();
    if (!consoleAlreadyCreated)
    {
        if (::AllocConsole() == FALSE)
        {
			assert(false && "Failed to create console.");
		}
	}

    m_outputHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

WindowsConsoleHelper::~WindowsConsoleHelper()
{
#ifdef TGON_ENABLE_CONSOLE
    ::FreeConsole();
#endif
}

WindowsConsoleHelper* WindowsConsoleHelper::Get()
{
    static WindowsConsoleHelper instance;
    return &instance;
}

HANDLE WindowsConsoleHelper::GetConsoleHandle() const
{
    return m_outputHandle;
}

} /*namespace*/

void GenericConsole::Write(const char* format, ...)
{
#ifdef TGON_ENABLE_CONSOLE
    va_list vaList;
    va_start(vaList, format);
    
    vsprintf_s(m_buffer, BufferSize, format, vaList);
    
    ::WriteConsoleA(
        WindowsConsoleHelper::Get()->GetConsoleHandle(),
        m_buffer,
        std::strlen(m_buffer),
        nullptr,
    	nullptr
    );
#endif
}

//void WindowsConsole::Write(const char* str)
//{
//#ifndef TGON_ENABLE_CONSOLE
//	::WriteConsoleA(
//        WindowsConsoleHelper::Get().GetConsoleHandle(),
//        str,
//        std::strlen(str),
//        nullptr,
//		nullptr
//	);
//#endif
//}
//
//void WindowsConsole::Write(const wchar_t* str)
//{
//#ifndef NDEBUG
//	::WriteConsoleW(
//		WindowsConsoleHelper::Get().GetConsoleHandle(),
//		str,
//		std::wcslen(str),
//		nullptr,
//		nullptr
//	);
//#endif
//}
//
//template<typename DerivedTy>
//inline void GenericConsole<DerivedTy>::Write(const wchar_t* str, ...)
//{
//    va_list vaList;
//    va_start(vaList, str);
//
//    // Build string
//    vswprintf_s(m_wideBuffer.get(), BUFFER_SIZE, str, vaList);
//
//    // And finally output
//    DerivedTy::WriteImpl(m_wideBuffer.get());
//}
//
//template<typename DerivedTy>
//inline void GenericConsole<DerivedTy>::WriteLine(const char* str, ...)
//{
//    va_list vaList;
//    va_start(vaList, str);
//
//    // Build string
//    vsprintf_s(m_buffer.get(), BUFFER_SIZE, str, vaList);
//
//    // And finally output
//    //DerivedTy::WriteImpl( m_buffer.get( ));
//    //DerivedTy::WriteImpl( "\n" );
//}
//
//template<typename DerivedTy>
//inline void GenericConsole<DerivedTy>::WriteLine(const wchar_t* str, ...)
//{
//    va_list vaList;
//    va_start(vaList, str);
//
//    // Build string
//    vswprintf_s(m_wideBuffer.get(), BUFFER_SIZE, str, vaList);
//
//    // And finally output
//    //DerivedTy::WriteImpl( m_wideBuffer.get( ));
//    //DerivedTy::WriteImpl( "\n" );
//}

} /* namespace tgon */