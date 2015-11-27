// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-28
* 최종 수정 :
* 최종 수정일 :
*/

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#define NSBEGIN( name ) namespace name {
#define NSEND( ) }

#include <iostream>
#include <memory>
#include <cassert>
#include <map>
#include <unordered_set>

#include <Windows.h>
#include <dwmapi.h>

#include "Uncopyable.h"
#include "WindowsDwStyle.h"
#include "WindowStyle.h"
#include "WindowEvent.h"