// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <Platform.hpp>

#ifdef TGON_PLATFORM_WINDOWS
	#include <SDKDDKVer.h>
	#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// Standard
#include <memory>
#include <functional>
#include <cassert>
#include <unordered_map>

// Non-standard
#ifdef TGON_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

// User
#ifdef TGON_PLATFORM_WINDOWS
	#include "WindowsSettings.h"
#endif
#include "WindowEvent.h"
#include "WindowStyle.h"