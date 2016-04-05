#include "PrecompiledHeader.h"
#include "LayeredConsole.h"


void tgon::LayeredConsole::FillBuffer( const char* arg )
{
	enum
	{
		kMaxConvertableSize = 256,
	};

	wchar_t wcsDest[kMaxConvertableSize] = {0};

#ifdef _MSC_VER
	size_t cvCharNum = 0;
	mbstowcs_s( &cvCharNum, wcsDest, arg, kMaxConvertableSize );
#else
	std::mbstowcs( wcsDest, arg, kMaxConvertableSize );
#endif

	m_buf += wcsDest;
}