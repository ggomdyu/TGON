// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-28
* ���� ���� :
* ���� ������ :
*/

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

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