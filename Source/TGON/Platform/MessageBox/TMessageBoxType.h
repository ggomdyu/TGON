#pragma once
#include "../Platform/Slate/PlatformMessageBox.h"


namespace tgon
{


enum struct TMsgBoxButton
{
	Ok				= static_cast<int>( MsgBoxButtonImpl::Ok ),
	OkCancel		= static_cast<int>( MsgBoxButtonImpl::OkCancel ),
	YesNo			= static_cast<int>( MsgBoxButtonImpl::YesNo ),
	YesNoCancel		= static_cast<int>( MsgBoxButtonImpl::YesNoCancel ),
};

enum struct TMsgBoxFlag
{
	None			= 0,
	IconQuestion	= static_cast<int>( MsgBoxFlagImpl::IconQuestion ),
	IconExclamation = static_cast<int>( MsgBoxFlagImpl::IconExclamation ),
	IconAsterisk	= static_cast<int>( MsgBoxFlagImpl::IconAsterisk ),
};


}