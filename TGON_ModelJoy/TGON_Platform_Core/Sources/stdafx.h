// stdafx.h : Defines the entry point for the console application.

#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-28
* ���� ���� :
* ���� ������ :
*/

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#define NSBEGIN( name ) namespace name {
#define NSEND( ) }

#include <iostream>
#include <sstream>
#include <memory>
#include <cassert>
#include <map>
#include <unordered_set>

#include <Windows.h>
#include <dwmapi.h>

#include "msgstream.h"
#include "Uncopyable.h"
#include "WindowsWindowUtil.h"
#include "WindowStyle.h"
#include "WindowEvent.h"