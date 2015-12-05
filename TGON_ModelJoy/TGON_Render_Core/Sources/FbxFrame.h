#pragma once

#include <string>

namespace FrameEnum {
	enum
	{
		Empty,
		Skeleton_Root,
		Skeleton_Limb,
		Skeleton_LIimbnode,
		Skeleton_Effector,
		Light,
		Camera,
		Mesh,
		Marker,
		Null,
		Root,
	};
}

struct FbxFrame
{
	FbxFrame( ) :
		frameType( FrameEnum::Empty ) {}

	int frameType;
	std::string name;
};

