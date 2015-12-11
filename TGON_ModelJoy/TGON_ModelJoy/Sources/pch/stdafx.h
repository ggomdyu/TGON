/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/

#pragma once

// Standard
#include <cassert>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>

// etc…
#include "Uncopyable.h"

#include "WindowEvent.h"
#include "WindowStyle.h"
#include "Singleton.h"

#include "Direct3D9.h"


#define NSBEGIN( entry ) namespace entry {
#define NSEND( ) }

#if defined( _WIN32 ) | defined( _MSC_VER ) /* using VC++? */
	#define TGON_MEMSORT_16 __declspec( align( 16 ))
#else
#define TGON_MEMSORT_16
#endif