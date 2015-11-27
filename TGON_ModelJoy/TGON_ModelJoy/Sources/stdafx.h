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

// Platform dependent SDK
#if defined( WIN32 )
	#include <Windows.h>
	#include <d3d9.h>
	#include <d3dx9.h>
	#include <atlbase.h>
#endif

// SDK
#include <fbxsdk.h>

// etc…
#include "Uncopyable.h"

#include "WindowEvent.h"
#include "WindowStyle.h"
#include "WindowsDwStyle.h"
#include "Singleton.h"
#include "msgstream.h"

#include "Direct3D9.h"


#define NSBEGIN( entry ) namespace entry {
#define NSEND( ) }

#if defined( _WIN32 ) | defined( _MSC_VER ) 
	#define TGON_MEMSORT_16 __declspec( align( 16 ))
#else
#define TGON_MEMSORT_16
#endif