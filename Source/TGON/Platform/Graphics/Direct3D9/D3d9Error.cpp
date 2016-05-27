#include "PrecompiledHeader.h"
#include "D3d9Error.h"

#include "../Core/Error/ErrCode.h"
#include "D3d9Error.h"

template <>
const char* tgon::EnumStrings<tgon::D3d9ErrorCode>::m_stringArr[] =
{
	"ID_FAILED",
	"ID_SUCCESS",
	"ID_OUT_OF_MEMORY",
};
