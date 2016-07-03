#pragma once
#include "../Slate/PlatformMessageBox.h"


namespace tgon
{


enum struct TMsgBoxButton
{
	Ok				= static_cast<int32_t>( MsgBoxButtonImpl::Ok ),
	OkCancel		= static_cast<int32_t>( MsgBoxButtonImpl::OkCancel ),
	YesNo			= static_cast<int32_t>( MsgBoxButtonImpl::YesNo ),
	YesNoCancel		= static_cast<int32_t>( MsgBoxButtonImpl::YesNoCancel ),
};

enum struct TMsgBoxFlag
{
	None			= 0,
	IconQuestion	= static_cast<int32_t>( MsgBoxFlagImpl::IconQuestion ),
	IconExclamation = static_cast<int32_t>( MsgBoxFlagImpl::IconExclamation ),
	IconAsterisk	= static_cast<int32_t>( MsgBoxFlagImpl::IconAsterisk ),
};


}