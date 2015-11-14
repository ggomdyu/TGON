#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifdef PLATFORM_WINDOWS_OS
	#define MT_NONE 0
	#define MT_CREATE WM_CREATE
	#define MT_SIZE WM_SIZE
	#define MT_MOVE WM_MOVE
	#define MT_DESTROY WM_DESTROY
#endif

struct WindowMessage
{
public:
	WindowMessage( uint32_t _uMsg = WindowMessage::None ) :
			uMsg( _uMsg ) {}

	enum : uint32_t
	{
		None = MT_NONE,
		Create = MT_CREATE,
		Size = MT_SIZE,
		Move = MT_MOVE,
		Destroy = MT_DESTROY,
	};

	uint32_t uMsg = 0;
};