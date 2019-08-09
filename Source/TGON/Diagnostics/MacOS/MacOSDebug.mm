#import "PrecompiledHeader.h"

#import <string>
#import <mutex>
#import <AppKit/NSAlert.h>

#import "../Debug.h"

namespace tgon
{

void Debug::Write(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
	std::string str(message);
    str.insert(0, m_indentLevel, '\t');

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    NSLog(@"%s", str.c_str());
#endif
}

void Debug::WriteLine(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::string str(message);
    str.insert(0, m_indentLevel, '\t');
    str += u8"\n";

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    NSLog(@"%s", str.c_str());
#endif
}

void Debug::Assert(bool condition, const std::string_view& message, const std::string_view& detailMessage)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    if (condition)
    {
        return;
    }

    Fail(message, detailMessage);
#endif
}
   
} /* namespace tgon */
