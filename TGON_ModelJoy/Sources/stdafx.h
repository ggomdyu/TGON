/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/

#pragma once
// Standard
#include <vector>
#include <cassert>
#include <sstream>
#include <map>
#include <string>

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
#include "msgstream.h"
#include "Singleton.h"
#include "WindowsDwStyle.h"
#include "WindowStyle.h"
#include "Uncopyable.h"

#define NSBEGIN( entry ) namespace entry {
#define NSEND( ) }

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD dwColor;
};